#include <Arduino.h>

#define BUTTON_PIN_BITMASK 0x200000000 // 2^33 in hex

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

void setup(){
  Serial.begin(115200);
  delay(1000); //chờ 1 khoảng nhỏ cho serial hoạt động

  //mỗi lần thức dậy sẽ tăng biến này 1 lần và in ra
  ++bootCount;
  Serial.println("Boot number: " + String(bootCount));

  //in ra nguồn đánh thức esp32
  print_wakeup_reason();

  //cấu hình chế độ thức dậy là ext0
  //chế độ này chỉ bật được khi bộ RTC còn hoạt động
  esp_sleep_enable_ext0_wakeup(GPIO_NUM_33,1); //1 = High, 0 = Low

  
  //cấu hình chế độ thức dậy là ext1
  //chế độ này có thể bật ngay cả khi RTC không còn hoạt động
  //esp_sleep_enable_ext1_wakeup(BUTTON_PIN_BITMASK,ESP_EXT1_WAKEUP_ANY_HIGH);

  Serial.println("Going to sleep now");
  delay(1000);
  Serial.flush(); 
  // băt đầu vào chế độ ngủ
  esp_deep_sleep_start();
}

void loop(){
  //This is not going to be called
}