/****************************************************************************

    EA076 C - Projeto Final - Tracker.io
    Dimitri Reis        RA 145869
    Guilherme Frauches  RA 155591

    Placa solar que se ajusta de acordo com a incidencia luminosa e
    mostra a potencia gerada pela placa em um display lcd

 ****************************************************************************/

#include <stdio.h>
#include "TimerOne.h"
#include "LiquidCrystal.h"

//(<pino RS>, <pino enable>, <pino D4>, <pino D5>, <pino D6>, <pino D7>)
//Define os pinos que serão utilizados para ligação ao display
LiquidCrystal lcd(2, 3, 4, 5, 6, 7);

void setup() {
  //Define o número de colunas e linhas do LCD
  lcd.begin(16, 2);
  lcd.setCursor (0, 0);
  lcd.print(" Arduino based ");
  lcd.setCursor(0, 1);
  lcd.print("Digital Voltmeter");
  delay(2000);

  /*
    Timer1.initialize();                // Inicializacao da interrupcao por tempo
    Timer1.attachInterrupt(Int_Timer);

    Serial.begin(9600);
    Wire.begin();*/
}

/* Realiza o tratamento da interrupção */
/*void Int_Timer() {
  sValue_left = analogRead(LDR_left);
  sValue_right = analogRead(LDR_right);
  if (pisca)                                          // Pisca o LED a cada 1 seg, se necessario
    digitalWrite(ledPin, digitalRead(ledPin) ^ 1);
  else
    digitalWrite (ledPin, LOW);
  }*/

void loop() {
  //Limpa a tela
  lcd.clear();
  //Posiciona o cursor na coluna 0, linha 0;
  lcd.setCursor(0, 0);
  //Envia o texto entre aspas para o LCD
  lcd.print("Hello World");
  lcd.setCursor(0, 1);
  lcd.print("Testando");

  /*     analog_value = analogRead(A0);
     temp = (analog_value * 5.0) / 1024.0;

     voltage = temp/(0.0909);
     if (voltage < 0.1)
     {
       voltage=0.0;
     } */
}



/*
   Referências
   Servo: http://www.electronicshub.org/arduino-servo-motor/
   Solar Tracker: http://www.electronicshub.org/arduino-solar-tracker/
   Light Sensor: http://www.electronicshub.org/arduino-light-sensor/
   Digital Voltmeter: http://www.electronicshub.org/digital-arduino-voltmeter/
   LCD: http://blog.filipeflop.com/display/controlando-um-lcd-16x2-com-arduino.html
*/

/*
  const int LDR_left = A1;    // Pino referente ao LDR da esquerda
  const int LDR_right = A2;   // Pino referente ao LDR da direita
  unsigned int sValue_left;     // Variavel que representa o valor lido do LDR
  unsigned int sValue_right;     // Variavel que representa o valor lido do LDR
  unsigned int faixa = 50;  //faixa de compracao entre os LDRs
*/

