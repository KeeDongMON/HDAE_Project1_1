#include <opencv2/opencv.hpp>
#include <vector>
#include <iostream>
#include <cmath>
#include <cstdio>
#include <linux/can.h>
#include <linux/can/raw.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <net/if.h>
#include <cstring>
#include <unistd.h>
#include <sys/ioctl.h>
#include "lane_detect.h"
#include "color.h"
#include "can.h"
#include "draw.h"
#include "lkas.h"

using namespace cv;
using namespace std;

const int Width = 320;
const int Height = 240;

int main() {
    if (!init_can_socket("can0")) {
        cerr << "CAN initialization failed" << endl;
        // return -1;
    }

    VideoCapture cap(0);
    cap.set(CAP_PROP_FRAME_WIDTH, Width);
    cap.set(CAP_PROP_FRAME_HEIGHT, Height);
    if (!cap.isOpened()) {
        cerr << "Camera open failed!" << endl;
        return -1;
    }
    PIDController pid(0.4f, 0.0f, 0.1f);

    // -------- [1] ROI 정의 ----------
    Rect lane_roi_rect(0, Height * 2 / 3, Width, Height / 3);      // 하단 1/3
    Rect tlight_roi_rect(0, 0, Width, (Height * 2) / 3);           // 상단 2/3

    int y_bottom = Height - 1;
    int y_top = Height / 3;

    const int offset_threshold = 30;
    const int MAX_PWM = 150;

    double last_time = getTickCount();
    int frame_count = 0;

    // 바퀴 PWM
    const int R_FIXED_LEFT_PWM = 200;
    const int R_FIXED_RIGHT_PWM = 130;
    const int L_FIXED_LEFT_PWM = 130;
    const int L_FIXED_RIGHT_PWM = 200;

    const int edge_margin = 20;   // 벽 판정

    // ROI 꼭짓점 벡터
    vector<Point> lane_roi_verts = {
        Point(lane_roi_rect.x, lane_roi_rect.y),
        Point(lane_roi_rect.x, lane_roi_rect.y + lane_roi_rect.height - 1),
        Point(lane_roi_rect.x + lane_roi_rect.width - 1, lane_roi_rect.y + lane_roi_rect.height - 1),
        Point(lane_roi_rect.x + lane_roi_rect.width - 1, lane_roi_rect.y)
    };
    Mat lane_roi_mask = get_roi_mask(Size(Width, Height), lane_roi_verts);

    while (true) {
        Mat frame;
        if (!cap.read(frame)) break;

        char direction = 'S';
        float offset = 0.0f;
        LKASCommand lkas = {};

        frame_count++;

        double current_time = getTickCount();
        double elapsed_sec = (current_time - last_time) / getTickFrequency();
        last_time = current_time;
        double fps = 1.0 / elapsed_sec;

        draw_fps_info(frame, fps, Height);

        // -------- [2] 신호등 인식/Draw ----------
        Mat tlight_roi = frame(tlight_roi_rect);
        string signal_str;
        vector<cv::Vec3f> detected_circles;
        TrafficSignal signal = traffic_signal_detect(tlight_roi, &signal_str, &detected_circles);
        int signal_val = static_cast<int>(signal);

        rectangle(frame, tlight_roi_rect, Scalar(0, 255, 255), 2);
        draw_traffic_signals(frame, detected_circles, signal, tlight_roi_rect);

        // -------- [3] 차선 인식/Draw ----------
        Mat lane_roi = frame(lane_roi_rect);
        Mat lane_roi_mask_crop = lane_roi_mask(lane_roi_rect);
        Mat mask_lane_roi = filter_white(lane_roi);
        bitwise_and(mask_lane_roi, lane_roi_mask_crop, mask_lane_roi);

        Mat edges;
        Canny(mask_lane_roi, edges, 50, 150);
        Mat edges_full = Mat::zeros(frame.size(), CV_8U);
        edges.copyTo(edges_full(lane_roi_rect));

        vector<Point> left_pts = sliding_lane_points(edges_full, true);
        vector<Point> right_pts = sliding_lane_points(edges_full, false);

        LaneFitInfo left_info = analyze_lane(left_pts, y_top, y_bottom);
        LaneFitInfo right_info = analyze_lane(right_pts, y_top, y_bottom);

        vector<Point> left_curve, right_curve;
        if (left_info.valid) {
            for (int y = y_bottom; y >= y_top; --y) {
                int x = cvRound(left_info.poly[0] * y * y + left_info.poly[1] * y + left_info.poly[2]);
                if (x >= 0 && x < Width && lane_roi_mask.at<uchar>(y, x))
                    left_curve.emplace_back(x, y);
            }
        }
        if (right_info.valid) {
            for (int y = y_bottom; y >= y_top; --y) {
                int x = cvRound(right_info.poly[0] * y * y + right_info.poly[1] * y + right_info.poly[2]);
                if (x >= 0 && x < Width && lane_roi_mask.at<uchar>(y, x))
                    right_curve.emplace_back(x, y);
            }
        }

        rectangle(frame, lane_roi_rect, Scalar(255, 0, 255), 2);
        draw_lane_and_roi(frame, left_curve, right_curve,
                         left_info.poly, right_info.poly,
                         lane_roi_verts, lane_roi_mask, Width);

        // 두 곡선 끝점 차이 일정 이하 시 invalid 처리(이중검출 노이즈 제외)
        if (left_info.valid && right_info.valid) {
            if (abs(left_info.x_bottom - right_info.x_bottom) < 50) {
                left_info.valid = false;
                right_info.valid = false;
            }
        }

        // -------- [4] 벽에서 시작/바닥에서 시작 여부 판별 --------
        bool left_at_left_wall  = (left_info.valid && (left_info.x_bottom <= edge_margin));
        bool left_at_right_wall = (left_info.valid && (left_info.x_bottom >= Width - edge_margin));
        bool right_at_left_wall  = (right_info.valid && (right_info.x_bottom <= edge_margin));
        bool right_at_right_wall = (right_info.valid && (right_info.x_bottom >= Width - edge_margin));

        // 바닥(y_bottom)에서 시작 = x_bottom > edge_margin && x_bottom < (Width - edge_margin)
        bool left_at_bottom_center = (left_info.valid &&
                                      left_info.x_bottom > edge_margin &&
                                      left_info.x_bottom < (Width - edge_margin));
        bool right_at_bottom_center = (right_info.valid &&
                                       right_info.x_bottom > edge_margin &&
                                       right_info.x_bottom < (Width - edge_margin));

        // -------- [5] LKAS 제어 분기 -----------
        // "선 하나는 벽, 나머진 바닥 중앙에 있을 때 → 벽에 붙은 선 있는 쪽 방향으로 이동"
        if (left_info.valid && right_info.valid) {
            if ((left_at_left_wall && right_at_bottom_center) || (left_at_right_wall && right_at_bottom_center)) {
                // 왼쪽벽 or 오른쪽벽에 왼쪽선, 오른쪽선은 바닥 가운데 → 왼쪽(또는 오른쪽)선 쪽 방향
                if (left_at_left_wall) {
                    lkas = get_lkas_command_constant_left(L_FIXED_LEFT_PWM, L_FIXED_RIGHT_PWM, 45.0f); // 좌회전
                } else if (left_at_right_wall) {
                    lkas = get_lkas_command_constant_right(R_FIXED_LEFT_PWM, R_FIXED_RIGHT_PWM, -45.0f); // 우회전
                }
                direction = lkas.direction;
                offset = 0.0f;
                draw_lkas_info(frame, lkas, lkas.intervention, 20, 40, 20, direction, lkas.steering_angle);
            } else if ((right_at_right_wall && left_at_bottom_center) || (right_at_left_wall && left_at_bottom_center)) {
                if (right_at_right_wall) {
                    lkas = get_lkas_command_constant_right(R_FIXED_LEFT_PWM, R_FIXED_RIGHT_PWM, -45.0f); // 우회전
                } else if (right_at_left_wall) {
                    lkas = get_lkas_command_constant_left(L_FIXED_LEFT_PWM, L_FIXED_RIGHT_PWM, 45.0f); // 좌회전
                }
                direction = lkas.direction;
                offset = 0.0f;
                draw_lkas_info(frame, lkas, lkas.intervention, 20, 40, 20, direction, lkas.steering_angle);
            } else {
                // 기존 중앙 offset 제어 유지 (두 곡선 모두 바닥 중앙? 또는 일반 케이스)
                int lane_center = (left_info.x_bottom + right_info.x_bottom) / 2;
                int car_center = Width / 2;
                offset = static_cast<float>(lane_center - car_center);
                if (std::abs(offset) < offset_threshold) {
                    direction = 'S';
                    lkas.intervention = false;
                    lkas.steering_angle = 0.0f;
                    lkas.left_speed = 0;
                    lkas.right_speed = 0;
                } else {
                    if (offset > 0) {
                        lkas = get_lkas_command_constant_left(L_FIXED_LEFT_PWM, L_FIXED_RIGHT_PWM, 45.0f);
                    } else {
                        lkas = get_lkas_command_constant_right(R_FIXED_LEFT_PWM, R_FIXED_RIGHT_PWM, -45.0f);
                    }
                    direction = lkas.direction;
                }
                draw_lkas_info(frame, lkas, lkas.intervention, 20, 40, 20, direction, offset);
            }
        }
        // 아래 else if들은 (하나만 valid 등) 기존 분기 코드 유지
        else if (left_info.valid && !right_info.valid &&
                 (left_at_left_wall || left_at_right_wall)) {
            lkas = get_lkas_command_constant_left(L_FIXED_LEFT_PWM, L_FIXED_RIGHT_PWM, 45.0f);
            direction = lkas.direction;
            offset = 0.0f;
            draw_lkas_info(frame, lkas, lkas.intervention, 20, 40, 20, lkas.direction, lkas.steering_angle);
        }
        else if (!left_info.valid && right_info.valid &&
                 (right_at_left_wall || right_at_right_wall)) {
            lkas = get_lkas_command_constant_left(R_FIXED_LEFT_PWM, R_FIXED_RIGHT_PWM, -45.0f);
            direction = lkas.direction;
            offset = 0.0f;
            draw_lkas_info(frame, lkas, lkas.intervention, 20, 40, 20, lkas.direction, lkas.steering_angle);
        }
        else if (left_info.valid && !right_info.valid) {
            lkas = get_lkas_command_constant_right(R_FIXED_LEFT_PWM, R_FIXED_RIGHT_PWM, -45.0f);
            direction = lkas.direction;
            offset = 0.0f;
            draw_lkas_info(frame, lkas, lkas.intervention, 20, 40, 20, lkas.direction, lkas.steering_angle);

        } else if (!left_info.valid && right_info.valid) {
            lkas = get_lkas_command_constant_left(L_FIXED_LEFT_PWM, L_FIXED_RIGHT_PWM, 45.0f);
            direction = lkas.direction;
            offset = 0.0f;
            draw_lkas_info(frame, lkas, lkas.intervention, 20, 40, 20, lkas.direction, lkas.steering_angle);

        } else {
            direction = 'O';
            offset = 0.0f;
            lkas = {};
            lkas.intervention = false;
        }

        // CAN 데이터 전송 준비
        uint8_t can_data[8] = {0};
        uint8_t dir_code = 0;
        switch (direction) {
            case 'L': dir_code = 1; break;
            case 'R': dir_code = 2; break;
            case 'S': dir_code = 0; break;
            case 'O': dir_code = 0; break;
        }
        can_data[0] = lkas.intervention ? 1 : 0; // 차선 벗어났는지 여부
        can_data[1] = static_cast<uint8_t>(dir_code);
        can_data[2] = static_cast<uint8_t>(signal_val);

        printf("CAN MSG (bin): [%d %d %d]\n",
               can_data[0], can_data[1], can_data[2]);
        send_can_frame(0x123, can_data, 8);

        imshow("Lane & LKAS + Traffic Light", frame);
        if ((char)waitKey(1) == 'q') break;
    }

    close_can_socket();
    cap.release();
    destroyAllWindows();
    return 0;
}
