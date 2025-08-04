#include "BluetoothSerial.h"

// HC-05 블루투스 모듈의 MAC 주소 (실제 사용 환경에 맞게 변경하세요)
String mac_address_str = "00:22:09:01:C3:0B";
uint8_t address[6];

// BluetoothSerial 객체 생성
BluetoothSerial btSerial;

// 조이스틱 아날로그 입력 핀 번호
const int JOY_X_PIN = 26;
const int JOY_Y_PIN = 25;

// 스위치 입력 핀 번호 (예시, 실제 배선에 맞게 변경!)
const int SW_L_PIN = 27; // 좌측 깜빡이
const int SW_R_PIN = 12; // 우측 깜빡이
const int SW_P_PIN = 32; // 자율주차모드

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

  if (btSerial.connect(address)) {
    Serial.println("HC-05에 성공적으로 연결됨!");
  } else {
    Serial.println("HC-05 연결 실패! 확인 후 다시 시도.");
  }
}

int swL_state = 0;
int swR_state = 0;
int swP_state = 0;

// RC카 파라미터
const float L = 117.0;      // mm, 앞↔뒤 바퀴 간 거리 (실제 카에 맞게 수정)
const float T = 135.0;      // mm, 좌↔우 바퀴 간 거리 (실제 카에 맞게 수정)
const int MAX_PWM = 250;   // 최대 속도(PWM Duty)

// 조이스틱 입력을 0~1 범위로 변환
float getJoystickThrottlex(int val) {
  float mid = 1910.0;
  float maxDiff = 1910.0;
  return constrain((val - mid) / maxDiff, -1.0, 1.0); // -1~1
}
float getJoystickThrottley(int val) {
  float mid = 1930.0;
  float maxDiff = 1930.0;
  return constrain((val - mid) / maxDiff, -1.0, 1.0); // -1~1
}
void loop() {
  if (btSerial.connected()) {
    int xVal = analogRead(JOY_X_PIN);
    int yVal = analogRead(JOY_Y_PIN);
    Serial.print(xVal);
    Serial.print(" ");
    Serial.println(yVal);
    float throttle = getJoystickThrottlex(xVal); // -1(backward) ~ 1(forward)
    float steer    = getJoystickThrottley(yVal); // -1(right)   ~ 1(left)

    // 애커만 기하학에 따라 바퀴 속도 차이 계산
  // θ = steer * 최대 조향각 (예: 30도 ≒ 0.523rad)
  float max_steer_rad = 1.0; // 실제 차량 특성보면 0.5rad(≈28도)가 보통 한계
  float theta = steer * max_steer_rad;

  float v0 = throttle; // (0~+1 or 0~-1) 최대속도 비율. 
  // RC카는 pwm duty로 전달하면 되므로...
  float scale = 1.0; // 필요한 보정값(특성 따라 0.8~1.0써도 됨)

  float v_left  = (1 + (T/(2*L))*tan(theta)) * v0 * scale;
  float v_right = (1 - (T/(2*L))*tan(theta)) * v0 * scale;

  int left_dir = (v_left >= 0) ? 1 : 0;
  int right_dir = (v_right >= 0) ? 1 : 0;

  // Double check: 범위 -1~1 내로
  v_left  = constrain(v_left, -1.0, 1.0);
  v_right = constrain(v_right, -1.0, 1.0);

  int left_duty  = (int)(abs((abs(v_left)  * MAX_PWM)));
  int right_duty = (int)(abs((abs(v_right) * MAX_PWM)));

  if(left_duty < 25 && left_duty >= 0) left_duty = 0;
  if(right_duty < 25 && right_duty >= 0) right_duty = 0;

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
    
    //송신할 데이터
    String sendStr = String(right_duty) + ";"+ String(left_duty) + ";" +
                String(swL_state) + ";" + String(swR_state) + ";" + String(swP_state) + ";" + String(right_dir) + "\n";
    //블루투스 송신
    btSerial.print(sendStr);
    //시리얼 출력
    Serial.println(sendStr);
  } 
  else { // 연결 안될 때
    Serial.println("블루투스 연결 안됨, 연결 재시도 중...");
    if (!btSerial.connect(address)) {
      Serial.println("재연결 실패...");
      delay(2000);
    } else {
      Serial.println("블루투스 재연결 성공!");
    }
  }

  //블루투스 수신 데이터 시리얼 출력
  while (btSerial.available()) {
    char c = btSerial.read();
    Serial.write(c);
  }

  delay(100); // 반복 주기 (필요시 조정)
}