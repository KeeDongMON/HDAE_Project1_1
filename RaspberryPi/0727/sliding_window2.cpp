#include <opencv2/opencv.hpp>
#include <vector>
#include <numeric>
#include <iostream>

using namespace cv;
using namespace std;

const int Width = 320;   // 해상도 축소
const int Height = 240;

Mat filter_white(const Mat& img) {
    Mat blur, hls, mask, morph;
    GaussianBlur(img, blur, Size(3, 3), 0);
    cvtColor(blur, hls, COLOR_BGR2HLS);
    inRange(hls, Scalar(0, 200, 0), Scalar(255, 255, 255), mask);
    Mat kernel = getStructuringElement(MORPH_RECT, Size(3, 3));
    morphologyEx(mask, morph, MORPH_CLOSE, kernel);
    return morph;
}
Mat get_roi_mask(const Size& sz, const std::vector<Point>& verts) {
    Mat mask = Mat::zeros(sz, CV_8U);
    std::vector<std::vector<Point>> pts = { verts };
    fillPoly(mask, pts, Scalar(255));
    return mask;
}
Mat region_of_interest(const Mat& img, const Mat& mask) {
    Mat res;
    bitwise_and(img, mask, res);
    return res;
}
void draw_roi(Mat& img, const std::vector<Point>& verts, Scalar color = Scalar(0,255,255), int thickness = 2) {
    for (size_t i = 0; i < verts.size(); ++i)
        line(img, verts[i], verts[(i+1)%verts.size()], color, thickness);
}
vector<Point> sliding_lane_points(const Mat& binary_img, bool is_left, int nwindows=15, int margin=32, int minpix=15) {
    int h = binary_img.rows;
    int w = binary_img.cols;
    Mat hist;
    reduce(binary_img(Range(h/2, h), Range::all()), hist, 0, REDUCE_SUM, CV_32S);

    int base;
    if (is_left) {
        double minVal, maxVal; Point minLoc, maxLoc;
        minMaxLoc(hist(Range::all(), Range(0, w/2)), &minVal, &maxVal, &minLoc, &maxLoc);
        base = maxLoc.x;
    } else {
        double minVal, maxVal; Point minLoc, maxLoc;
        minMaxLoc(hist(Range::all(), Range(w/2, w)), &minVal, &maxVal, &minLoc, &maxLoc);
        base = maxLoc.x + w/2;
    }

    vector<Point> points;
    int window_height = h / nwindows;
    int x_current = base;

    for (int window = 0; window < nwindows; ++window) {
        int win_y_low = h - (window + 1) * window_height;
        int win_y_high = h - window * window_height;
        int win_x_low = max(x_current - margin, 0);
        int win_x_high = min(x_current + margin, w);

        Rect win_rect(Point(win_x_low, win_y_low), Point(win_x_high, win_y_high));
        Mat window_img = binary_img(win_rect);

        vector<Point> nonzero;
        findNonZero(window_img, nonzero);
        for (auto& p : nonzero)
            points.emplace_back(p.x + win_x_low, p.y + win_y_low);

        if (nonzero.size() > minpix) {
            int sum_x = 0;
            for (auto& p : nonzero)
                sum_x += (p.x + win_x_low);
            x_current = sum_x / static_cast<int>(nonzero.size());
        }
    }
    return points;
}
Vec3f fit_quad_curve(const std::vector<Point>& pts) {
    if (pts.size() < 3)
        return Vec3f(0, 0, 0);
    Mat X(pts.size(), 3, CV_64F);
    Mat Y(pts.size(), 1, CV_64F);

    for (size_t i = 0; i < pts.size(); ++i) {
        double y = pts[i].y;
        X.at<double>(i, 0) = y * y;
        X.at<double>(i, 1) = y;
        X.at<double>(i, 2) = 1;
        Y.at<double>(i, 0) = pts[i].x;
    }
    Mat coeff;
    solve(X, Y, coeff, DECOMP_QR);
    return Vec3f(coeff.at<double>(0), coeff.at<double>(1), coeff.at<double>(2));
}

void draw_curve_in_roi(Mat& img, const Vec3f& poly, const Mat& roi_mask, Scalar color, int thickness=4) {
    vector<Point> curve_pts;
    int width = img.cols, height = img.rows;
    for (int y = 0; y < height; ++y) {
        int x = cvRound(poly[0]*y*y + poly[1]*y + poly[2]);
        if (x >= 0 && x < width && roi_mask.at<uchar>(y, x) > 0)
            curve_pts.emplace_back(x, y);
    }
    if (curve_pts.size() > 2)
        polylines(img, curve_pts, false, color, thickness);
}

// 곡선 좌/우 차선 사이 영역을 색 채워넣기
void fill_lane_area(Mat& img, const vector<Point>& left_curve, const vector<Point>& right_curve, Scalar color, const Mat& roi_mask) {
    if (left_curve.size() < 5 || right_curve.size() < 5) return;
    vector<Point> poly_pts;
    // 아래 y에서 위로 left, 위에서 아래로 right 순서로 polygon 닫힘
    poly_pts.insert(poly_pts.end(), left_curve.begin(), left_curve.end());
    poly_pts.insert(poly_pts.end(), right_curve.rbegin(), right_curve.rend());
    // ROI와 연산
    Mat mask = Mat::zeros(img.size(), CV_8UC1);
    vector<vector<Point>> pts = { poly_pts };
    fillPoly(mask, pts, Scalar(255));
    bitwise_and(mask, roi_mask, mask); // ROI 안에서만
    img.setTo(color, mask);
}

void fill_central_area(Mat& img, int left_end, int right_end, int y_bottom, int y_top, Scalar color, const Mat& roi_mask) {
    vector<Point> central_pts = {
        Point(left_end, y_bottom),
        Point(left_end, y_top),
        Point(right_end, y_top),
        Point(right_end, y_bottom)
    };
    Mat mask = Mat::zeros(img.size(), CV_8UC1);
    vector<vector<Point>> pts = { central_pts };
    fillPoly(mask, pts, Scalar(255));
    bitwise_and(mask, roi_mask, mask); // ROI 안에서만
    img.setTo(color, mask);
}

string getSteerCommand(bool has_left, bool has_right, int left_x, int right_x, int width, int threshold=0, int lane_offset=80) {
    int car_center = width / 2;
    int lane_center;
    int offset;
    if (has_left && has_right) {
        lane_center = (left_x + right_x) / 2;
        offset = car_center - lane_center;
        if (offset > threshold)      return "LEFT";
        else if (offset < -threshold) return "RIGHT";
        else return "OK";
    } else if (has_left) {
        lane_center = left_x + lane_offset;
        offset = car_center - lane_center;
        if (offset > 0) return "LEFT";
        else return "OK";
    } else if (has_right) {
        lane_center = right_x - lane_offset;
        offset = car_center - lane_center;
        if (offset < 0) return "RIGHT";
        else return "OK";
    } else {
        return "not detected";
    }
}

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

    while (true) {
        Mat frame, disp;
        if (!cap.read(frame)) break;
        resize(frame, frame, Size(Width, Height));
        disp = frame.clone();

        Mat mask = filter_white(frame);
        Mat edges; Canny(mask, edges, 50, 150);
        Mat roi = region_of_interest(edges, roi_mask);

        vector<Point> left_pts = sliding_lane_points(roi, true);
        vector<Point> right_pts = sliding_lane_points(roi, false);

        Vec3f left_poly = fit_quad_curve(left_pts);
        Vec3f right_poly = fit_quad_curve(right_pts);

        // --- 곡선상의 (x, y) 추출
        vector<Point> left_curve, right_curve;
        for (int y = Height-1; y >= 0; --y) {
            if (left_pts.size() > 10) {
                int x = cvRound(left_poly[0]*y*y + left_poly[1]*y + left_poly[2]);
                if (x >= 0 && x < Width && roi_mask.at<uchar>(y, x) > 0)
                    left_curve.emplace_back(x, y);
            }
            if (right_pts.size() > 10) {
                int x = cvRound(right_poly[0]*y*y + right_poly[1]*y + right_poly[2]);
                if (x >= 0 && x < Width && roi_mask.at<uchar>(y, x) > 0)
                    right_curve.emplace_back(x, y);
            }
        }

        // --- lane 영역 채우기(초록색)
        if (left_curve.size() > 5 && right_curve.size() > 5)
            fill_lane_area(disp, left_curve, right_curve, Scalar(0,255,0), roi_mask);

        // --- 가운데 영역(노란색; 한쪽 차선 또는 모두 없을 때)
        int lane_y_bottom = Height-1;
        int lane_y_top = Height*0.62;
        if (left_curve.size() < 5 && right_curve.size() < 5) {
            // 전혀 검출된 차선 없을 때: ROI 중심 부근 지정
            int band = 45;
            int cx = Width/2;
            fill_central_area(disp, cx-band, cx+band, lane_y_bottom, lane_y_top, Scalar(0,255,255), roi_mask);
        } else if (left_curve.size() < 5 && right_curve.size() > 5) {
            // 오른쪽만 검출: 오른쪽 차선에서 일정 오프셋만 중앙 가정
            int rx = right_curve.front().x;
            fill_central_area(disp, rx-90, rx, lane_y_bottom, lane_y_top, Scalar(0,255,255), roi_mask);
        } else if (right_curve.size() < 5 && left_curve.size() > 5) {
            int lx = left_curve.front().x;
            fill_central_area(disp, lx, lx+90, lane_y_bottom, lane_y_top, Scalar(0,255,255), roi_mask);
        }

        draw_roi(disp, roi_verts, Scalar(0,255,255), 2);

        bool has_left = (left_pts.size() > 10), has_right = (right_pts.size() > 10);

        if (has_left)
            draw_curve_in_roi(disp, left_poly, roi_mask, Scalar(255, 0, 0), 3);
        if (has_right)
            draw_curve_in_roi(disp, right_poly, roi_mask, Scalar(0, 255, 0), 3);

        // 조향 판단 및 시각화
        int left_x = 0, right_x = Width;
        if (has_left) {
            vector<int> left_xs;
            for (auto& p : left_pts) if (p.y > Height - 10) left_xs.push_back(p.x);
            if (!left_xs.empty()) left_x = left_xs[0];
        }
        if (has_right) {
            vector<int> right_xs;
            for (auto& p : right_pts) if (p.y > Height - 10) right_xs.push_back(p.x);
            if (!right_xs.empty()) right_x = right_xs[0];
        }
        string steer_command = getSteerCommand(has_left, has_right, left_x, right_x, Width);

        putText(disp, "STEER: " + steer_command, Point(20, 80), FONT_HERSHEY_SIMPLEX, 1.0, Scalar(0,255,255), 2);

        if (steer_command == "LEFT")
            putText(disp, "Turn LEFT!", Point(20, Height - 20), FONT_HERSHEY_SIMPLEX, 1.0, Scalar(0, 0, 255), 2);
        else if (steer_command == "RIGHT")
            putText(disp, "Turn RIGHT!", Point(20, Height - 20), FONT_HERSHEY_SIMPLEX, 1.0, Scalar(0, 0, 255), 2);
        else if (steer_command == "not detected")
            putText(disp, "not detected", Point(20, Height - 20), FONT_HERSHEY_SIMPLEX, 1.0, Scalar(0, 0, 255), 2);

        putText(disp, "LKAS: " + steer_command, Point(20, 40), FONT_HERSHEY_SIMPLEX, 1.0, Scalar(255,255,0), 2);

        // FPS 계산 및 출력
        double current_time = getTickCount();
        double elapsed_sec = (current_time - last_time) / getTickFrequency();
        last_time = current_time;
        double fps = 1.0 / elapsed_sec;
        char fps_text[32];
        sprintf(fps_text, "FPS: %.2f", fps);
        putText(disp, fps_text, Point(20, 120), FONT_HERSHEY_SIMPLEX, 1.0, Scalar(0,255,0), 2);

        imshow("Lane & Steering Assist", disp);
        if ((char)waitKey(1) == 'q')
            break;
    }
    cap.release();
    destroyAllWindows();
    return 0;
}
