// can.h
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

// LKAS 제어 명령 구조체
struct LKASCommand {
    bool intervention;
    float steering_angle;
    float left_speed;
    float right_speed;
    char direction; // 반드시 추가
};

bool init_can_socket(const char* ifname = "can0");
bool send_to_can(const char* msg);
void close_can_socket();

#endif // CAN_H
