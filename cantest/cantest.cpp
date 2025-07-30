/*
    CAN 통신 TEST
    Made by YOU WON GYU

    Pre-Setting :: /boot/config.txt
    라즈베리파이5의 경우 /boot/firmware/config.txt로 옮겨짐

    RS485 CAN HAT을 통해
    MCP2515, SN65HVD230 Controller/Transeciver 사용
    CAN H-L 사이 종단 저항 120옴을 끊어줌.
    (TC375 Lite Kit 트랜시버에 120옴/ TOFsense에 120옴을 종단저항으로 달고있음)
    (CAN BUS내 타 Node는 120옴을 달고 있으면 안됨. 저항 낮아짐)

    [all]항목 아래에
    dtparam=spi=on
    dtoverlay=mcp2515-can0,oscilator=12000000,interrupt=25,spimaxfrequency=2000000 추가
    작성

    Usage :: IN Raspi CLI
    
    sudo ip link set can0 down
    
    //TC375, TOFsense 에서 500000 보율 사용중
    //해당 CAN BUS는 500000 보율을 사용해야 함.
    sudo ip link set can0 type can bitrate 500000

    sudo ip link set can0 up

    g++ cantest.cpp -o cantest
    
    chmod +x cantest
    ./cantest
*/


#include <linux/can.h>
#include <linux/can/raw.h>
#include <sys/socket.h>
#include <net/if.h>
#include <sys/ioctl.h>
#include <cstring>
#include <iostream>
#include <unistd.h>        // usleep
#include <signal.h>        // signal handling
#include <atomic>

using namespace std;

atomic<bool> keepRunning(true);

void intHandler(int) {
    keepRunning = false;
}

int main() {
    int s;
    struct sockaddr_can addr;
    struct ifreq ifr;

    // Signal handler 등록 (Ctrl+C)
    signal(SIGINT, intHandler);

    // Socket Create
    s = socket(PF_CAN, SOCK_RAW, CAN_RAW);
    if (s < 0) {
        perror("Socket create error");
        return 1;
    }

    strcpy(ifr.ifr_name, "can0");
    if (ioctl(s, SIOCGIFINDEX, &ifr) < 0) {
        perror("ioctl error");
        return 1;
    }

    addr.can_family  = AF_CAN;
    addr.can_ifindex = ifr.ifr_ifindex;
    if (bind(s, (struct sockaddr *)&addr, sizeof(addr)) < 0) {
        perror("bind error");
        return 1;
    }

    // CAN FRAME 구성
    struct can_frame frame;
    frame.can_id  = 0x12;
    frame.can_dlc = 4;
    frame.data[0] = 0x43;  // 'C'
    frame.data[1] = 0x41;  // 'A'
    frame.data[2] = 0x4E;  // 'N'
    frame.data[3] = 0x0A; // '\n' TC375쪽에서 개행실패해서 여기 넣음

    while (keepRunning.load()) {
        int nbytes = write(s, &frame, sizeof(frame));
        if (nbytes != sizeof(frame)) {
            perror("Write error");
            break;
        }
        
        cout << "CAN frame sent!" << endl;
        usleep(2000000);  // 2s delay
    }

    close(s);

    cout << "\nProgram terminated cleanly" << endl;
    return 0;
}
