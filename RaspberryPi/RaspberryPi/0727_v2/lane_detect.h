#ifndef LANE_DETECT_H
#define LANE_DETECT_H

#include <opencv2/opencv.hpp>
#include <vector>

// 차선 데이터 구조체
struct LaneFitInfo {
    bool valid;
    cv::Vec3f poly;       // 2차 방정식 계수 (a, b, c)
    double curvature;     // 곡률
    int x_top, x_bottom;  // ROI 내 위/아래 y에서 차선의 x좌표
};

cv::Mat filter_white(const cv::Mat& img);
cv::Mat get_roi_mask(const cv::Size& sz, const std::vector<cv::Point>& verts);
cv::Mat region_of_interest(const cv::Mat& img, const cv::Mat& mask);
void draw_roi(cv::Mat& img, const std::vector<cv::Point>& verts, cv::Scalar color = cv::Scalar(0,255,255), int thickness = 2);
std::vector<cv::Point> sliding_lane_points(const cv::Mat& binary_img, bool is_left, int nwindows=15, int margin=32, int minpix=15);
LaneFitInfo analyze_lane(const std::vector<cv::Point>& pts, int y_top, int y_bottom);
void draw_curve_in_roi(cv::Mat& img, const cv::Vec3f& poly, const cv::Mat& roi_mask, cv::Scalar color, int thickness=4);
void fill_lane_area(cv::Mat& img, const std::vector<cv::Point>& left_curve, const std::vector<cv::Point>& right_curve, cv::Scalar color, const cv::Mat& roi_mask);

#endif
