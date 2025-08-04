// 조이스틱 예제 : 조이스틱 입력값을 시리얼로 확인하는 예제 파일
// 보드 설정 : ESP32 PICO-D4

// VCC -> 5V or 3.3V
// GND -> GND
// VRx -> GPIO25 (X축)
// VRy -> GPIO26 (Y축)
// SW  -> GPIO27 (버튼)

int sx = 25;  // VRx (X)
int sy = 26;  // VRy (Y)
int sw = 27;  // SW (버튼)

void setup() {
  Serial.begin(115200);
  pinMode(sw, INPUT_PULLUP);  // 버튼은 내부 풀업 설정
}

void loop() {
  int xVal = analogRead(sx);
  int yVal = analogRead(sy);
  int swVal = digitalRead(sw);  // 0이면 눌림

  Serial.print("x: ");
  Serial.print(xVal);
  Serial.print("   y: ");
  Serial.print(yVal);
  Serial.print("   sw: ");
  Serial.println(swVal);

  delay(100);
}