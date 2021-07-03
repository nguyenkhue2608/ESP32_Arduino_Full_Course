#include <Arduino.h>

#define DAC1 25
// khởi tạo giá trị DAC
int Value = 0; //255= 3.3V 128=1.65V
void setup() {
  Serial.begin(115200);
}

void loop() { 
  //Khởi tạo tín hiệu hình sin
  // tăng dần điện áp
  for(int Value = 0; Value <= 255; Value++){   
    //ghi giá trị điện áp lên chân DAC
    dacWrite(DAC1, Value);
    delay(15);
  }
  // giảm dần điện áp
  for(int Value = 255; Value >= 0; Value--){
    //ghi giá trị điện áp lên chân DAC
    dacWrite(DAC1, Value); 
  }
}