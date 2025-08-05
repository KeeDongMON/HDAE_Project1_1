#include "can.h"
#include <cstdint>
#include <sys/ioctl.h>
#include <net/if.h>
#include <linux/can.h>
#include <linux/can/raw.h>
#include <cstring>
#include <unistd.h>
#include <cstdio>

int can_socket = -1;

bool init_can_socket(const char* ifname) {
    struct ifreq ifr;
    struct sockaddr_can addr;
    can_socket = socket(PF_CAN, SOCK_RAW, CAN_RAW);
    if (can_socket < 0) { perror("CAN socket open error"); return false; }
    strcpy(ifr.ifr_name, ifname);
    if (ioctl(can_socket, SIOCGIFINDEX, &ifr) < 0) {
        perror("CAN ioctl error"); close(can_socket); can_socket = -1; return false;
    }
    addr.can_family = AF_CAN;
    addr.can_ifindex = ifr.ifr_ifindex;
    if (bind(can_socket, (struct sockaddr *)&addr, sizeof(addr)) < 0) {
        perror("CAN bind error"); close(can_socket); can_socket = -1; return false;
    }
    return true;
}

bool send_can_frame(uint32_t can_id, const uint8_t* data, uint8_t len) {
    if (can_socket < 0) return false;
    if (len > 8) len = 8;

    struct can_frame frame;
    frame.can_id = can_id;
    frame.can_dlc = len;
    memcpy(frame.data, data, len);

    int nbytes = write(can_socket, &frame, sizeof(frame));
    return nbytes == sizeof(frame);
}

void close_can_socket() {
    if (can_socket >= 0) close(can_socket);
    can_socket = -1;
}
