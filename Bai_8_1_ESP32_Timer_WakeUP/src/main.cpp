#include <Arduino.h>

#define uS_TO_S_FACTOR 1000000  // biến chuyển từ micro giây sang giây
#define TIME_TO_SLEEP  5        //Thời gian thức dậy

RTC_DATA_ATTR int bootCount = 0; // biến này lưu tại bộ nhớ RTC
int bootCountInRam = 0; // biến này lưu tại RAM

//in ra nguồn đánh thức
void print_wakeup_reason(){
  esp_sleep_wakeup_cause_t wakeup_reason;
  wakeup_reason = esp_sleep_get_wakeup_cause();
  switch(wakeup_reason)
  {
    case ESP_SLEEP_WAKEUP_EXT0 : 
      Serial.println("Wakeup caused by external signal using RTC_IO"); 
      break;
    case ESP_SLEEP_WAKEUP_EXT1 : 
      Serial.println("Wakeup caused by external signal using RTC_CNTL"); 
      break;
    case ESP_SLEEP_WAKEUP_TIMER : 
      Serial.println("Wakeup caused by timer"); 
      break;
    case ESP_SLEEP_WAKEUP_TOUCHPAD : 
      Serial.println("Wakeup caused by touchpad"); 
      break;
    case ESP_SLEEP_WAKEUP_ULP : 
      Serial.println("Wakeup caused by ULP program"); 
      break;
    default : 
      Serial.printf("Wakeup was not caused by deep sleep: %d\n",wakeup_reason); 
      break;
  }
}

void setup(){
  Serial.begin(115200);
  delay(1000); //chờ 1 khoảng nhỏ cho serial hoạt động

  //mỗi lần thức dậy sẽ tăng biến này 1 lần và in ra
  ++bootCount;
  ++bootCountInRam;
  Serial.println("Boot number: " + String(bootCount));
  Serial.println("Boot in ram number: " + String(bootCountInRam));

  //in ra nguồn đánh thức esp32
  print_wakeup_reason();

  //gọi hàm thức dậy mỗi 5s
  esp_sleep_enable_timer_wakeup(TIME_TO_SLEEP * uS_TO_S_FACTOR);
  Serial.println("Setup ESP32 to sleep for every " + String(TIME_TO_SLEEP) +
  " Seconds");

  Serial.println("Going to sleep now");
  delay(1000);
  Serial.flush(); 
  // băt đầu vào chế độ ngủ
  esp_deep_sleep_start();
}

void loop(){
  //This is not going to be called
}