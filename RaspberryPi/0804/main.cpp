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

using namespace cv;
using namespace std;

// LKAS 제어 명령 계산 함수
LKASCommand get_lkas_command(
    int offset, int offset_threshold = 5,
    float k = 0.4f, float base_speed_percent = 100, float max_delta_percent = 50
) {
    LKASCommand cmd;
    cmd.direction = 'S';  // 기본값, 직진
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
        // 방향 할당 (왼쪽 속도가 크면 'L', 오른쪽이 크면 'R')
        if (cmd.left_speed > cmd.right_speed)
            cmd.direction = 'L';
        else if (cmd.left_speed < cmd.right_speed)
            cmd.direction = 'R';
        // 같으면 이미 'S' (직진)
    }
    return cmd;
}

const int Width = 320;
const int Height = 240;

int main() {
    if (!init_can_socket("can0")) {
        cerr << "CAN initialization failed" << endl;
        // 테스트 중단 없이 진행 가능하도록 주석 처리
        // return -1;
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

    const int offset_threshold = 5, frame_show_gap = 10;
    const float k = 0.4f, base_speed_percent = 100, max_delta_percent = 50;
    int frame_count = 0;

    while (true) {
        Mat frame;
        if (!cap.read(frame)) break;

        // 초기화
        char direction = 'S';
        float offset = 0.0f;
        LKASCommand lkas = {};

        // 신호등 감지 및 표시
        string signal_str;
        vector<cv::Vec3f> detected_circles;
        TrafficSignal signal = traffic_signal_detect(frame, &signal_str, &detected_circles);
        int signal_val = static_cast<int>(signal);

        rectangle(frame, Rect(0, 0, frame.cols, frame.rows / 3), Scalar(0,255,255), 2);
        draw_traffic_signals(frame, detected_circles, signal);

        // 차선/ROI 분석
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

        draw_lane_and_roi(frame, left_curve, right_curve,
                          left_info.poly, right_info.poly,
                          roi_verts, roi_mask, Width);
	
	if (left_info.valid && right_info.valid) {
    		if (abs(left_info.x_bottom - right_info.x_bottom) < 30) {
        		// 두 선이 실제로는 너무 가까우면 Detected/LKAS Active 금지
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

        draw_status_info(frame, signal_str, fps, lanes_detected, Height);

        if (lanes_detected) {
            int lane_center = (left_info.x_bottom + right_info.x_bottom) / 2;
            int car_center = Width / 2;
            offset = static_cast<float>(lane_center - car_center);
            lkas = get_lkas_command(static_cast<int>(offset), offset_threshold, k, base_speed_percent, max_delta_percent);
            direction = lkas.direction;

            draw_lkas_info(frame, lkas, lkas.intervention, 10, 60, 20, direction, offset);
        } else {
            // 차선 미검출시 기본값 할당
            direction = 'O';        // Not found
            offset = 0.0f;
            lkas.intervention = false;
        }
	if (!left_pts.empty() && !right_pts.empty()) {
    printf("L: [%d~%d] R: [%d~%d]\n",
       left_pts.front().x, left_pts.back().x,
       right_pts.front().x, right_pts.back().x);
}
        // CAN 메시지 스트링 생성 및 출력
        uint8_t can_data[8] = {0}; // 8바이트 고정

	// direction을 숫자로 변환: 'L'->1, 'R'->2, 'S'->3, 'O'->0
	uint8_t dir_code = 0;
	switch(direction) {
    	case 'L': dir_code = 1; break;
    	case 'R': dir_code = 2; break;
    	case 'S': dir_code = 3; break;
    	case 'O': dir_code = 0; break;
    	default:  dir_code = 0; break;
	}

	can_data[0] = lkas.intervention ? 1 : 0;
	can_data[1] = dir_code;
	can_data[2] = static_cast<uint8_t>(std::min(std::abs(offset), 255.0f)); // offset은 0~255 정수로
	can_data[3] = static_cast<uint8_t>(signal_val);
	// 나머지 바이트는 필요하면 추가, 아니면 0

	printf("CAN MSG (bin): [%d %d %d %d]\n", can_data[0], can_data[1], can_data[2], can_data[3]);

	send_can_frame(0x123, can_data, 8);
        imshow("Lane & LKAS + Traffic Light", frame);
        if ((char)waitKey(1) == 'q') break;
    }

    close_can_socket();
    cap.release();
    destroyAllWindows();
    return 0;
}
