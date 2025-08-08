#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include "BluetoothSerial.h"

LiquidCrystal_I2C lcd(0x3F, 16, 2); // I2C, width, height

String mac_address_str = "00:22:09:01:C3:0B"; // HC-05 MAC 주소
// String mac_address_str = "98:DA:60:0C:51:D0"; // HC-05 MAC 주소


uint8_t address[6];

BluetoothSerial btSerial; // BluetoothSerial 객체 생성

///////////// 입력 핀 번호 /////////////
const int JOY_X_PIN = 26;
const int JOY_Y_PIN = 25;
const int SW_L_PIN = 27; // 좌측 깜빡이
const int SW_R_PIN = 12; // 우측 깜빡이
const int SW_P_PIN = 14; // 자율주차모드
const int SW_W_PIN = 33; // 비상 깜빡이
const int SW_LKAS_PIN = 32; // LKAS ON/oFF


///////////////////////////////////////////
void setup() {
  Serial.begin(115200);
  delay(1000);

  // MAC 주소 문자열->바이트 배열 변환
  sscanf(mac_address_str.c_str(), "%hhx:%hhx:%hhx:%hhx:%hhx:%hhx",
         &address[0], &address[1], &address[2], &address[3], &address[4], &address[5]);

  // 스위치 핀 입력 설정
  pinMode(SW_L_PIN, INPUT_PULLUP);
  pinMode(SW_R_PIN, INPUT_PULLUP);
  pinMode(SW_P_PIN, INPUT_PULLUP);
  pinMode(SW_W_PIN, INPUT_PULLUP);
  pinMode(SW_LKAS_PIN, INPUT_PULLUP);

  //////////LCD////////////////
  Wire.begin(21, 22);
  lcd.init(); // lcd 초기화
  lcd.backlight(); // 백라이트 ON

  // 블루투스 PIN 설정
  btSerial.setPin("1234", 4);

  // 블루투스 시작, 마스터 모드
  if (!btSerial.begin("ESP32_Master", true)) {
    Serial.println("Bluetooth 시작 실패!");
    while(1);
  }
  Serial.println("ESP32 BLE 마스터 모드 시작됨.");

  // HC-05에 연결 시도
  Serial.print("HC-05 연결 시도: ");
  Serial.println(mac_address_str);

  while(!btSerial.connect(address)){
    lcd.setCursor(0, 0);
    lcd.print("Connecting...");
    Serial.println("HC-05 연결 실패! 확인 후 다시 시도.");
  }

  lcd.setCursor(0, 0);
  lcd.print("Connected    ");
  Serial.println("HC-05에 성공적으로 연결됨!");
  delay(1000);

  lcd.setCursor(0, 0);
  lcd.print("Driving Mode");

}

int swL_state = 0;
int swR_state = 0;
int swP_state = 0;
int swW_state = 0;
int swLKAS_state = 0;
int right_duty = 0;
int left_duty = 0;

// RC카 파라미터
const int MAX_PWM = 250;   // 최대 속도(PWM Duty)

// 조이스틱 입력을 0~1 범위로 변환
float getJoystickThrottlex(int val) {
  float mid = 1470.0;
  float maxDiff = 1470.0;
  return constrain((val - mid) / maxDiff, -1.0, 1.0); // -1~1
}

float getJoystickThrottley(int val) {
  float mid = 1470.0;
  float maxDiff = 1470.0;
  return constrain((val - mid) / maxDiff, -1.0, 1.0); // -1~1
}

//////////////////////////////////////////////////////

void loop() {

    ////////////////모터 출력////////////////////
    int xVal = analogRead(JOY_X_PIN);
    int yVal = analogRead(JOY_Y_PIN);
    Serial.print("xVal: ");
    Serial.print(xVal);
    Serial.print(", yVal: ");
    Serial.println(yVal);
    // -1.0 ~ 1.0 범위로 변환
    float throttle = getJoystickThrottlex(xVal);
    float steer   = getJoystickThrottley(yVal);

    // 8방향 구분을 위한 변수 (예: 문자열 대신 enum/int 로 대체 가능)
    String dir = "straight";

    const float DEADZONE = 0.4;

    // 방향 판별을 위한 임계값(Deadzone) 체크
    bool x_pos = steer > DEADZONE;
    bool x_neg = steer < -DEADZONE;
    bool y_pos = throttle > DEADZONE;
    bool y_neg = throttle < -DEADZONE;

    float v_left = 0;
    float v_right = 0;

    // 8방향 조건에 맞게 분기
    if (!x_pos && !x_neg && !y_pos && !y_neg) {
      dir = "straight";
      v_left = 0;
      v_right = 0;
    }
    else if (!x_pos && !x_neg && y_pos) {
      dir = "front";
      v_left = throttle;
      v_right = throttle;
    }
    else if (x_pos && y_pos) {
      dir = "front_left";
      v_left = -0.6;
      v_right = 0.6;
      // v_left = 0.3;
      // v_right = throttle;
    }
    else if (x_neg && y_pos) {
      dir = "front_right";
      v_left = 0.6;
      v_right = -0.6;
      // v_left = throttle;
      // v_right = 0.3;
    }
    else if (!x_pos && !x_neg && y_neg) {
      dir = "back";
      v_left = throttle * 0.6;
      v_right = throttle * 0.6;
    }
    else if (x_pos && y_neg) {
      dir = "back_left";
      v_left = 0.4;       
      v_right = -0.4;
    }
    else if (x_neg && y_neg) {
      dir = "back_right";
      v_left = 0.4;
      v_right = -0.4;
    }
    else if (x_pos && !y_pos && !y_neg) {
      dir = "clockwise";
      v_left = -0.4;
      v_right = 0.4;
    }
    else if (x_neg && !y_pos && !y_neg) {
      dir = "unclockwise";
      v_left = 0.4;
      v_right = -0.4;
    }
    else {
      // 예외 처리 (필요시)
      dir = "straight";
      v_left = 0;
      v_right = 0;
    }

    Serial.print("Throttle: ");
    Serial.print(throttle, 4); // 소수점 4자리 출력
    Serial.print(", Steer: ");
    Serial.println(steer, 4);

    Serial.println(dir);

    // 실제 모터 duty 계산 (MAX_PWM 곱해서 0~ +최대, -최대~0 범위)
    const int MAX_PWM = 250;
    int left_duty = (int)(abs(v_left) * MAX_PWM);
    int right_duty = (int)(abs(v_right) * MAX_PWM);

    // 최소 임계값 처리 (예: 소음 제거)
    if (left_duty < 30) left_duty = 0;
    if (right_duty < 30) right_duty = 0;

    int left_dir = (v_left >= 0) ? 1 : 0;
    int right_dir = (v_right >= 0) ? 1 : 0;


    /////////////스위치/////////////////////////
    int swL_reading = digitalRead(SW_L_PIN); // 좌측 방향 지시등
    int swR_reading = digitalRead(SW_R_PIN); // 우측 방향 지시등
    int swW_reading = digitalRead(SW_W_PIN); // 비상 깜빡이
    int swP_reading = digitalRead(SW_P_PIN); // 주차 모드 ON/OFF
    int swLKAS_reading = digitalRead(SW_LKAS_PIN); // LKAS 모드 ON/OFF

    if(swL_reading == 0){
      if (swL_state == 0){
        swL_state = 1;
        lcd.setCursor(0, 1);
        lcd.print("L");
      }
      else{
        swL_state = 0;
        lcd.setCursor(0, 1);
        lcd.print(" ");
      }
      delay(50);
    }
    if(swR_reading == 0){
      if (swR_state == 0){
        swR_state = 1;
        lcd.setCursor(2, 1);
        lcd.print("R");
      }
      else{
        swR_state = 0;
        lcd.setCursor(2, 1);
        lcd.print(" ");
      }
      delay(50);
    }
    if(swP_reading == 0){
      if (swP_state == 0){
        lcd.setCursor(0, 0);
        lcd.print("Parking Mode");
        swP_state = 1;
      }
      else{
        lcd.setCursor(0, 0);
        lcd.print("Driving Mode");
        swP_state = 0;
      }
      delay(100);
    }
    if(swW_reading == 0){
      if (swW_state == 0){
        lcd.setCursor(4, 1);
        lcd.print("W");
        swW_state = 1;
      }
      else{
        lcd.setCursor(4, 1);
        lcd.print(" ");
        swW_state = 0;
      }
      delay(100);
    }
    if(swLKAS_reading == 0){
      if (swLKAS_state == 0){
        lcd.setCursor(0, 0);
        lcd.print("LKAS MODE   ");
        swLKAS_state = 1;
      }
      else{
        lcd.setCursor(0, 0);
        lcd.print("Driving MODE");
        swLKAS_state = 0;
      }
      delay(100);
    }


    ////////////////데이터 송신//////////////////////
    String sendStr = String(left_duty) + ";"+ String(right_duty) + ";" + String(swL_state) + ";" + String(swR_state) + ";" + String(swW_state) + ";" + String(swP_state) + ";" + String(swLKAS_state) + ";" + String(left_dir) + "; "+ String(right_dir) + "\n";
    btSerial.print(sendStr); //블루투스 송신

    if(left_dir == 0) left_duty *= (-1);
    if(right_dir == 0) right_duty *= (-1);

    lcd.setCursor(7, 1);
    lcd.print("           ");
    lcd.setCursor(7, 1);
    lcd.print(left_duty);
    lcd.setCursor(12, 1);
    lcd.print(right_duty);

    String sendStr2 = String(left_duty) + ";"+ String(right_duty) + ";" + String(swL_state) + ";" + String(swR_state) + ";" + String(swW_state) + ";" + String(swP_state) + ";" + String(swLKAS_state) + ";" + String(left_dir) + "; "+ String(right_dir) + "\n";
    Serial.println(sendStr2); //시리얼 출력

    if (!btSerial.connected()) { // BLE 연결 끊기면
      Serial.println("블루투스 연결 안됨, 연결 재시도 중...");
      lcd.setCursor(0, 0);
      lcd.print("Connecting...");
    while (!btSerial.connect(address)) {
      Serial.println("재연결 실패...");
      delay(2000);
    } 
    lcd.setCursor(0, 0);
    lcd.print("Connected   ");
    delay(500);
    Serial.println("블루투스 재연결 성공!");
    lcd.init(); // lcd 초기화
    lcd.backlight(); // 백라이트 ON
    lcd.print("Driving Mode");
    swP_state = 0;
  }

  //////////////////////데이터 수신////////////////////////
  // while (btSerial.available()) {
  //   char c = btSerial.read();
  //   // 신호등 초록인데 안가고 있을 때
  //   if(c == '1'){ 
  //     if(right_duty == 0 && left_duty == 0){
  //         lcd.setCursor(5, 1);
  //         lcd.print("!!GO!!");
  //     }
  //     else{
  //       lcd.setCursor(5, 1);
  //         lcd.print("      ");
  //     }
  //   }
  //   Serial.write(c);
  // }

  delay(100); // 반복 주기
}
