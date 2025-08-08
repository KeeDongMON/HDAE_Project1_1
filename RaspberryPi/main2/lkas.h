#pragma once

#include <cmath>
#include <algorithm>
#include <opencv2/core.hpp>

extern const int Width;
extern const int Height;

struct LKASCommand {
    bool intervention;
    float steering_angle;  // degree 단위
    float left_speed;      // PWM 또는 속도 값
    float right_speed;
    char direction;        // 'L' (좌회전), 'R' (우회전), 'S' (직진), 'O' (없음)
};

inline LKASCommand get_lkas_command_constant_left(
    int left_pwm, int right_pwm,
    float steering_angle_deg = -45.0f  // 좌회전이면 양수 각도
) {
    LKASCommand cmd;
    cmd.intervention = true;
    cmd.left_speed = static_cast<float>(left_pwm);
    cmd.right_speed = static_cast<float>(right_pwm);
    cmd.steering_angle = steering_angle_deg;
    cmd.direction = 'L';
    return cmd;
}

// - 오른쪽(우회전) 강제 조향용
inline LKASCommand get_lkas_command_constant_right(
    int left_pwm, int right_pwm,
    float steering_angle_deg = 45.0f  // 우회전이면 음수 각도
) {
    LKASCommand cmd;
    cmd.intervention = true;
    cmd.left_speed = static_cast<float>(left_pwm);
    cmd.right_speed = static_cast<float>(right_pwm);
    cmd.steering_angle = steering_angle_deg;
    cmd.direction = 'R';
    return cmd;
}

// 단순 offset 비례 제어 + Ackermann 수식을 이용한 좌우 바퀴 속도 계산 함수
inline LKASCommand get_lkas_command_simple(
    float offset,
    float max_steer_rad = 0.5f,  // 최대 조향각 (radian 단위, 약 28.6도)
    float L = 0.117f,
    float T = 0.135f,
    int MAX_PWM = 250,
    float offset_threshold = 5.0f
) {
    LKASCommand cmd;
    cmd.intervention = false;
    cmd.steering_angle = 0.0f;
    cmd.left_speed = MAX_PWM / 2.0f;
    cmd.right_speed = MAX_PWM / 2.0f;
    cmd.direction = 'S';

    if (std::abs(offset) < offset_threshold) {
        // 개입 없음, 직진 유지
        cmd.intervention = false;
    } else {
        // intervention 발생
        cmd.intervention = true;

        // offset을 최대 조향각에 선형 매핑 (-max_steer_rad ~ +max_steer_rad)
        // 화면 반 너비 기준 정규화
        float max_offset = Width / 2.0f;
        float steer_ratio = std::clamp(offset / max_offset, -1.0f, 1.0f);
        float steer_angle = steer_ratio * max_steer_rad;
        cmd.steering_angle = steer_angle * 180.0f / CV_PI;  // degree 변환

        // 속도 감쇠 (조향각 클수록 감속)
        float speed_reduce_ratio = 1.0f - 0.7f * (std::abs(steer_angle) / max_steer_rad);
        speed_reduce_ratio = std::clamp(speed_reduce_ratio, 0.3f, 1.0f);

        float v0 = speed_reduce_ratio;

        // Ackermann 수식 적용
        float left_v  = v0 * (1 + (T / (2 * L)) * tan(steer_angle));
        float right_v = v0 * (1 - (T / (2 * L)) * tan(steer_angle));

        cmd.left_speed = std::clamp(left_v * MAX_PWM, 0.0f, (float)MAX_PWM);
        cmd.right_speed = std::clamp(right_v * MAX_PWM, 0.0f, (float)MAX_PWM);

        if (cmd.left_speed > cmd.right_speed) cmd.direction = 'L';
        else if (cmd.left_speed < cmd.right_speed) cmd.direction = 'R';
        else cmd.direction = 'S';
    }

    return cmd;
}

// PID 제어기는 위 main 코드에서 사용하지 않을 수도 있으니 필요한 경우만 사용하세요.
class PIDController {
public:
    float kp, ki, kd;
    float error_sum, prev_error;
    double last_time;
    float max_error_sum;

    PIDController(float p, float i, float d)
        : kp(p), ki(i), kd(d), error_sum(0), prev_error(0), max_error_sum(30) {
        last_time = static_cast<double>(cv::getTickCount()) / cv::getTickFrequency();
    }

    float update(float error) {
        double now = static_cast<double>(cv::getTickCount()) / cv::getTickFrequency();
        double dt = now - last_time;
        last_time = now;
        error_sum = std::clamp(static_cast<float>(error_sum + error * dt), -max_error_sum, max_error_sum);
        float d_error = (dt > 0) ? (error - prev_error) / dt : 0;
        prev_error = error;
        return kp * error + ki * error_sum + kd * d_error;
    }

    void reset() {
        error_sum = 0; prev_error = 0;
        last_time = static_cast<double>(cv::getTickCount()) / cv::getTickFrequency();
    }
};
