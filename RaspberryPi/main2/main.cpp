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
        // return -1;  // 테스트 연속 진행 위한 주석 처리
    }

    VideoCapture cap(0);
    cap.set(CAP_PROP_FRAME_WIDTH, Width);
    cap.set(CAP_PROP_FRAME_HEIGHT, Height);
    if (!cap.isOpened()) {
        cerr << "Camera open failed!" << endl;
        return -1;
    }
    PIDController pid(0.4f, 0.0f, 0.1f);

    vector<Point> roi_verts = {
        Point(Width * 0.18, Height * 0.62),
        Point(Width * 0.05, Height * 0.98),
        Point(Width * 0.95, Height * 0.98),
        Point(Width * 0.82, Height * 0.62)
    };
    Mat roi_mask = get_roi_mask(Size(Width, Height), roi_verts);
    Rect roi_box = boundingRect(roi_verts);

    int y_bottom = Height - 1;
    int y_top = static_cast<int>(Height * 0.62);

    const int offset_threshold = 5;
    const int MAX_PWM = 150;

    double last_time = getTickCount();
    int frame_count = 0;

    while (true) {
        Mat frame;
        if (!cap.read(frame)) break;

        char direction = 'S';
        float offset = 0.0f;
        LKASCommand lkas = {};

        string signal_str;
        vector<cv::Vec3f> detected_circles;
        TrafficSignal signal = traffic_signal_detect(frame, &signal_str, &detected_circles);
        int signal_val = static_cast<int>(signal);

        rectangle(frame, Rect(0, 0, frame.cols, frame.rows / 3), Scalar(0, 255, 255), 2);
        draw_traffic_signals(frame, detected_circles, signal);

        Mat frame_roi = frame(roi_box);
        Mat roi_mask_crop = roi_mask(roi_box);
        Mat mask_roi = filter_white(frame_roi);
        bitwise_and(mask_roi, roi_mask_crop, mask_roi);

        Mat edges;
        Canny(mask_roi, edges, 50, 150);
        Mat edges_full = Mat::zeros(frame.size(), CV_8U);
        edges.copyTo(edges_full(roi_box));

        vector<Point> left_pts = sliding_lane_points(edges_full, true);
        vector<Point> right_pts = sliding_lane_points(edges_full, false);

        LaneFitInfo left_info = analyze_lane(left_pts, y_top, y_bottom);
        LaneFitInfo right_info = analyze_lane(right_pts, y_top, y_bottom);

        vector<Point> left_curve, right_curve;
        if (left_info.valid) {
            for (int y = y_bottom; y >= y_top; --y) {
                int x = cvRound(left_info.poly[0] * y * y + left_info.poly[1] * y + left_info.poly[2]);
                if (x >= 0 && x < Width && roi_mask.at<uchar>(y, x))
                    left_curve.emplace_back(x, y);
            }
        }
        if (right_info.valid) {
            for (int y = y_bottom; y >= y_top; --y) {
                int x = cvRound(right_info.poly[0] * y * y + right_info.poly[1] * y + right_info.poly[2]);
                if (x >= 0 && x < Width && roi_mask.at<uchar>(y, x))
                    right_curve.emplace_back(x, y);
            }
        }

        draw_lane_and_roi(frame, left_curve, right_curve,
                          left_info.poly, right_info.poly,
                          roi_verts, roi_mask, Width);

        if (left_info.valid && right_info.valid) {
            if (abs(left_info.x_bottom - right_info.x_bottom) < 30) {
                left_info.valid = false;
                right_info.valid = false;
            }
        }

        bool lanes_detected = (left_info.valid && right_info.valid);
        frame_count++;

        double current_time = getTickCount();
        double elapsed_sec = (current_time - last_time) / getTickFrequency();
        last_time = current_time;
        double fps = 1.0 / elapsed_sec;

        draw_fps_info(frame, fps, Height);

        if (lanes_detected) {
            int lane_center = (left_info.x_bottom + right_info.x_bottom) / 2;
            int car_center = Width / 2;
            offset = static_cast<float>(lane_center - car_center);

            lkas = get_lkas_command_pid(offset, pid, 65.0f, 0.117f, 0.135f, MAX_PWM, offset_threshold);
            direction = lkas.direction;

            draw_lkas_info(frame, lkas, lkas.intervention, 20, 40, 20, direction, offset);
        } else {
            direction = 'O';
            offset = 0.0f;
            lkas.intervention = false;
        }

        uint8_t can_data[8] = {0};

        // direction 숫자 코드 ('L'->1, 'R'->2, 'S'->3, 'O'->0)
        uint8_t dir_code = 0;
        switch (direction) {
            case 'L': dir_code = 1; break;
            case 'R': dir_code = 2; break;
            case 'S': dir_code = 3; break;
            case 'O': dir_code = 0; break;
        }

        can_data[0] = lkas.intervention ? 1 : 0;
        can_data[1] = static_cast<uint8_t>(lkas.right_speed);
        can_data[2] = static_cast<uint8_t>(lkas.left_speed);
        can_data[3] = static_cast<uint8_t>(std::min(std::abs(offset), 255.0f));
        can_data[4] = static_cast<uint8_t>(signal_val);
        

        printf("CAN MSG (bin): [%d %d %d %d %d]\n",
                can_data[0], can_data[1], can_data[2], can_data[3], can_data[4]);

        send_can_frame(0x123, can_data, 8);

        imshow("Lane & LKAS + Traffic Light", frame);
        if ((char)waitKey(1) == 'q') break;
    }

    close_can_socket();
    cap.release();
    destroyAllWindows();
    return 0;
}
