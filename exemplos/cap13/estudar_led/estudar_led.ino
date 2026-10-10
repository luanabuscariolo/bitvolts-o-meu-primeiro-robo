/* ============================================================
   BitVolts — O meu primeiro robô
   Capítulo 13 — Um programa completo para ler e alterar

   Ligações: LED verde esquerdo no GPIO 40, com 220 Ω.
   Monte com a energia desligada. Confira antes de energizar.
   ============================================================ */

const int PIN_LED = 40;
const int PAUSA_MS = 500;
int ciclos = 0;

void acender(bool ligado) {
  digitalWrite(PIN_LED, ligado ? HIGH : LOW);
}

void setup() {
  Serial.begin(115200);
  pinMode(PIN_LED, OUTPUT);
  acender(false);
}

void loop() {
  acender(true);
  delay(PAUSA_MS);
  acender(false);
  delay(PAUSA_MS);
  ciclos++;
  Serial.println(ciclos);
  if (ciclos == 5) {
    Serial.println("Cinco ciclos completos.");
  }
}
