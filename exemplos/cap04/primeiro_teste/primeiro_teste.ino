/* ============================================================
   BitVolts — O meu primeiro robô
   Capítulo 4 — O primeiro teste

   Ligações: Só o cabo USB. Nada mais ligado.
   Monte com a energia desligada. Confira antes de energizar.
   ============================================================ */

void setup() {
  Serial.begin(115200);
  delay(1000);
  Serial.println("Ola! A placa esta viva.");
}

void loop() {
  Serial.println("...ainda aqui.");
  delay(2000);
}
