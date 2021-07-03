#include <Arduino.h>

const int ledPin =  16;      // chân led

// biến trạng thái Led
int ledState = LOW;

// Giá trị lần cuối cùng được cập nhật
unsigned long previousMillis = 0;   

const long interval = 1000; // giá trị delay (milliseconds)

void setup() {
  // set led là ouput
  pinMode(ledPin, OUTPUT);
}

void loop() {

  // khởi tạo một biến lưu giá trị hiện tại của Timer
  unsigned long currentMillis = millis();

  //lấy giá trị hiện tại trừ đi giá trị trước đó và so sánh với khoản thời gian delay
  if (currentMillis - previousMillis >= interval) {
    // nếu giá trị đó bằng hoặc vượt qua
    // lưu giá trị hiện tại thành giá trị lần cuối cập nhật
    previousMillis = currentMillis;

    // đảo giá trị led States
    if (ledState == LOW) {
      ledState = HIGH;
    } else {
      ledState = LOW;
    }

    // ghi giá trị đó lên Led
    digitalWrite(ledPin, ledState);
  }
  //nếu giá trị chưa vượt qua thì không làm gì cả
  delay(5000);
}