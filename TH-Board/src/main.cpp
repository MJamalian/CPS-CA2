#include <Arduino.h>

#include <Wire.h>

#define Addr 0x40

float humidity = 0;
float temp = 0;

bool isChanged = false;
void setup()
{
    Wire.begin();
    Serial.begin(9600);
    delay(300);
}
void loop()
{
    unsigned int data[2];
    Wire.beginTransmission(Addr);
    Wire.write(0xF5);
    Wire.endTransmission();
    delay(500);
    Wire.requestFrom(Addr, 2);
    if(Wire.available() == 2)
    {
        data[0] = Wire.read();
        data[1] = Wire.read();
        float newHumidity = (((data[0] * 256.0 + data[1]) * 125.0) / 65536.0) - 6;
        if (newHumidity != humidity) {
            humidity = newHumidity;
            isChanged = true;
        }
    }

    Wire.beginTransmission(Addr);
    Wire.write(0xF3);
    Wire.endTransmission();
    delay(500);
    Wire.requestFrom(Addr, 2);
    if(Wire.available() == 2)
    {
        data[0] = Wire.read();
        data[1] = Wire.read();
        float newTemp = (((data[0] * 256.0 + data[1]) * 175.72) / 65536.0) - 46.85;
        if (newTemp != temp) {
            temp = newTemp;
            isChanged = true;
        }
    }
    if (isChanged) {
        String outData;
        outData = String(humidity);
        outData += 'M';
        outData += String(temp);
        outData += '\0';
        Serial.print(outData);


        isChanged = false;
    }

    delay(300);
}
