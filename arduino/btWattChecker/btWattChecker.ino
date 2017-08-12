
int xin;
int yin;
int zin;
int dis;
void setup() {
    Serial.begin(115200);
}

void loop() {

    dis = analogRead(0);
    xin = analogRead(1) - 512;
    yin = analogRead(2) - 512;
    zin = analogRead(3) - 512;

digitalWrite(3, LOW); 
analogWrite(2, dis/2); 

    
     Serial.println(millis());
     Serial.print("X:");
     Serial.println(xin);
     Serial.print("Y:");
     Serial.println(yin);
     Serial.print("Z:");
     Serial.println(zin);
     Serial.print("distance:");
     Serial.println(dis);
     delay(500) ;
}
