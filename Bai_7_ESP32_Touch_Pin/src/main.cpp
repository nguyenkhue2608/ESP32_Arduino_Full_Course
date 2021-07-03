#include <Arduino.h>

// chọn chân touch
const int touchPin = 4; 
const int ledPin = 16;

// Giới hạn touch (độ nhạy)
const int threshold = 20;
// Giá trị touch
int touchValue;

void setup(){
  Serial.begin(9600);
  delay(1000);
  // khởi tạo led là output
  pinMode (ledPin, OUTPUT);
}

void loop(){
  // đọc giá trị touch
  touchValue = touchRead(touchPin);
  Serial.print(touchValue);
  //nếu giá trị nhỏ hơn giới hạn
  if(touchValue < threshold){
    // bật led
    digitalWrite(ledPin, HIGH);
    Serial.println(" - LED on");
  }
  else{
    // nếu lớn hơn hoặc bằng thì tắt led
    digitalWrite(ledPin, LOW);
    Serial.println(" - LED off");
  }
  delay(500);
}