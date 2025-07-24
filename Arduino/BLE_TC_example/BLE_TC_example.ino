#include "BluetoothSerial.h"

BluetoothSerial btSerial;

String mac_address_str = "00:22:09:01:C3:0B";
uint8_t address[6];

void setup() {
  Serial.begin(115200);
  delay(1000);

  sscanf(mac_address_str.c_str(), "%hhx:%hhx:%hhx:%hhx:%hhx:%hhx",
         &address[0], &address[1], &address[2], &address[3], &address[4], &address[5]);

  // PIN 설정은 begin() 전에 반드시 해주세요.
  btSerial.setPin("1234", 4);

  if (!btSerial.begin("ESP32_Master", true)) { // Master 모드로 블루투스 시작
    Serial.println("Bluetooth 시작 실패!");
    while (1); // 멈춤
  }
  Serial.println("ESP32가 마스터 모드로 시작되었습니다.");

  Serial.print(mac_address_str);
  Serial.println(" 주소의 HC-05에 연결을 시도합니다...");

  bool connected = btSerial.connect(address);
  if (connected) {
    Serial.println("HC-05에 성공적으로 연결되었습니다!");
  } else {
    Serial.println("HC-05 연결에 실패했습니다. MAC 주소나 HC-05의 상태를 확인하세요.");
  }
}

void loop() {
  if (btSerial.available()) {
    char data_received = btSerial.read();
    Serial.write(data_received);
  }

  if (Serial.available()) {
    char data_to_send = Serial.read();
    btSerial.write(data_to_send);
  }
}
