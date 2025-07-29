#include "color.h"
#include <opencv2/opencv.hpp>
#include <algorithm>
using namespace cv;
using namespace std;

static std::string detect_signal_color(const cv::Vec3b& hsv_pix) {
    int h = hsv_pix[0], s = hsv_pix[1], v = hsv_pix[2];
    if (((h >= 0 && h <= 10) || (h >= 170 && h <= 179)) && s > 100 && v > 100) return "Red";
    if (h >= 15 && h <= 35 && s > 100 && v > 100) return "Yellow";
    if (h >= 40 && h <= 90 && s > 50 && v > 50) return "Green";
    return "None";
}

// [중요] detected_circles 벡터(out)로 원 위치/반경 함께 반환
TrafficSignal traffic_signal_detect(const cv::Mat& image, std::string* out_str,
                                    std::vector<cv::Vec3f>* out_circles) {
    if (image.empty() || image.rows < 10) {
        if (out_str) *out_str = "No Signal";
        return TrafficSignal::NONE;
    }
    int roi_height = image.rows / 3;
    cv::Rect roi_rect(0, 0, image.cols, roi_height);
    cv::Mat roi = image(roi_rect);

    cv::Mat gray;
    cv::cvtColor(roi, gray, COLOR_BGR2GRAY);
    cv::GaussianBlur(gray, gray, Size(9, 9), 2, 2);

    std::vector<cv::Vec3f> circles;
    HoughCircles(gray, circles, HOUGH_GRADIENT, 1, gray.rows / 10, 100, 20, 5, 40);

    if (out_circles) {
        for (auto c : circles) out_circles->push_back(c);
    }

    cv::Mat hsv;
    cv::cvtColor(roi, hsv, COLOR_BGR2HSV);

    std::vector<std::string> detected_colors;

    // 기준 반지름값(픽셀 단위, 원하는 값으로 조정)
    const int MIN_RADIUS = 5;   // 예: 반지름 10픽셀 이상만 인식
    const int MAX_RADIUS = 10;

    for (const auto& c : circles) {
        cv::Point center(cvRound(c[0]), cvRound(c[1]));
        int radius = cvRound(c[2]);
	if (radius < MIN_RADIUS && radius > MAX_RADIUS) continue;
        cv::Mat mask = cv::Mat::zeros(hsv.size(), CV_8U);
        cv::circle(mask, center, radius, cv::Scalar(255), FILLED);
        cv::Scalar mean_hsv = cv::mean(hsv, mask);
        cv::Vec3b pix_val(
            static_cast<uchar>(mean_hsv[0]),
            static_cast<uchar>(mean_hsv[1]),
            static_cast<uchar>(mean_hsv[2])
        );
        std::string color = detect_signal_color(pix_val);
        if (color != "None") detected_colors.push_back(color);
    }
    if (!detected_colors.empty()) {
        int r = std::count(detected_colors.begin(), detected_colors.end(), "Red");
        int y = std::count(detected_colors.begin(), detected_colors.end(), "Yellow");
        int g = std::count(detected_colors.begin(), detected_colors.end(), "Green");
        std::string res; TrafficSignal sig;
        if (r >= y && r >= g)      { res = "Red";    sig = TrafficSignal::RED; }
        else if (y >= g)           { res = "Yellow"; sig = TrafficSignal::YELLOW; }
        else                       { res = "Green";  sig = TrafficSignal::GREEN; }
        if (out_str) *out_str = res;
        return sig;
    }
    if (out_str) *out_str = "No Signal";
    return TrafficSignal::NONE;
}
