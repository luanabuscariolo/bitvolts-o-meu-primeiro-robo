/* ============================================================
   BitVolts — O meu primeiro robô
   Capítulo 10 · Teste 9 — O monitor de bateria

   Ligações: Figura 46 do livro. Divisor 100 kΩ (BAT+) / 47 kΩ (GND) com o meio no GPIO 1; 100 nF entre GPIO 1 e GND.
   Monte com a energia desligada. Confira antes de energizar.
   ============================================================ */

#define PIN_BAT       1
#define R1_KOHM     100.0
#define R2_KOHM      47.0
#define FATOR_CALIB   1.00

void setup() {
  Serial.begin(115200);
  analogReadResolution(12);

  analogSetPinAttenuation(PIN_BAT, ADC_11db);
  Serial.println("Compare com o multimetro na bateria.");
}

float lerTensao() {

  long soma = 0;
  for (int i = 0; i < 20; i++) {
    soma += analogReadMilliVolts(PIN_BAT);
    delay(5);
  }
  float v_gpio = (soma / 20.0) / 1000.0;

  float fator = R2_KOHM / (R1_KOHM + R2_KOHM);
  return (v_gpio / fator) * FATOR_CALIB;
}

void loop() {
  Serial.print(lerTensao(), 2);
  Serial.println(" V");
  delay(1000);
}
