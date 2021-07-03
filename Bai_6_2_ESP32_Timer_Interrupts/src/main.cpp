#include <Arduino.h>

const int ledPin =  16;      // chân led
// biến trạng thái Led
int ledState = LOW;

hw_timer_t* timer = NULL; //khơi tạo timer
portMUX_TYPE timerMux = portMUX_INITIALIZER_UNLOCKED; 

// hàm xử lý ngắt
void IRAM_ATTR onTimer() {   
  portENTER_CRITICAL_ISR(&timerMux); //vào chế độ tránh xung đột
  digitalWrite(ledPin, ~ledState); // đảo giá trị Led
  portEXIT_CRITICAL_ISR(&timerMux); // thoát 
}
 
void setup() {
  Serial.begin(115200);
  //khởi tạo chân led là output
  pinMode(ledPin,OUTPUT);

  //khơit tạo timer với chu kì 1us vì thạch anh của ESP chạy 8MHz
  timer = timerBegin(0, 80, true);
  //khởi tạo hàm xử lý ngắt ngắt cho Timer
  timerAttachInterrupt(timer, &onTimer, true);
  //khởi tạo thời gian ngắt cho timer là 1s (1000000 us)
  timerAlarmWrite(timer, 1000000, true);
  //bắt đầu chạy timer
  timerAlarmEnable(timer);
}
 
void loop() {
 //do nothing
}