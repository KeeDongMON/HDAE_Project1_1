#include <opencv2/opencv.hpp>
#include <iostream>
#include <vector>
#include <numeric>

using namespace cv;
using namespace std;

// HLS 색공간에서 밝은 부분(흰색 계열)만 추출
Mat filter_white_lanes(const Mat &image) {
    Mat hls, mask;
    cvtColor(image, hls, COLOR_BGR2HLS);
    Scalar lower_white(0, 200, 0);
    Scalar upper_white(255, 255, 255);
    inRange(hls, lower_white, upper_white, mask);
    return mask;
}

// ROI 마스킹 (사다리꼴)
Mat region_of_interest(const Mat& img, const vector<Point>& vertices) {
    Mat mask = Mat::zeros(img.size(), img.type());
    vector<vector<Point>> pts = {vertices};
    fillPoly(mask, pts, Scalar(255));
    Mat masked;
    bitwise_and(img, mask, masked);
    return masked;
}

// 사다리꼴 ROI 시각화
void draw_ROI_polygon(Mat& img, const vector<Point>& vertices, Scalar color = Scalar(0,255,255), int thickness = 2) {
    for (size_t i = 0; i < vertices.size(); ++i) {
        line(img, vertices[i], vertices[(i+1) % vertices.size()], color, thickness);
    }
}

// 슬라이딩 윈도우로 차선 포인트 추출 및 polyfit 곡선 피팅
vector<Point> sliding_window_polyfit(const Mat &binary_img, bool left_lane, int nwindows=9, int margin=30, int minpix=20) {
    int height = binary_img.rows, width = binary_img.cols;
    Mat hist;
    reduce(binary_img(Range(height/2, height), Range::all()), hist, 0, REDUCE_SUM, CV_32S);

    int base;
    if (left_lane) {
        double minVal, maxVal;
        Point minLoc, maxLoc;
        minMaxLoc(hist(Range(0, width/2)), &minVal, &maxVal, &minLoc, &maxLoc);
        base = maxLoc.x;
    } else {
        double minVal, maxVal;
        Point minLoc, maxLoc;
        minMaxLoc(hist(Range(width/2, width)), &minVal, &maxVal, &minLoc, &maxLoc);
        base = maxLoc.x + width/2;
    }

    vector<Point> lane_points;
    int window_height = height / nwindows;
    int x_current = base;

    for (int window = 0; window < nwindows; ++window) {
        int win_y_low = height - (window + 1) * window_height;
        int win_y_high = height - window * window_height;
        int win_x_low = x_current - margin;
        int win_x_high = x_current + margin;

        // 바깥 경계 보정
        win_x_low = max(0, win_x_low);
        win_x_high = min(width-1, win_x_high);

        vector<Point> nonzero_points;
        for (int y = win_y_low; y < win_y_high; ++y) {
            for (int x = win_x_low; x < win_x_high; ++x) {
                if (binary_img.at<uchar>(y, x) > 0) {
                    nonzero_points.push_back(Point(x, y));
                }
            }
        }
        lane_points.insert(lane_points.end(), nonzero_points.begin(), nonzero_points.end());

        if (nonzero_points.size() > minpix) {
            // 새 윈도우 중심 보정
            int sum_x = 0;
            for (const auto& p : nonzero_points) sum_x += p.x;
            x_current = sum_x / nonzero_points.size();
        }
    }
    return lane_points;
}

// 2차 다항식 피팅 (polyfit)
// y = a*x^2 + b*x + c
Vec3f fit_quadratic_curve(const vector<Point>& pts) {
    if (pts.size() < 3) return Vec3f(0, 0, 0);
    Mat X(pts.size(), 3, CV_64F);
    Mat Y(pts.size(), 1, CV_64F);
    for (int i = 0; i < pts.size(); ++i) {
        double y = pts[i].y, x = pts[i].x;
        X.at<double>(i,0) = x*x;
        X.at<double>(i,1) = x;
        X.at<double>(i,2) = 1;
        Y.at<double>(i,0) = y;
    }
    Mat coef;
    solve(X, Y, coef, DECOMP_QR);
    return Vec3f(coef.at<double>(0), coef.at<double>(1), coef.at<double>(2));
}

// 피팅된 곡선을 그리기
void draw_polyline(Mat& img, Vec3f poly_coef, Scalar color) {
    vector<Point> curve;
    int width = img.cols;
    for (int x = 0; x < width; x += 2) {
        int y = poly_coef[0]*x*x + poly_coef[1]*x + poly_coef[2];
        if (y >= 0 && y < img.rows)
            curve.push_back(Point(x, y));
    }
    if (curve.size() > 2)
        polylines(img, curve, false, color, 5);
}

int main() {
    VideoCapture cap(0);
    if (!cap.isOpened()) {
        cerr << "Error: Could not open video stream." << endl;
        return -1;
    }
    int offset_threshold = 30;
    double prevTime = static_cast<double>(getTickCount());

    while (true) {
        Mat frame;
        bool ret = cap.read(frame);
        if (!ret) break;

        double curTime = static_cast<double>(getTickCount());
        Mat small_frame;
        resize(frame, small_frame, Size(320, 240));
        Mat white_mask = filter_white_lanes(small_frame);
        Mat edges;
        Canny(white_mask, edges, 30, 100);
        int height = edges.rows, width = edges.cols;

        // 사다리꼴 ROI
        int roi_top = static_cast<int>(height * 0.55);
        int roi_margin = static_cast<int>(width * 0.08);
        vector<Point> roi_vertices = {
            Point(roi_margin, height),
            Point(width / 2 - width * 0.18, roi_top),
            Point(width / 2 + width * 0.18, roi_top),
            Point(width - roi_margin, height)
        };

        Mat roi = region_of_interest(edges, roi_vertices);

        // 슬라이딩 윈도우 방식으로 왼쪽·오른쪽 차선 곡선 포인트 탐색
        vector<Point> left_lane_pts = sliding_window_polyfit(roi, true);
        vector<Point> right_lane_pts = sliding_window_polyfit(roi, false);

        Vec3f left_coef = fit_quadratic_curve(left_lane_pts);
        Vec3f right_coef = fit_quadratic_curve(right_lane_pts);

        Mat vis_image;
        cvtColor(roi, vis_image, COLOR_GRAY2BGR);

        if (left_lane_pts.size() < 10 && right_lane_pts.size() < 10) {
            putText(vis_image, "not detected", Point(20, 200), FONT_HERSHEY_SIMPLEX, 1, Scalar(0,0,255), 2);
        } else {
            if (left_lane_pts.size() >= 10)
                draw_polyline(vis_image, left_coef, Scalar(255,0,0));
            if (right_lane_pts.size() >= 10)
                draw_polyline(vis_image, right_coef, Scalar(0,255,0));
        }

        // ROI 영역 시각화
        draw_ROI_polygon(vis_image, roi_vertices);

        // FPS 표시
        double sec = (curTime - prevTime) / getTickFrequency();
        prevTime = curTime;
        double fps = 1.0 / sec;
        string fps_str = format("FPS : %.1f", fps);
        putText(vis_image, fps_str, Point(0,100), FONT_HERSHEY_SIMPLEX, 1, Scalar(0,255,0));

        imshow("Curve Lane Detection (Sliding Window)", vis_image);

        if ((char)waitKey(1) == 'q')
            break;
    }
    cap.release();
    destroyAllWindows();
    return 0;
}
