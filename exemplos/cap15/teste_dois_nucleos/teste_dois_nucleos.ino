/* ============================================================
   BitVolts — O meu primeiro robô · Capítulo 15
   Provar que os dois núcleos correm ao mesmo tempo

   Este sketch não faz nada de útil. Serve só para você ver, com
   os próprios olhos, que duas tarefas correm em paralelo em
   núcleos diferentes.
   ============================================================ */

void tarefaA(void* p) {
  for (;;) {
    Serial.print("A (nucleo ");
    Serial.print(xPortGetCoreID());
    Serial.println(") — rapida");
    vTaskDelay(pdMS_TO_TICKS(300));
  }
}

void tarefaB(void* p) {
  for (;;) {
    Serial.print("        B (nucleo ");
    Serial.print(xPortGetCoreID());
    Serial.println(") — lenta");
    // Simula um trabalho demorado, como escrever uma frase no display.
    vTaskDelay(pdMS_TO_TICKS(2000));
  }
}

void setup() {
  Serial.begin(115200);
  delay(600);
  Serial.println("\n=== Teste 11.1 — dois nucleos ===");
  Serial.println("A deve aparecer ~6x entre cada B.\n");

  xTaskCreatePinnedToCore(tarefaA, "A", 2048, NULL, 1, NULL, 0);
  xTaskCreatePinnedToCore(tarefaB, "B", 2048, NULL, 1, NULL, 1);
}

void loop() {
  vTaskDelay(pdMS_TO_TICKS(1000));
}
