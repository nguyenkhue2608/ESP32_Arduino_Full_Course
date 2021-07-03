#include <Arduino.h>

#define Threshold 40 //biến giới hạn (độ nhạy) cho touch pin

// khai báo 1 biến kiểu touch_pad_t
touch_pad_t touchPin;

RTC_DATA_ATTR int bootCount = 0; // biến này lưu tại bộ nhớ RTC

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

//in ra chân wake up
void print_wakeup_touchpad(){
  touchPin = esp_sleep_get_touchpad_wakeup_status();

  switch(touchPin)
  {
    case 0  : Serial.println("Touch detected on GPIO 4"); break;
    case 1  : Serial.println("Touch detected on GPIO 0"); break;
    case 2  : Serial.println("Touch detected on GPIO 2"); break;
    case 3  : Serial.println("Touch detected on GPIO 15"); break;
    case 4  : Serial.println("Touch detected on GPIO 13"); break;
    case 5  : Serial.println("Touch detected on GPIO 12"); break;
    case 6  : Serial.println("Touch detected on GPIO 14"); break;
    case 7  : Serial.println("Touch detected on GPIO 27"); break;
    case 8  : Serial.println("Touch detected on GPIO 33"); break;
    case 9  : Serial.println("Touch detected on GPIO 32"); break;
    default : Serial.println("Wakeup not by touchpad"); break;
  }
}

void callback(){
  //Hàm được gọi mỗi khi có touch pin dc kích hoạt
}

void setup(){
  Serial.begin(115200);
  delay(1000); //chờ 1 khoảng nhỏ cho serial hoạt động

  //mỗi lần thức dậy sẽ tăng biến này 1 lần và in ra
  ++bootCount;
  Serial.println("Boot number: " + String(bootCount));

  //in ra nguồn đánh thức esp32
  print_wakeup_reason();

  //in ra chân touch đánh thức ESP32 
  print_wakeup_touchpad();

  //Cài đặt ngắt cho chân Touch Pad 3 (GPIO15)
  touchAttachInterrupt(T3, callback, Threshold);

  //Cấu hình chê độ thức dây là touchpad
  esp_sleep_enable_touchpad_wakeup();

  Serial.println("Going to sleep now");
  delay(1000);
  Serial.flush(); 
  // băt đầu vào chế độ ngủ
  esp_deep_sleep_start();
}

void loop(){
  //This is not going to be called
}