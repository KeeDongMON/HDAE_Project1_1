#include "main.h"
#define CENTER_VAL 3039  // 조이스틱 중앙값
#define DEADZONE 100     // 중앙 ±100 사이 정지 구간
#define MAX_ADC 4095     // ADC 최대값
#define MAX_PWM 100      // PWM 최대 출력

#define BUF_LEN 64
char buf[BUF_LEN];
int idx = 0;

int main(void)
{
    SYSTEM_Init();
    Motor_Init();

    while (1) {
        int ch = Bluetooth_RecvByteNonBlocked();
        if (ch != -1) {
            if ((char)ch == '\n') {
                buf[idx] = '\0';
                idx = 0;

                int xVal = 0, yVal = 0;

                if (sscanf(buf, "x:%d,y:%d", &xVal, &yVal) == 2) {
                    my_printf("Received X:%d Y:%d\n", xVal, yVal);

                    int pwmOut = 0;
                    int dir = 0;

                    int diff = xVal - CENTER_VAL;

                    if (diff > DEADZONE) {
                        // 조이스틱 X가 중앙보다 +100 이상 크면 정방향 (ex: 오른쪽 경향)
                        dir = 1;
                        // 최대 PWM의 절반까지 비례 증가
                        pwmOut = (diff * (MAX_PWM / 2)) / (MAX_ADC - CENTER_VAL);
                        if (pwmOut > (MAX_PWM / 2)) pwmOut = MAX_PWM / 2;

                    } else if (diff < -DEADZONE) {
                        // 조이스틱 X가 중앙보다 -100 이하 작으면 역방향 (ex: 왼쪽 경향)
                        dir = 2;  // 역방향
                        pwmOut = (-diff * (MAX_PWM / 2)) / CENTER_VAL;  // diff 음수이므로 -를 붙여 양수 변환
                        if (pwmOut > (MAX_PWM / 2)) pwmOut = MAX_PWM / 2;

                    } else {
                        // 중앙 ± DEADZONE 범위 내면 정지
                        dir = 0;
                        pwmOut = 0;
                    }

                    if (dir == 0) {
                        Motor_stopChA();
                        Motor_stopChB();
                    } else {
                        // PWM 출력, 지정 방향으로 모터 구동
                        Motor_movChA_PWM(pwmOut, dir);
                        Motor_movChB_PWM(pwmOut, dir);
                    }
                }
                else {
                    my_printf("Parse error: %s\n", buf);
                }
            }
            else if (idx < BUF_LEN - 1) {
                buf[idx++] = (char)ch;
            }
        }
    }

    return 0;
}
