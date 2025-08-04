#pragma once
#include <opencv2/opencv.hpp>
#include <vector>
#include <string>

enum class TrafficSignal {
    NONE,
    RED,
    YELLOW,
    GREEN
};

TrafficSignal traffic_signal_detect(const cv::Mat& image, std::string* out_str = nullptr, std::vector<cv::Vec3f>* out_circles = nullptr);
