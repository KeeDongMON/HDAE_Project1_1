#ifndef DRAW_H
#define DRAW_H

#include <opencv2/opencv.hpp>
#include <vector>
#include <string>
#include "lane_detect.h"
#include "color.h"
#include "can.h"

// 신호등 원 그리기
void draw_traffic_signals(cv::Mat& frame, const std::vector<cv::Vec3f>& detected_circles, TrafficSignal signal);

// 차선+ROI 영역 및 차선 곡선 폴리라인 그리기
void draw_lane_and_roi(cv::Mat& frame,
                       const std::vector<cv::Point>& left_curve,
                       const std::vector<cv::Point>& right_curve,
                       const cv::Vec3f& left_poly,
                       const cv::Vec3f& right_poly,
                       const std::vector<cv::Point>& roi_verts,
                       const cv::Mat& roi_mask,
                       int Width);

// LKAS 상태/속도/조향 정보 텍스트 표시
void draw_lkas_info(cv::Mat& frame, const LKASCommand& lkas, bool intervention, int x, int y0, int line_gap, char direction, int offset);

// 상단/하단 상태(신호등, FPS, 차선감지 유무) 정보 표시
void draw_status_info(cv::Mat& frame, const std::string& signal_str, double fps, bool lanes_detected, int height);

#endif // DRAW_H
