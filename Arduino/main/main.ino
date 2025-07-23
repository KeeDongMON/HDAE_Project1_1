// 조이스틱 입력값을 BLE로 보내는 코드

#include <BLEDevice.h>
#include <BLEUtils.h>
#include <BLEServer.h>
#include <BLE2902.h>

// === 조이스틱 핀 설정 ===
int sx = 25;  // VRx (X축 아날로그)
int sy = 26;  // VRy (Y축 아날로그)
int sw = 27;  // 버튼 스위치 (디지털)

//sx,sy값 범위 : 0~4095

// === UUID 설정 ===
#define SERVICE_UUID        "12345678-1234-1234-1234-1234567890ab"
#define CHARACTERISTIC_UUID "abcd1234-ab12-cd34-ef56-abcdef123456"

BLECharacteristic *pCharacteristic;
bool deviceConnected = false;

// === 연결 상태 콜백 ===
class MyServerCallbacks : public BLEServerCallbacks {
  void onConnect(BLEServer* pServer) {
    deviceConnected = true;
  }

  void onDisconnect(BLEServer* pServer) {
    deviceConnected = false;
  }
};

void setup() {
  Serial.begin(115200);

  // 핀 설정
  pinMode(sw, INPUT_PULLUP);  // 버튼은 눌렀을 때 LOW

  // BLE 초기화
  BLEDevice::init("ESP_joystick");

  BLEServer *pServer = BLEDevice::createServer();
  pServer->setCallbacks(new MyServerCallbacks());

  BLEService *pService = pServer->createService(SERVICE_UUID);

  pCharacteristic = pService->createCharacteristic(
                      CHARACTERISTIC_UUID,
                      BLECharacteristic::PROPERTY_NOTIFY
                    );

  pCharacteristic->addDescriptor(new BLE2902());

  pService->start();
  pServer->getAdvertising()->start();

  Serial.println("BLE Advertising Started as 'ESP_joystick'");
}

void loop() {
  // 조이스틱 값 읽기
  int xVal = analogRead(sx);  // 0~4095
  int yVal = analogRead(sy);  // 0~4095
  int swVal = digitalRead(sw); // 0 = 눌림, 1 = 안 눌림

  // 문자열로 포맷팅
  char data[50];
  sprintf(data, "x:%d,y:%d,sw:%d", xVal, yVal, swVal);

  // 시리얼 출력
  Serial.println(data);

  // BLE Notify 전송
  if (deviceConnected) {
    pCharacteristic->setValue((uint8_t*)data, strlen(data));
    pCharacteristic->notify();
  }

  delay(100);  // 100ms 간격
}
