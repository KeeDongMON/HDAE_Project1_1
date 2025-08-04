#include "lane_detect.h"
#include <opencv2/opencv.hpp>
#include <cmath>

using namespace cv;
using namespace std;

Mat filter_white(const Mat& img) {
    Mat blur, hls, mask, morph;
    GaussianBlur(img, blur, Size(3, 3), 0);
    cvtColor(blur, hls, COLOR_BGR2HLS);
    inRange(hls, Scalar(0, 200, 0), Scalar(255, 255, 255), mask);
    Mat kernel = getStructuringElement(MORPH_RECT, Size(3, 3));
    morphologyEx(mask, morph, MORPH_CLOSE, kernel);
    return morph;
}

Mat get_roi_mask(const Size& sz, const vector<Point>& verts) {
    Mat mask = Mat::zeros(sz, CV_8U);
    vector<vector<Point>> pts = { verts };
    fillPoly(mask, pts, Scalar(255));
    return mask;
}

Mat region_of_interest(const Mat& img, const Mat& mask) {
    Mat res;
    bitwise_and(img, mask, res);
    return res;
}

void draw_roi(Mat& img, const vector<Point>& verts, Scalar color, int thickness) {
    for (size_t i = 0; i < verts.size(); ++i)
        line(img, verts[i], verts[(i + 1) % verts.size()], color, thickness);
}

vector<Point> sliding_lane_points(const Mat& binary_img, bool is_left, int nwindows, int margin, int minpix) {
    int h = binary_img.rows;
    int w = binary_img.cols;

    Mat hist;
    reduce(binary_img(Range(h / 2, h), Range::all()), hist, 0, REDUCE_SUM, CV_32S);

    int base;
    if (is_left) {
        double minVal, maxVal;
        Point minLoc, maxLoc;
        minMaxLoc(hist(Range::all(), Range(0, w / 2)), &minVal, &maxVal, &minLoc, &maxLoc);
        base = maxLoc.x;
    } else {
        double minVal, maxVal;
        Point minLoc, maxLoc;
        minMaxLoc(hist(Range::all(), Range(w / 2, w)), &minVal, &maxVal, &minLoc, &maxLoc);
        base = maxLoc.x + w / 2;
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

        for (const auto& p : nonzero)
            points.emplace_back(p.x + win_x_low, p.y + win_y_low);

        if ((int)nonzero.size() > minpix) {
            int sum_x = 0;
            for (const auto& p : nonzero)
                sum_x += (p.x + win_x_low);
            x_current = sum_x / static_cast<int>(nonzero.size());
        }
    }

    return points;
}

int eval_curve_x(const Vec3f& poly, int y) {
    return cvRound(poly[0] * y * y + poly[1] * y + poly[2]);
}

LaneFitInfo analyze_lane(const vector<Point>& pts, int y_top, int y_bottom) {
    LaneFitInfo info;
    info.valid = pts.size() > 25;
    info.poly = Vec3f(0, 0, 0);
    info.curvature = 0;
    info.x_top = 0;
    info.x_bottom = 0;
    if (!info.valid)
        return info;

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
    info.poly = Vec3f(coeff.at<double>(0), coeff.at<double>(1), coeff.at<double>(2));

    info.x_bottom = eval_curve_x(info.poly, y_bottom);
    info.x_top = eval_curve_x(info.poly, y_top);

    double a = info.poly[0], b = info.poly[1], y_eval = y_bottom;
    double denom = fabs(2 * a);
    if (denom < 1e-6)
        denom = 1e-6;

    info.curvature = pow(1 + pow(2 * a * y_eval + b, 2), 1.5) / denom;

    return info;
}

void draw_curve_in_roi(Mat& img, const Vec3f& poly, const Mat& roi_mask, Scalar color, int thickness) {
    vector<Point> curve_pts;
    int width = img.cols;
    int height = img.rows;

    for (int y = 0; y < height; ++y) {
        int x = cvRound(poly[0] * y * y + poly[1] * y + poly[2]);
        if (x >= 0 && x < width && roi_mask.at<uchar>(y, x) > 0)
            curve_pts.emplace_back(x, y);
    }

    if (curve_pts.size() > 2)
        polylines(img, curve_pts, false, color, thickness);
}

void fill_lane_area(Mat& img, const vector<Point>& left_curve, const vector<Point>& right_curve, Scalar color, const Mat& roi_mask) {
    if (left_curve.size() < 5 || right_curve.size() < 5) return;

    vector<Point> poly_pts;
    poly_pts.insert(poly_pts.end(), left_curve.begin(), left_curve.end());
    poly_pts.insert(poly_pts.end(), right_curve.rbegin(), right_curve.rend());

    Mat mask = Mat::zeros(img.size(), CV_8UC1);
    vector<vector<Point>> pts = { poly_pts };
    fillPoly(mask, pts, Scalar(255));
    bitwise_and(mask, roi_mask, mask);

    img.setTo(color, mask);
}
