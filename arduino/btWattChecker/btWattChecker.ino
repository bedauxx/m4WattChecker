

#include <Wire.h>
#include <Adafruit_INA219.h>

Adafruit_INA219 ina219;


void setup() {
    Serial.begin(115200);
    ina219.begin();
}

void loop() {

  float shuntvoltage = 0;
  float busvoltage = 0;
  float current_mA = 0;
  float loadvoltage = 0;

 // shuntvoltage = ina219.getShuntVoltage_mV();
  busvoltage = ina219.getBusVoltage_V();
  current_mA = ina219.getCurrent_mA() /1000 ;
 // loadvoltage = busvoltage + (shuntvoltage / 1000);
    
    if(busvoltage==0){
         delay(100);
    }else if(busvoltage>5){
         delay(100);
    }else{
         Serial.print("V,");
         Serial.println("A");
         delay(250);
    }

}


