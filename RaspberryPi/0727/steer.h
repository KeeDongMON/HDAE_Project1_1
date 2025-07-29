#ifndef STEER_H
#define STEER_H

#include <string>

// 조향 명령을 결정하는 함수
std::string getSteerCommand(
    bool has_left, bool has_right, 
    int left_x_top, int right_x_top,
    int left_x_bottom, int right_x_bottom,
    int width,
    double left_curvature, double right_curvature,
    int offset_threshold = 20,           // 좌우 offset 임계값
    int lane_offset = 80,                // 한쪽만 잡혔을때 기준 오프셋
    int curve_threshold = 30             // 상단/하단 offset 차이 커브 인식 threshold
);

#endif
