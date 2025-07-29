#include <opencv2/opencv.hpp>
#include <vector>
#include <iostream>
#include <cmath>
#include <cstdio>

// SocketCAN 헤더
#include <linux/can.h>
#include <linux/can/raw.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <net/if.h>
#include <cstring>
#include <unistd.h>
#include <sys/ioctl.h>

#include "lane_detect.h"

using namespace cv;
using namespace std;

// --- LKAS 명령 구조체 ---
struct LKASCommand {
    bool intervention;
    float steering_angle;
    float left_speed;
    float right_speed;
};

LKASCommand get_lkas_command(
    int offset, int offset_threshold = 5,
    float k = 0.4f, float base_speed_percent = 100, float max_delta_percent = 50
) {
    LKASCommand cmd;
    if (std::abs(offset) < offset_threshold) {
        cmd.intervention = false;
        cmd.steering_angle = 0.0f;
        cmd.left_speed = base_speed_percent / 2.0f;
        cmd.right_speed = base_speed_percent / 2.0f;
    } else {
        cmd.intervention = true;
        cmd.steering_angle = k * offset;
        float delta = std::max(std::min(k * offset, max_delta_percent), -max_delta_percent);
        float left_pct = (base_speed_percent / 2.0f) - delta / 2.0f;
        float right_pct = (base_speed_percent / 2.0f) + delta / 2.0f;
        float scale = base_speed_percent / (left_pct + right_pct);
        cmd.left_speed = left_pct * scale;
        cmd.right_speed = right_pct * scale;
        cmd.left_speed = std::clamp(cmd.left_speed, 0.0f, 100.0f);
        cmd.right_speed = std::clamp(cmd.right_speed, 0.0f, 100.0f);
    }
    return cmd;
}

// --- CAN 송신 함수 및 전역 변수 ---
int can_socket = -1;

bool init_can_socket(const char* ifname = "can0") {
    struct ifreq ifr;
    struct sockaddr_can addr;

    can_socket = socket(PF_CAN, SOCK_RAW, CAN_RAW);
    if (can_socket < 0) {
        perror("CAN socket open error");
        return false;
    }
    strcpy(ifr.ifr_name, ifname);
    if (ioctl(can_socket, SIOCGIFINDEX, &ifr) < 0) {
        perror("CAN ioctl error");
        close(can_socket);
        can_socket = -1;
        return false;
    }
    addr.can_family = AF_CAN;
    addr.can_ifindex = ifr.ifr_ifindex;
    if (bind(can_socket, (struct sockaddr *)&addr, sizeof(addr)) < 0) {
        perror("CAN bind error");
        close(can_socket);
        can_socket = -1;
        return false;
    }
    return true;
}

bool send_to_can(const LKASCommand& cmd) {
    if (can_socket < 0) return false;
    struct can_frame frame;
    frame.can_id = 0x123; // 예시 CAN ID
    frame.can_dlc = 8;
    frame.data[0] = cmd.intervention ? 1 : 0;
    int16_t angle_scaled = static_cast<int16_t>(cmd.steering_angle * 100);
    uint16_t left_scaled = static_cast<uint16_t>(cmd.left_speed * 100);
    uint16_t right_scaled = static_cast<uint16_t>(cmd.right_speed * 100);
    memcpy(&frame.data[1], &angle_scaled, sizeof(int16_t));
    memcpy(&frame.data[3], &left_scaled, sizeof(uint16_t));
    memcpy(&frame.data[5], &right_scaled, sizeof(uint16_t));
    frame.data[7] = 0;
    int nbytes = write(can_socket, &frame, sizeof(struct can_frame));
    return (nbytes == sizeof(struct can_frame));
}

// --- 메인 루프 및 차선검출 최적화 ---
const int Width = 320;
const int Height = 240;

int main() {
    if (!init_can_socket("can0")) {
        cerr << "CAN initialization failed" << endl;
    }

    VideoCapture cap(0);
    cap.set(CAP_PROP_FRAME_WIDTH, Width);
    cap.set(CAP_PROP_FRAME_HEIGHT, Height);
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
    Rect roi_box = boundingRect(roi_verts);

    double last_time = getTickCount();
    int y_bottom = Height - 1;
    int y_top = static_cast<int>(Height * 0.62);

    const int offset_threshold = 5;
    const float k = 0.4f;
    const float base_speed_percent = 100;
    const float max_delta_percent = 50;

    int frame_count = 0;

    while (true) {
        double t0 = getTickCount(); // 전체 시작

        Mat frame;
        if (!cap.read(frame)) break;

        //resize(frame, frame, Size(Width, Height));

        double t1 = getTickCount(); // after resize

        // ROI만 잘라서 필터링
        Mat frame_roi = frame(roi_box);
        Mat roi_mask_crop = roi_mask(roi_box);

        Mat mask_roi = filter_white(frame_roi);

        double t2 = getTickCount(); // after filter_white

        // ROI 마스크와 AND 연산
        bitwise_and(mask_roi, roi_mask_crop, mask_roi);

        // Canny ROI 내 에지 검출
        Mat edges;
        Canny(mask_roi, edges, 50, 150);

        double t3 = getTickCount(); // after Canny+bitwise

        // 전체 영상 크기로 에지 이미지 생성 후 ROI 부분 복사
        Mat edges_full = Mat::zeros(frame.size(), CV_8U);
        edges.copyTo(edges_full(roi_box));

        double t4 = getTickCount(); // after edges_full

        // 좌/우 차선 후보 추출 (윈도우 수 10으로)
        vector<Point> left_pts = sliding_lane_points(edges_full, true, 10, 32, 15);
        vector<Point> right_pts = sliding_lane_points(edges_full, false, 10, 32, 15);

        double t5 = getTickCount(); // after sliding_lane_points

        LaneFitInfo left_info = analyze_lane(left_pts, y_top, y_bottom);
        LaneFitInfo right_info = analyze_lane(right_pts, y_top, y_bottom);

        double t6 = getTickCount(); // after analyze_lane

        Mat disp = frame;
        vector<Point> left_curve, right_curve;

        if (left_info.valid) {
            for (int y = y_bottom; y >= y_top; --y) {
                int x = cvRound(left_info.poly[0]*y*y + left_info.poly[1]*y + left_info.poly[2]);
                if (x >=0 && x < Width && roi_mask.at<uchar>(y,x))
                    left_curve.emplace_back(x, y);
            }
        }
        if (right_info.valid) {
            for (int y = y_bottom; y >= y_top; --y) {
                int x = cvRound(right_info.poly[0]*y*y + right_info.poly[1]*y + right_info.poly[2]);
                if (x >=0 && x < Width && roi_mask.at<uchar>(y,x))
                    right_curve.emplace_back(x, y);
            }
        }

        if (left_curve.size() > 5 && right_curve.size() > 5)
            fill_lane_area(disp, left_curve, right_curve, Scalar(0,255,0), roi_mask);

        draw_roi(disp, roi_verts, Scalar(0,255,255), 2);

        if (left_info.valid)
            draw_curve_in_roi(disp, left_info.poly, roi_mask, Scalar(255,0,0), 3);
        if (right_info.valid)
            draw_curve_in_roi(disp, right_info.poly, roi_mask, Scalar(0,255,0), 3);

        LKASCommand lkas = {};
        bool lanes_detected = (left_info.valid && right_info.valid);

        int x = 10, y0 = 60, line_gap = 20;
        frame_count++;

        double current_time = getTickCount();
        double elapsed_sec = (current_time - last_time) / getTickFrequency();
        last_time = current_time;
        double fps = 1.0 / elapsed_sec;

        if (lanes_detected) {
            int lane_center = (left_info.x_bottom + right_info.x_bottom) / 2;
            int car_center = Width / 2;
            int offset = lane_center - car_center;

            lkas = get_lkas_command(offset, offset_threshold, k, base_speed_percent, max_delta_percent);

            if (can_socket >=0) {
                if (!send_to_can(lkas)) cerr << "CAN send failed" << endl;
            }
            if (can_socket<0 || frame_count%10==0) {
                printf("FPS: %.2f | LKAS: %d Angle: %.1f L: %.1f R: %.1f\n",
                       fps, lkas.intervention?1:0, lkas.steering_angle, lkas.left_speed, lkas.right_speed);
            }
            if (lkas.intervention) {
                putText(disp, "LKAS ACTIVE", Point(x,y0), FONT_HERSHEY_SIMPLEX, 0.5, Scalar(0,255,255), 1);
                char angle_buf[64], speed_buf[64];
                sprintf(angle_buf, "angle: %.1f deg", lkas.steering_angle);
                sprintf(speed_buf, "L: %.1f R: %.1f", lkas.left_speed, lkas.right_speed);
                putText(disp, angle_buf, Point(x,y0+line_gap), FONT_HERSHEY_SIMPLEX, 0.5, Scalar(0,255,0), 1);
                putText(disp, speed_buf, Point(x,y0+2*line_gap), FONT_HERSHEY_SIMPLEX, 0.5, Scalar(0,200,255), 1);
            } else {
                putText(disp, "LKAS SLEEP", Point(x,y0), FONT_HERSHEY_SIMPLEX, 0.5, Scalar(100,255,100), 1);
                putText(disp, "(Keep Lane)", Point(x,y0+line_gap), FONT_HERSHEY_SIMPLEX, 0.5, Scalar(100,255,100), 1);
            }
        } else {
            putText(disp, "not detected", Point(20, Height-20), FONT_HERSHEY_SIMPLEX, 0.6, Scalar(0,0,255), 2);
            if (can_socket<0 || frame_count%10 == 0) {
                printf("FPS: %.2f | LKAS: not detected\n", fps);
            }
        }

        char fps_text[32];
        sprintf(fps_text, "FPS: %.2f", fps);
        putText(disp, fps_text, Point(20,20), FONT_HERSHEY_SIMPLEX, 0.5, Scalar(0,255,0), 2);

        // ---- 타이밍 출력(10프레임마다 출력) ----
        if (frame_count % 10 == 0) {
            double t_resize = (t1 - t0) * 1000 / getTickFrequency();
            double t_filter = (t2 - t1) * 1000 / getTickFrequency();
            double t_canny = (t3 - t2) * 1000 / getTickFrequency();
            double t_edges_full = (t4 - t3) * 1000 / getTickFrequency();
            double t_sliding = (t5 - t4) * 1000 / getTickFrequency();
            double t_fit = (t6 - t5) * 1000 / getTickFrequency();

            printf("[TIME(ms)] resize: %.2f | filter_white: %.2f | canny+mask: %.2f | edges_full: %.2f | sliding: %.2f | fit: %.2f | FPS: %.2f\n",
                t_resize, t_filter, t_canny, t_edges_full, t_sliding, t_fit, fps);
        }

        imshow("Lane & LKAS", disp);
        if ((char)waitKey(1) == 'q') break;
    }

    if (can_socket>=0) close(can_socket);
    cap.release();
    destroyAllWindows();
    return 0;
}
