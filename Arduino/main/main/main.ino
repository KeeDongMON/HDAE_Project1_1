#include "BluetoothSerial.h"

// HC-05 MAC 주소 (실제 주소로 바꿔주세요)
String mac_address_str = "00:22:09:01:C3:0B";  // 예시
uint8_t address[6];

// BluetoothSerial 객체 생성
BluetoothSerial btSerial;

// 조이스틱 아날로그 핀 (ESP32 ADC 핀 예시)
const int JOY_X_PIN = 25;  // ADC1 채널
const int JOY_Y_PIN = 26;  // ADC1 채널

void setup() {
  Serial.begin(115200);
  delay(1000);

  // MAC 주소 문자열 -> byte 배열 변환
  sscanf(mac_address_str.c_str(), "%hhx:%hhx:%hhx:%hhx:%hhx:%hhx", 
         &address[0], &address[1], &address[2], &address[3], &address[4], &address[5]);

  // PIN 설정은 begin() 전에 호출 해야 함
  btSerial.setPin("1234", 4);  // HC-05 실제 PIN으로 변경

  // 블루투스 시작, 마스터 모드(true)
  if (!btSerial.begin("ESP32_Master", true)) {
    Serial.println("Bluetooth 시작 실패!");
    while (1);
  }
  Serial.println("ESP32 BLE 마스터 모드 시작됨.");

  // HC-05에 연결 시도
  Serial.print("HC-05 연결 시도: ");
  Serial.println(mac_address_str);

  bool connected = btSerial.connect(address);
  if (connected) {
    Serial.println("HC-05에 성공적으로 연결됨!");
  } else {
    Serial.println("HC-05 연결 실패! 확인 후 다시 시도.");
  }
}

void loop() {
  // 블루투스 연결 확인
  if (btSerial.connected()) {
    // 아날로그 조이스틱 값 읽기
    int xVal = analogRead(JOY_X_PIN);
    int yVal = analogRead(JOY_Y_PIN);

    // 시리얼 모니터에 출력
    Serial.print("X: ");
    Serial.print(xVal);
    Serial.print(", Y: ");
    Serial.println(yVal);

    // HC-05(블루투스)로 X, Y 값 전송 (문자열로)
    String outStr = "x:" + String(xVal) + ",y:" + String(yVal) + "\n";
    btSerial.print(outStr);

  } else {
    Serial.println("블루투스 연결 안됨, 연결 재시도 중...");
    if (!btSerial.connect(address)) {
      Serial.println("재연결 실패...");
      delay(2000);
    } else {
      Serial.println("블루투스 재연결 성공!");
    }
  }

  // HC-05로부터 데이터 오면 시리얼로 출력 (수신 확인용)
  while (btSerial.available()) {
    char c = btSerial.read();
    Serial.write(c);
  }

  delay(200); // 0.2초 주기 (필요시 조절)
}
