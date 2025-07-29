#include <opencv2/opencv.hpp>
#include <vector>
#include <iostream>
#include <cmath>
#include <cstdio>
#include "lane_detect.h"

using namespace cv;
using namespace std;

// --- LKAS 명령 구조체 ---
struct LKASCommand {
    bool intervention;      // LKAS 개입 여부
    float steering_angle;   // 복귀 조향각(P, deg)
    float left_speed;       // 왼쪽 바퀴 속도(퍼센트, 0~100)
    float right_speed;      // 오른쪽 바퀴 속도(퍼센트, 0~100)
};

// --- LKAS 명령 산출 함수 (속도 합 100% 보정) ---
LKASCommand get_lkas_command(
    int offset,
    int offset_threshold = 20,
    float k = 0.4f,
    float base_speed_percent = 100,
    float max_delta_percent = 50
) {
    LKASCommand cmd;

    if (std::abs(offset) < offset_threshold) {
        // 차선 내: 개입 없음, 좌우 속도 동일, 합 100%
        cmd.intervention = false;
        cmd.steering_angle = 0.0f;
        cmd.left_speed = base_speed_percent / 2.0f;
        cmd.right_speed = base_speed_percent / 2.0f;
    } else {
        // 차선 이탈: 개입, steering angle 및 좌우 속도 차 조절
        cmd.intervention = true;
        cmd.steering_angle = k * offset;

        float delta = std::max(std::min(k * offset, max_delta_percent), -max_delta_percent);

        // 기본 좌우 속도에서 delta/2 만큼 차이 발생, 합이 base_speed_percent 유지되도록 보정
        float left_pct = (base_speed_percent / 2.0f) - delta / 2.0f;
        float right_pct = (base_speed_percent / 2.0f) + delta / 2.0f;

        float scale = base_speed_percent / (left_pct + right_pct); // 보정 계수

        cmd.left_speed = left_pct * scale;
        cmd.right_speed = right_pct * scale;

        // 속도 범위 0~100% 제한 (안전장치)
        cmd.left_speed = std::clamp(cmd.left_speed, 0.0f, 100.0f);
        cmd.right_speed = std::clamp(cmd.right_speed, 0.0f, 100.0f);
    }
    return cmd;
}

const int Width = 320;
const int Height = 240;

int main() {
    VideoCapture cap(0);
    if (!cap.isOpened()) {
        cerr << "Camera open failed!" << endl;
        return -1;
    }

    vector<Point> roi_verts = {
        Point(Width * 0.18, Height * 0.62),
        Point(Width * 0.05, Height * 0.98),
        Point(Width * 0.95, Height * 0.98),
        Point(Width * 0.82, Height * 0.62)
    };
    Mat roi_mask = get_roi_mask(Size(Width, Height), roi_verts);

    double last_time = getTickCount();
    int y_bottom = Height - 1;
    int y_top = static_cast<int>(Height * 0.62);

    // LKAS 환경 변수
    const int offset_threshold = 20;
    const float k = 0.4f;
    const float base_speed_percent = 100;
    const float max_delta_percent = 50;

    while (true) {
        Mat frame, disp;
        if (!cap.read(frame)) break;
        resize(frame, frame, Size(Width, Height));
        disp = frame.clone();

        Mat mask = filter_white(frame);
        Mat edges;
        Canny(mask, edges, 50, 150);  // 환경 맞게 조정 가능
        Mat roi = region_of_interest(edges, roi_mask);

        vector<Point> left_pts = sliding_lane_points(roi, true);
        vector<Point> right_pts = sliding_lane_points(roi, false);

        LaneFitInfo left_info = analyze_lane(left_pts, y_top, y_bottom);
        LaneFitInfo right_info = analyze_lane(right_pts, y_top, y_bottom);

        vector<Point> left_curve, right_curve;
        if (left_info.valid) {
            for (int y = y_bottom; y >= y_top; --y) {
                int x = cvRound(left_info.poly[0] * y * y + left_info.poly[1] * y + left_info.poly[2]);
                if (x >= 0 && x < Width && roi_mask.at<uchar>(y, x) > 0)
                    left_curve.emplace_back(x, y);
            }
        }
        if (right_info.valid) {
            for (int y = y_bottom; y >= y_top; --y) {
                int x = cvRound(right_info.poly[0] * y * y + right_info.poly[1] * y + right_info.poly[2]);
                if (x >= 0 && x < Width && roi_mask.at<uchar>(y, x) > 0)
                    right_curve.emplace_back(x, y);
            }
        }

        if (left_curve.size() > 5 && right_curve.size() > 5)
            fill_lane_area(disp, left_curve, right_curve, Scalar(0, 255, 0), roi_mask);

        draw_roi(disp, roi_verts, Scalar(0, 255, 255), 2);

        if (left_info.valid)
            draw_curve_in_roi(disp, left_info.poly, roi_mask, Scalar(255, 0, 0), 3);
        if (right_info.valid)
            draw_curve_in_roi(disp, right_info.poly, roi_mask, Scalar(0, 255, 0), 3);

        LKASCommand lkas = {};
        bool lanes_detected = (left_info.valid && right_info.valid);

        int x = 10, y0 = 60, line_gap = 20;

        if (lanes_detected) {
            int lane_center = (left_info.x_bottom + right_info.x_bottom) / 2;
            int car_center = Width / 2;
            int offset = lane_center - car_center;

            lkas = get_lkas_command(offset, offset_threshold, k, base_speed_percent, max_delta_percent);

            // *** MCU/외부 송신 함수 호출 위치 ***
            // send_to_mcu(lkas.intervention, lkas.steering_angle, lkas.left_speed, lkas.right_speed);

            // 화면에 줄바꿈하여 출력
            if (lkas.intervention) {
                putText(disp, "LKAS ACTIVE", Point(x, y0), FONT_HERSHEY_SIMPLEX, 0.5, Scalar(0, 255, 255), 1);
                char angle_buf[64], speed_buf[64];
                sprintf(angle_buf, "angle: %.1f deg", lkas.steering_angle);
                sprintf(speed_buf, "L: %.1f   R: %.1f", lkas.right_speed, lkas.left_speed);
                putText(disp, angle_buf, Point(x, y0 + line_gap), FONT_HERSHEY_SIMPLEX, 0.5, Scalar(0, 255, 0), 1);
                putText(disp, speed_buf, Point(x, y0 + 2 * line_gap), FONT_HERSHEY_SIMPLEX, 0.5, Scalar(0, 200, 255), 1);
            } else {
                putText(disp, "LKAS SLEEP", Point(x, y0), FONT_HERSHEY_SIMPLEX, 0.5, Scalar(100, 255, 100), 1);
                putText(disp, "(Keep Lane)", Point(x, y0 + line_gap), FONT_HERSHEY_SIMPLEX, 0.5, Scalar(100, 255, 100), 1);
            }
        } else {
            putText(disp, "not detected", Point(20, Height - 20), FONT_HERSHEY_SIMPLEX, 0.6, Scalar(0, 0, 255), 2);
            // 안전을 위해 MCU에 명령 송신 시 기본값으로 Send 가능
            // send_to_mcu(false, 0, 0, 0);
        }

        double current_time = getTickCount();
        double elapsed_sec = (current_time - last_time) / getTickFrequency();
        last_time = current_time;
        double fps = 1.0 / elapsed_sec;
        char fps_text[32];
        sprintf(fps_text, "FPS: %.2f", fps);
        putText(disp, fps_text, Point(20, 120), FONT_HERSHEY_SIMPLEX, 0.5, Scalar(0, 255, 0), 2);

        imshow("Lane & LKAS", disp);
        if ((char)waitKey(1) == 'q') break;
    }
    cap.release();
    destroyAllWindows();
    return 0;
}
