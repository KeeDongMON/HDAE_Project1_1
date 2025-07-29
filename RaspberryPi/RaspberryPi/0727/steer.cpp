#include "steer.h"
#include <cmath>
#include <string>
using namespace std;

// ROI 위/아래 차선 중앙 좌표, 곡률 받아서 조향 명령 판단
string getSteerCommand(
    bool has_left, bool has_right, 
    int left_x_top, int right_x_top,
    int left_x_bottom, int right_x_bottom,
    int width,
    double left_curvature, double right_curvature,
    int offset_threshold,
    int lane_offset,
    int curve_threshold
) {
    // 선이 하나 이하로 인식되면 무조건 not detected!
    if (!(has_left && has_right))
        return "not detected";

    int car_center = width / 2;

    // 하단(차 가까이)과 상단(전방) 기준 차선 중앙, offset 계산
    int lane_center_bottom = (left_x_bottom + right_x_bottom) / 2;
    int offset_bottom = car_center - lane_center_bottom;

    int lane_center_top = (left_x_top + right_x_top) / 2;
    int offset_top = car_center - lane_center_top;

    int offset_diff = std::abs(offset_top - offset_bottom);

    // 커브 구간에서 추가 분기 (상·하단 offset 차이가 큰 경우)
    if (offset_diff > curve_threshold) {
        if (offset_top > offset_bottom)        return "LEFT(CURVE)";
        else if (offset_top < offset_bottom)   return "RIGHT(CURVE)";
    }

    // 일반적 오프셋 기준 판단
    if (offset_bottom > offset_threshold)         return "LEFT";
    else if (offset_bottom < -offset_threshold)   return "RIGHT";
    else                                         return "OK"; // 직진
}
