/* ============================================================
   BitVolts — O meu primeiro robô
   Capítulo 10 · Teste 5 — O buzzer

   Ligações: Figura 41 do livro. Pino + ao GPIO 7, pino − ao GND.
   Monte com a energia desligada. Confira antes de energizar.
   ============================================================ */

#define PIN_BUZZER 7

int escala[] = {262, 294, 330, 349, 392, 440, 494, 523};

void setup() {
  Serial.begin(115200);
  Serial.println("Deve ouvir 8 notas subindo.");
}

void loop() {
  for (int i = 0; i < 8; i++) {
    tone(PIN_BUZZER, escala[i]);
    delay(350);
    noTone(PIN_BUZZER);
    delay(80);
  }
  delay(1500);
}
