#include <opencv2/opencv.hpp>
#include <vector>
#include <iostream>
#include "lane_detect.h"
#include "steer.h"

using namespace cv;
using namespace std;

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
    int y_bottom = Height-1;
    int y_top = static_cast<int>(Height*0.62);

    while (true) {
        Mat frame, disp;
        if (!cap.read(frame)) break;
        resize(frame, frame, Size(Width, Height));
        disp = frame.clone();

        Mat mask = filter_white(frame);
        Mat edges;
        Canny(mask, edges, 50, 150);
        Mat roi = region_of_interest(edges, roi_mask);

        // --- 차선 포인트 추출 및 분석 ---
        vector<Point> left_pts = sliding_lane_points(roi, true);
        vector<Point> right_pts = sliding_lane_points(roi, false);

        LaneFitInfo left_info  = analyze_lane(left_pts, y_top, y_bottom);
        LaneFitInfo right_info = analyze_lane(right_pts, y_top, y_bottom);

        // 시각화용 곡선 출력
        vector<Point> left_curve, right_curve;
        if (left_info.valid) {
            for (int y = y_bottom; y >= y_top; --y) {
                int x = cvRound(left_info.poly[0]*y*y + left_info.poly[1]*y + left_info.poly[2]);
                if (x >= 0 && x < Width && roi_mask.at<uchar>(y, x) > 0)
                    left_curve.emplace_back(x, y);
            }
        }
        if (right_info.valid) {
            for (int y = y_bottom; y >= y_top; --y) {
                int x = cvRound(right_info.poly[0]*y*y + right_info.poly[1]*y + right_info.poly[2]);
                if (x >= 0 && x < Width && roi_mask.at<uchar>(y, x) > 0)
                    right_curve.emplace_back(x, y);
            }
        }

        // 오직 양쪽 모두 있을 때만 초록색 fill
        if (left_curve.size() > 5 && right_curve.size() > 5)
            fill_lane_area(disp, left_curve, right_curve, Scalar(0,255,0), roi_mask);

        draw_roi(disp, roi_verts, Scalar(0,255,255), 2);

        if (left_info.valid)
            draw_curve_in_roi(disp, left_info.poly, roi_mask, Scalar(255, 0, 0), 3);
        if (right_info.valid)
            draw_curve_in_roi(disp, right_info.poly, roi_mask, Scalar(0, 255, 0), 3);

        // ---- 조향 판단 및 시각화 ----
        string steer_command = getSteerCommand(
            left_info.valid, right_info.valid,
            left_info.x_top, right_info.x_top,
            left_info.x_bottom, right_info.x_bottom,
            Width,
            left_info.curvature, right_info.curvature
        );

        putText(disp, "STEER: " + steer_command, Point(20, 80), FONT_HERSHEY_SIMPLEX, 1.0, Scalar(0,255,255), 2);

        if (steer_command.find("LEFT") != string::npos)
            putText(disp, "Turn LEFT!", Point(20, Height - 20), FONT_HERSHEY_SIMPLEX, 1.0, Scalar(0,0,255), 2);
        else if (steer_command.find("RIGHT") != string::npos)
            putText(disp, "Turn RIGHT!", Point(20, Height - 20), FONT_HERSHEY_SIMPLEX, 1.0, Scalar(0,0,255), 2);
        else if (steer_command == "not detected")
            putText(disp, "not detected", Point(20, Height - 20), FONT_HERSHEY_SIMPLEX, 1.0, Scalar(0,0,255), 2);

        putText(disp, "LKAS: " + steer_command, Point(20, 40), FONT_HERSHEY_SIMPLEX, 1.0, Scalar(255,255,0), 2);

        double current_time = getTickCount();
        double elapsed_sec = (current_time - last_time) / getTickFrequency();
        last_time = current_time;
        double fps = 1.0 / elapsed_sec;
        char fps_text[32];
        sprintf(fps_text, "FPS: %.2f", fps);
        putText(disp, fps_text, Point(20, 120), FONT_HERSHEY_SIMPLEX, 1.0, Scalar(0,255,0), 2);

        imshow("Lane & Steering Assist", disp);
        if ((char)waitKey(1) == 'q') break;
    }
    cap.release();
    destroyAllWindows();
    return 0;
}
