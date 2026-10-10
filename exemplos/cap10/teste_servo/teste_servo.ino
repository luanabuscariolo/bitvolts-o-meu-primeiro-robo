/* ============================================================
   BitVolts — O meu primeiro robô
   Capítulo 10 · Teste 4 — O servo

   Ligações: Figura 40 do livro. Castanho ao GND, vermelho ao nó 5 V, laranja ao GPIO 6.
   Monte com a energia desligada. Confira antes de energizar.
   ============================================================ */

#include <ESP32Servo.h>

#define PIN_SERVO 6
Servo servo;

void setup() {
  Serial.begin(115200);
  servo.setPeriodHertz(50);

  servo.attach(PIN_SERVO, 500, 2400);
  servo.write(90);
  delay(1000);
}

void moverSuave(int de, int para) {
  int passo = (para > de) ? 1 : -1;
  for (int a = de; a != para; a += passo) {
    servo.write(a);
    delay(15);
  }
  servo.write(para);
}

void loop() {
  Serial.println("esquerda"); moverSuave(90, 150); delay(600);
  Serial.println("centro");   moverSuave(150, 90); delay(600);
  Serial.println("direita");  moverSuave(90, 30);  delay(600);
  Serial.println("centro");   moverSuave(30, 90);  delay(1200);
}
