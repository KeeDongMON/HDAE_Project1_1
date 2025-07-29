// 예시 메시지 형식 : w,swL:1,swR:0,swP:1
// 키보드 입력처럼 수정

// swL : 좌측 방향 지시등
// swR : 우측 방향 지시등
// swP : 자율 주차 시작 버튼

    // 블루투스 송신
    //(x 명령);(y 명령);(왼쪽깜빡이);(오른쪽깜빡이);(주차모드)
    // 정지 'x';'x'
    // 직진'w';'x'
    // 후진 's';'x'
    // 우회전 'w';'d'
    // 좌회전 'w';'a'
    // 우후진's';'d'
    // 좌후진's';'a'

#include "BluetoothSerial.h"

// BluetoothSerial 객체 생성
BluetoothSerial btSerial;

// 조이스틱 아날로그 입력 핀 번호
const int JOY_X_PIN = 25;
const int JOY_Y_PIN = 26;

// 스위치 입력 핀 번호 (예시, 실제 배선에 맞게 변경!)
const int SW_L_PIN = 32; // 좌측 깜빡이
const int SW_R_PIN = 33; // 우측 깜빡이
const int SW_P_PIN = 2; // 자율주차모드

void setup() {
  Serial.begin(115200);
  delay(1000);

  // 스위치 핀 입력 설정
  pinMode(SW_L_PIN, INPUT_PULLUP);
  pinMode(SW_R_PIN, INPUT_PULLUP);
  pinMode(SW_P_PIN, INPUT_PULLUP);

}

int swL_state = 0;
int swR_state = 0;
int swP_state = 0;

void loop() {
    int xVal = analogRead(JOY_X_PIN);
    int yVal = analogRead(JOY_Y_PIN);

    // 현재 스위치 입력값 읽기
    int swL_reading = digitalRead(SW_L_PIN);
    int swR_reading = digitalRead(SW_R_PIN);
    int swP_reading = digitalRead(SW_P_PIN);

    if(swL_reading == 0){
      if (swL_state == 0){
        swL_state = 1;
      }
      else{
        swL_state = 0;
      }
      delay(50);
    }
    if(swR_reading == 0){
      if (swR_state == 0){
        swR_state = 1;
      }
      else{
        swR_state = 0;
      }
      delay(50);
    }
    if(swP_reading == 0){
      if (swP_state == 0){
        swP_state = 1;
      }
      else{
        swP_state = 0;
      }
      delay(100);
    }

    // 조이스틱 조건 처리
    char xcmd = 'x';
    char ycmd = 'x';

    if(xVal < 2000) xcmd = 's';
    else if(xVal > 3500) xcmd = 'w';
    else xcmd = 'x';

    if(yVal < 2000) ycmd = 'a';
    else if(yVal > 3500) ycmd = 'd';
    else ycmd = 'x';

    String sendStr = String(xcmd) + ";" +String(ycmd) + ";"+ String(swL_state) +
                      ";" + String(swR_state) +
                      ";" + String(swP_state) + "\n";
    Serial.println(sendStr);
  delay(100); // 반복 주기 (필요시 조정)
}
