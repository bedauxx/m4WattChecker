#include <Thanos_INA260.h>



//#include <Wire.h>
//#include <Adafruit_INA219.h>

Thanos_INA260 ina260;


void setup() {
    Serial.begin(115200);
    ina260.begin();
}

void loop() {

  float busvoltage = 0;
  float current_mA = 0;

  busvoltage = ina260.getBusVoltage_V();
  current_mA = ina260.getCurrent_mA() /1000 ;
    
    if(busvoltage==0){
         delay(100);
    }else if(busvoltage>5){
         delay(100);
    }else{
         Serial.print(busvoltage);
         Serial.print("V,");
         Serial.print(current_mA);
         Serial.println("A");
         delay(250);
    }

}


