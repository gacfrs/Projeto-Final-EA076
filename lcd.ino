
/****************************************************************************
    EA076 C - Projeto Final - Tracker.io
    Dimitri Reis        RA 145869
    Guilherme Frauches  RA 155591
    Placa solar que se ajusta de acordo com a incidencia luminosa e
    mostra a potencia gerada pela placa em um display lcd
 ****************************************************************************/

#include <stdio.h>
#include <Servo.h>
#include <LiquidCrystal.h>
#include "TimerOne.h"

const int LDR_left = A0;    // Pino referente ao LDR da esquerda
const int LDR_up = A1;    // Pino referente ao LDR de cima
const int LDR_right = A2;   // Pino referente ao LDR da direita
const int LDR_down = A3;   // Pino referente ao LDR de baixo

int sValue_left;     // Variavel que representa o valor lido do LDR
int sValue_right;     // Variavel que representa o valor lido do LDR
int sValue_up;     // Variavel que representa o valor lido do LDR
int sValue_down;     // Variavel que representa o valor lido do LDR

int compara_hor = 0;
int compara_ver = 0;

int pos_vert = 0;
int pos_horiz = 90;

/*int on_horiz=0;
  int direction_horiz=0;
  int on_vert=0;*/

#define LED_left 13
#define LED_right 12
#define LED_up 11
#define LED_down 6
#define SERVO_H 10
#define SERVO_V 5
#define faixa 100  //faixa de compracao entre os LDRs
#define up_edge 150
#define low_edge 30

Servo s_horiz;
Servo s_vert;

#define Luz_Fundo  8

//cria um objeto tipo LiquidCrystal que chamei de "lcd" nos pinos citados:
LiquidCrystal lcd(12, 11, 6, 4, 3, 2);
int portasolar = A5;
float tensao_placa = 0;

void setup() {
  Serial.begin(9600);

  pinMode(LED_left, OUTPUT);
  pinMode(LED_right, OUTPUT);
  pinMode(LED_up, OUTPUT);
  pinMode(LED_down, OUTPUT);

  digitalWrite(LED_left, LOW);          // comandado pelo teclado matricial
  digitalWrite(LED_right, LOW);
  digitalWrite(LED_up, LOW);          // comandado pelo teclado matricial
  digitalWrite(LED_down, LOW);

  s_horiz.attach(SERVO_H);
  s_vert.attach(SERVO_V);
  s_horiz.write(0);
  s_vert.write(0);

  Timer1.initialize();                // Inicializacao da interrupcao por tempo
  Timer1.attachInterrupt(Int_Timer);

  lcd.begin(16, 2);
  pinMode(Luz_Fundo, OUTPUT);
  digitalWrite(Luz_Fundo, HIGH);
}

/* Realiza o tratamento da interrupção */
void Int_Timer() {
  sValue_left = analogRead(LDR_left);
  sValue_right = analogRead(LDR_right);
  compara_hor = abs(sValue_left - sValue_right);

  sValue_up = analogRead(LDR_up);
  sValue_down = analogRead(LDR_down);
  compara_ver = abs(sValue_up - sValue_down);

  tensao_placa = analogRead(portasolar);
  tensao_placa = map (tensao_placa, 0, 650, 0, 256);
  tensao_placa = tensao_placa / 100;
  
  lcd.setCursor(0, 0);
  lcd.print("Voltagem : ");
  lcd.print(tensao_placa);
  lcd.setCursor(0, 1);
  lcd.print("Capacida :");
  tensao_placa = tensao_placa * 40;
  lcd.print(tensao_placa);
  lcd.print("%");

  /* if(compara_hor >= faixa){
     on_horiz=1;
    }

     on_horiz=1;
    /*
     Serial.print(sValue_left);
     Serial.print(" ");
     Serial.print(sValue_right);
     Serial.print(" ");
     Serial.print(compara_hor);
     Serial.print(" ");
     Serial.print(sValue_up);
     Serial.print(" ");
     Serial.print(sValue_down);
     Serial.print(" ");
     Serial.print(compara_ver);
     Serial.print("\n");*/
  Serial.print(sValue_left);
  Serial.print(" ");
  Serial.print(sValue_right);
  Serial.print(" ");
  Serial.print(compara_hor);
  Serial.print(" ");
  Serial.print(faixa);
  Serial.print(" ");
  Serial.print(pos_horiz);
  Serial.print(" ");
  Serial.print(tensao_placa);
  Serial.print("\n");

}

void loop() {



  if (compara_hor >= faixa) {
    if ((sValue_left > sValue_right) && (pos_horiz < up_edge)) //gira pra esquerda
      pos_horiz = pos_horiz + 15;
    if ((sValue_left < sValue_right) && (pos_horiz > low_edge))
      pos_horiz = pos_horiz - 15;
    s_horiz.write(pos_horiz);
    delay(1000);
  }
}

/*if (compara_ver >= faixa) {
  if (sValue_up < sValue_down) { //gira pra esquerda
     digitalWrite(LED_up, HIGH);
     digitalWrite(LED_down, LOW);
   } else { //gira pra direita
     digitalWrite(LED_up, LOW);
     digitalWrite(LED_down, HIGH);
   }
  }*/
/*} else {
  digitalWrite(LED_left, LOW);          // comandado pelo teclado matricial
  digitalWrite(LED_right, LOW);
  digitalWrite(LED_up, LOW);          // comandado pelo teclado matricial
  digitalWrite(LED_down, LOW);
  }*/
//}


/*
   Referências
   Servo: http://www.electronicshub.org/arduino-servo-motor/
   Solar Tracker: http://www.electronicshub.org/arduino-solar-tracker/
   Light Sensor: http://www.electronicshub.org/arduino-light-sensor/
   Digital Voltmeter: http://www.electronicshub.org/digital-arduino-voltmeter/
   LCD: http://blog.filipeflop.com/display/controlando-um-lcd-16x2-com-arduino.html
*/

/*

*/
