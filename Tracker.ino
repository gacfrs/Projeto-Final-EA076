/****************************************************************************
    EA076 C - Projeto Final - Tracker.io
    Dimitri Reis        RA 145869
    Guilherme Frauches  RA 155591
    Placa solar que se ajusta de acordo com a incidencia luminosa e
    mostra a tensao gerada pela placa em um display lcd
 ****************************************************************************/

#include <Servo.h>
#include <LiquidCrystal.h>

Servo servohori;    // Define o servo horizontal
Servo servoverti;   // Define o servo vertical

// Define os pinos que serão utilizados para ligação ao display
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

#define servoLimitHigh 120  // Limites superior e inferior dos servos
#define servoLimitLow 60
#define band 100            // Faixa de valor aceitavel para os LDRs

int servoh = 90;
int servov = 90;
float voltage = 0;          // Tensao lida pelo painel solar

const int ldrleft = A0;     // Define os pinos dos LDRs e painel solar
const int ldrup = A1;
const int ldrright = A2;
const int ldrdown = A3;
const int solarpanel = A5;

void setup () {
  lcd.begin(16, 2);       // Define o numero de colunas e linhas do LCD

  servohori.attach(10);   // Define portas e posicoes iniciais dos servos
  servohori.write(90);
  servoverti.attach(6);
  servoverti.write(90);

  delay(500);
  Serial.begin(9600);
}

void loop() {
  servoh = servohori.read();              // Le as posicoes atuais dos servos
  servov = servoverti.read();

  int up = analogRead(ldrup);             // Le os valores dos LDRs
  int down = analogRead(ldrdown) + 70;
  int left = analogRead(ldrleft) + 70;
  int right = analogRead(ldrright);

  int dif_hor = abs(left - right);        // Calcula a diferenca absoluta entre eles
  int dif_ver = abs(up - down);

  if (dif_ver >= band) {                  // Se a diferenca for maior que a faixa de erro aceitavel os motores regulam o painel
    if (up > down) {
      if (servov >= servoLimitHigh)
        servov = servoLimitHigh;
      servoverti.write(servov + 10);
      delay(10);
    }

    else if (down > up) {
      if (servov <= servoLimitLow)
        servov = servoLimitLow;
      servoverti.write(servov - 10);
      delay(10);
    }

    else
      servoverti.write(servov);
    delay(50);
  }

  if (dif_hor >= band) {
    if (left > right) {
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
    }

    else
      servohori.write(servoh);
    delay(50);
  }

  voltage = analogRead(solarpanel);         // Le a tensao do painel solar
  voltage = map (voltage, 0, 630, 0, 300);  // Mapeia entre seus extremos
  voltage = voltage / 100;

  lcd.clear();                // Limpa a tela
  lcd.setCursor(0, 0);        // Posiciona o cursor na coluna 0, linha 0
  lcd.print("Tensao: ");      // Imprime o texto no LCD
  lcd.print(voltage);
  lcd.setCursor(0, 1);
  lcd.print("Capacid.: ");
  voltage = voltage * 33.33;
  lcd.print(voltage);
  lcd.print("%");

  delay(500);
}
