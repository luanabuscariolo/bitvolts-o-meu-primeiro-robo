/* ============================================================
   BitVolts — O meu primeiro robô
   Capítulo 10 · Teste 3 — O sensor de distância

   Ligações: Figura 39 do livro. TRIG ao GPIO 4; ECHO pelo divisor de 3× 1 kΩ (capítulo 6) ao GPIO 5. O sensor precisa dos 5 V da bateria/LM2596.
   Monte com a energia desligada. Confira antes de energizar.
   ============================================================ */

#define PIN_TRIG 4
#define PIN_ECHO 5

void setup() {
  Serial.begin(115200);
  delay(500);
  pinMode(PIN_TRIG, OUTPUT);
  pinMode(PIN_ECHO, INPUT);
  digitalWrite(PIN_TRIG, LOW);
  Serial.println("Teste do sensor. Aproxime a mao.");
}

void loop() {

  digitalWrite(PIN_TRIG, LOW);  delayMicroseconds(2);
  digitalWrite(PIN_TRIG, HIGH); delayMicroseconds(10);
  digitalWrite(PIN_TRIG, LOW);

  unsigned long dur = pulseIn(PIN_ECHO, HIGH, 30000UL);

  if (dur == 0) {
    Serial.println("sem eco");
  } else {

    Serial.print(dur / 58.0, 1);
    Serial.println(" cm");
  }
  delay(300);
}
