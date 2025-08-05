#ifndef CAN_H
#define CAN_H

#include <linux/can.h>
#include <linux/can/raw.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <net/if.h>
#include <cstring>
#include <unistd.h>
#include <cstdio>
#include <cstdint>   // 여기가 중요! 반드시 추가

struct LKASCommand {
    bool intervention;
    float steering_angle;  // rad
    float left_speed;      // PWM duty 0~MAX_PWM
    float right_speed;     // PWM duty 0~MAX_PWM
    char direction;        // 'L', 'R', 'S', 'O'
};

bool init_can_socket(const char* ifname = "can0");
bool send_to_can(const char* msg);
bool send_can_frame(uint32_t can_id, const uint8_t* data, uint8_t len);
void close_can_socket();

#endif // CAN_H
