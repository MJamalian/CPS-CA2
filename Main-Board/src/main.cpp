#include <arduino.h>
#include <LiquidCrystal.h>
#include <AltSoftSerial.h>

AltSoftSerial myserial;
LiquidCrystal lcd(12, 11, 10, 7, 6, 5, 4);

String THInputStr;
String LightInputStr;

float lux = 0;
float temp = 0;
float humidity = 0;

String luxStr = "";
String tempStr = "";
String humidityStr = "";

void updateLCD();

void setup(){
    Serial.begin(9600);
    myserial.begin(9600);
    lcd.begin(16, 4);
}


void loop(){
    if(Serial.available()){
        char LightInputByte = (char)Serial.read();
        if (LightInputByte == '\0'){
            luxStr = LightInputStr;
            lux = LightInputStr.toFloat();
            LightInputStr = "";
            updateLCD();
        }
        else{
            LightInputStr += LightInputByte;
        }
    }
    if(myserial.available()){
        char THInputByte = (char)myserial.read();
        if (THInputByte == '\0'){
            int M_position = THInputStr.indexOf('M');

            humidityStr = THInputStr.substring(0, M_position);
            humidity = humidityStr.toFloat();

            tempStr = THInputStr.substring(M_position + 1);
            temp = tempStr.toFloat();
            THInputStr = "";
            updateLCD();
        }
        else{
            THInputStr += THInputByte;
        }
    }
}

void updateLCD(){
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("lux: ");
    lcd.print(luxStr);

    lcd.setCursor(0, 1);
    lcd.print("temp: ");
    lcd.print(tempStr);

    lcd.setCursor(0, 2);
    lcd.print("humidity: ");
    lcd.print(humidityStr);

    lcd.setCursor(0, 3);
    lcd.print("result: ");
    if(humidity > 80){
        lcd.print("0");
    }
    else if (humidity < 50) {
        lcd.print("15 cc/m");
    }
    else{
        if (temp < 25 && lux < 600) {
            lcd.print("10 d/m");
        }
        else if (temp < 25 && lux > 600) {
            lcd.print("5 d/m");
        }
        else{
            lcd.print("10 d/m");
        }
    }
}
