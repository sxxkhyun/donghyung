int LED_data = 0; // LED 상태로 0 또는 1의 값을 가짐
void setup() {
  Serial.begin(9600); // UART 시리얼 포트 초기화
}
void loop() {
  LED_data = (LED_data + 1) % 2; // 0과 1로 반복
  Serial.print(LED_data); // LED 제어 값 전송
  Serial.println();
  delay(1000);
}
