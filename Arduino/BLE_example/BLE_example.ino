//BLE예제 파일
#include <BLEDevice.h>
#include <BLEUtils.h>
#include <BLEServer.h>
#include <BLE2902.h>

// 사용자 정의 UUID (아무 UUID나 사용해도 됨)
#define SERVICE_UUID        "12345678-1234-1234-1234-1234567890ab"
#define CHARACTERISTIC_UUID "abcd1234-ab12-cd34-ef56-abcdef123456"

BLECharacteristic *pCharacteristic;
bool deviceConnected = false;

// 연결 상태 콜백 정의
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

  // BLE 장치 초기화
  BLEDevice::init("ESP32-HelloBLE");
  
  // BLE 서버 생성
  BLEServer *pServer = BLEDevice::createServer();
  pServer->setCallbacks(new MyServerCallbacks());

  // BLE 서비스 생성
  BLEService *pService = pServer->createService(SERVICE_UUID);

  // 특성(characteristic) 생성
  pCharacteristic = pService->createCharacteristic(
                      CHARACTERISTIC_UUID,
                      BLECharacteristic::PROPERTY_NOTIFY
                    );

  // Notify를 가능하게 하기 위한 디스크립터 추가
  pCharacteristic->addDescriptor(new BLE2902());

  // 서비스 시작
  pService->start();

  // 광고 시작
  pServer->getAdvertising()->start();
  Serial.println("BLE Advertising Started");
}

void loop() {
  if (deviceConnected) {
    pCharacteristic->setValue("Hello");
    pCharacteristic->notify();
    Serial.println("Sent: Hello");
  }
  delay(1000);  // 1초마다 전송
  if (deviceConnected) {
    pCharacteristic->setValue("Bye");
    pCharacteristic->notify();
    Serial.println("Sent: Bye");
  }
  delay(1000);
}
