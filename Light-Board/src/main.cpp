#include <Arduino.h>

float lux=0.00,ADC_value=0.0048828125,LDRValue=0;

void setup() {

  pinMode(A5,INPUT);    //make analog pin A0 as input
  Serial.begin(9600);   //initialize serial monitor
  delay(1000);

}

void loop() {
  // delay(1000);
  float newLDRValue=analogRead(A5);
  // mySerial.println("hello");
  if (newLDRValue != LDRValue) {
      lux=(250.000000/(ADC_value*newLDRValue))-50.000000;
      Serial.print(String(lux) + '\0');
      LDRValue = newLDRValue;
  }

  // delay(1000);

}
