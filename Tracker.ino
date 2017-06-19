
/****************************************************************************
    EA076 C - Projeto Final - Tracker.io
    Dimitri Reis        RA 145869
    Guilherme Frauches  RA 155591
    Placa solar que se ajusta de acordo com a incidencia luminosa e
    mostra a potencia gerada pela placa em um display lcd
 ****************************************************************************/

#include <Servo.h>
//defining Servos
Servo servohori;
int servoh = 90;
int servoLimitHigh = 120;
int servoLimitLow = 60;

#define faixa 100

Servo servoverti;
int servov = 90;
//Assigning LDRs
const int ldrleft = A0;    // Pino referente ao LDR da esquerda
const int ldrup = A1;    // Pino referente ao LDR de cima
const int ldrright = A2;   // Pino referente ao LDR da direita
const int ldrdown = A3;

#include <LiquidCrystal.h>
//Define os pinos que serão utilizados para ligação ao display
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);
int portasolar = A5;
float tensao_placa = 0;
void setup ()
{
  //Define o número de colunas e linhas do LCD
  lcd.begin(16, 2);

  servohori.attach(10);
  servohori.write(90);
  servoverti.attach(6);
  servoverti.write(90);
  delay(500);
  Serial.begin(9600);
}

void loop()
{
  servoh = servohori.read();
  servov = servoverti.read();
  //capturing analog values of each LDR
  int up = analogRead(ldrup);
  int down = analogRead(ldrdown) + 70;
  int left = analogRead(ldrleft) + 70;
  int right = analogRead(ldrright);
  // calculating average
  int dif_hor = abs(left - right);
  int dif_ver = abs(up - down);

  if (dif_ver >= faixa) {
    if (up > down) { //gira pra esquerda

      if (servov >= servoLimitHigh)
        servov = servoLimitHigh;
      servoverti.write(servov + 10);
      delay(10);
    } else if (down > up) {
      if (servov <= servoLimitLow)
        servov = servoLimitLow;
      servoverti.write(servov - 10);
      delay(10);
    } else
      servoverti.write(servov);
  }

  if (dif_hor >= faixa) {
    if (left > right) { //gira pra esquerda

      if (servoh <= servoLimitLow)
        servoh = servoLimitLow;
      servohori.write(servoh - 10);
      delay(10);
    }
    else if (right > left)  {

      if (servoh >= servoLimitHigh)
        servoh = servoLimitHigh;
      servohori.write(servoh + 10);
      delay(10);
    } else
      servohori.write(servoh);
    delay(50);
  }

  tensao_placa = analogRead(portasolar);
  tensao_placa = map (tensao_placa, 0, 630, 0, 300);
  tensao_placa = tensao_placa / 100;
  //Limpa a tela
  lcd.clear();
  //Posiciona o cursor na coluna 3, linha 0;
  lcd.setCursor(0, 0);
  //Envia o texto entre aspas para o LCD
  lcd.print("Tensao: ");
  lcd.print(tensao_placa);
  lcd.setCursor(0, 1);
  lcd.print("Capacid.: ");
  tensao_placa = tensao_placa * 33.33;
  lcd.print(tensao_placa);
  lcd.print("%");
  
  delay(500);
}
