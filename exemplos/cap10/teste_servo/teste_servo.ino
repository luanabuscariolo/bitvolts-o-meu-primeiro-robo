/* ============================================================
   BitVolts — O meu primeiro robô
   Capítulo 10 · Teste 4 — O servo

   Ligações: Figura 40 do livro. Castanho ao GND, vermelho ao nó 5 V, laranja ao GPIO 6.
   Monte com a energia desligada. Confira antes de energizar.
   ============================================================ */

#include <ESP32Servo.h>

#define PIN_SERVO 6
#define ANG_CENTRO 90
#define ANG_ESQUERDA 90
#define ANG_DIREITA 90
// Primeiro envio: permanece no centro. Sem o braço acoplado, ajuste
// ANG_CENTRO até alinhar a frente e iguale os outros dois valores a ele.
// Depois, com o conjunto livre, amplie cada lado em passos de 5 graus;
// grave e confira antes de ampliar novamente. Pare se forçar no batente.
Servo servo;

void setup() {
  Serial.begin(115200);
  servo.setPeriodHertz(50);

  servo.attach(PIN_SERVO, 500, 2400);
  servo.write(ANG_CENTRO);
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
  Serial.println("esquerda"); moverSuave(ANG_CENTRO, ANG_ESQUERDA); delay(600);
  Serial.println("centro");   moverSuave(ANG_ESQUERDA, ANG_CENTRO); delay(600);
  Serial.println("direita");  moverSuave(ANG_CENTRO, ANG_DIREITA); delay(600);
  Serial.println("centro");   moverSuave(ANG_DIREITA, ANG_CENTRO); delay(1200);
}
