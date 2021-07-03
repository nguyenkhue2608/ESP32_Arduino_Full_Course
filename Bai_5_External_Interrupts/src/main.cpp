#include <Arduino.h>

const int led = 17;
const int button = 16;
bool ledstates = 0;
portMUX_TYPE mux = portMUX_INITIALIZER_UNLOCKED;

void IRAM_ATTR buttonPush() {
  portENTER_CRITICAL_ISR(&mux);//Phần quan trọng cần được bảo vệ khỏi mọi truy cập đồng thời để thay đổi nó
  Serial.println("Button Pushed!!!");
  digitalWrite(led, ~ledstates);
  portEXIT_CRITICAL_ISR(&mux);//Cho phép tiếp tục chạy các task khác
}
void setup() {
  Serial.begin(9600);
  pinMode(button, INPUT_PULLUP);
  // cài đặt ngắt vào chân button, kiểu ngắt là falling (xung xuống), hàm gọi khi có sự kiện ngắt là button push
  attachInterrupt(digitalPinToInterrupt(button), buttonPush, FALLING);
  // chọn led là đầu ra
  pinMode(led, OUTPUT);
  //ghi giá trị ban đầu
  digitalWrite(led, ledstates);
}
void loop() {
  // do nothing
}