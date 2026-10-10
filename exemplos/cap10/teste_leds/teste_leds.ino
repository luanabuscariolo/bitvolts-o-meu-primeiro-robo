/* ============================================================
   BitVolts — O meu primeiro robô
   Capítulo 10 · Teste 6 — Os LEDs

   Ligações: Figura 43 do livro. Cada LED com 220 Ω: verde E 40, verde D 41, vermelho E 42, vermelho D 2, amarelos 39.
   Monte com a energia desligada. Confira antes de energizar.
   ============================================================ */

#define LED_VERDE_ESQ  40
#define LED_VERDE_DIR  41
#define LED_VERM_ESQ   42
#define LED_VERM_DIR    2
#define LED_AMARELOS   39

int todos[] = {LED_VERDE_ESQ, LED_VERDE_DIR, LED_VERM_ESQ,
               LED_VERM_DIR, LED_AMARELOS};
const char* nomes[] = {"verde esquerdo", "verde direito",
                       "vermelho esquerdo", "vermelho direito",
                       "amarelos"};

void setup() {
  Serial.begin(115200);
  for (int i = 0; i < 5; i++) {
    pinMode(todos[i], OUTPUT);
    digitalWrite(todos[i], LOW);
  }
}

void loop() {
  // O analogWrite do fim do loop prende o GPIO 39 ao PWM.
  // Sem esta linha, na segunda volta os amarelos nao acendem.
  pinMode(LED_AMARELOS, OUTPUT);

  for (int i = 0; i < 5; i++) {
    for (int j = 0; j < 5; j++) digitalWrite(todos[j], LOW);
    Serial.println(nomes[i]);
    digitalWrite(todos[i], HIGH);
    delay(1200);
  }

  Serial.println("amarelos a pulsar");
  for (int c = 0; c < 3; c++) {
    for (int b = 0; b <= 255; b += 5) {
      analogWrite(LED_AMARELOS, b);
      delay(8);
    }
    for (int b = 255; b >= 0; b -= 5) {
      analogWrite(LED_AMARELOS, b);
      delay(8);
    }
  }
  analogWrite(LED_AMARELOS, 0);
  delay(1000);
}
