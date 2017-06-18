#include <LiquidCrystal.h> 

#define Luz_Fundo  8

//cria um objeto tipo LiquidCrystal que chamei de "lcd" nos pinos citados:
LiquidCrystal lcd(12, 11, 6, 4, 3, 2);
int portasolar = A5; 
float sensorValue = 0;

void setup()
{
lcd.begin(16, 2); 
pinMode(Luz_Fundo,OUTPUT); 
digitalWrite(Luz_Fundo,HIGH); 
Serial.begin(9600); 
}

void loop()
{


lcd.setCursor(0,0);
lcd.print("Voltagem : ");
sensorValue = analogRead(portasolar);
Serial.println(sensorValue); 

sensorValue = map (sensorValue, 0, 650, 0, 250);
sensorValue = sensorValue/100;
lcd.print(sensorValue);


lcd.setCursor(0,1); 

lcd.print("Capacida :");
sensorValue = sensorValue *40;
lcd.print(sensorValue);
lcd.print("%");


delay(500);

}
/*
referencia :
http://engenheirando.com/arduino/displaylcd/

*/
