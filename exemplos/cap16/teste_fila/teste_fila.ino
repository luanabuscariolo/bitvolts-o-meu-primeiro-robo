/* ============================================================
   BitVolts — O meu primeiro robô · Capítulos 16 e 17
   A fila, o cooldown e a preempção

   Demonstra as três regras de comunicação entre os núcleos,
   sem sensor nem motor nenhum. Se entender este sketch,
   entende o firmware inteiro.
   ============================================================ */

#define COOLDOWN_MS 3000

QueueHandle_t fila;

// --- PRODUTOR (papel do Core 0) ---
// Corre depressa, mas só envia quando a situacao muda E o
// cooldown passou.
void produtor(void* p) {
  int situacao = 0;
  int ultimaEnviada = -1;
  unsigned long ultimoEnvio = 0;

  for (;;) {
    // A cada ~1,2 s finge que a situacao mudou.
    situacao = (millis() / 1200) % 4;

    bool mudou = (situacao != ultimaEnviada);
    bool passouCooldown = (millis() - ultimoEnvio >= COOLDOWN_MS);

    if (mudou && passouCooldown) {
      // xQueueOverwrite substitui o que la estiver.
      // A fila tem tamanho 1: so o presente importa.
      xQueueOverwrite(fila, &situacao);
      ultimaEnviada = situacao;
      ultimoEnvio = millis();
      Serial.print("[produtor] enviou ");
      Serial.println(situacao);
    }

    vTaskDelay(pdMS_TO_TICKS(50));   // ciclo rapido, como o corpo
  }
}

// --- CONSUMIDOR (papel do Core 1) ---
// Demora a processar. Se chegar coisa nova a meio, desiste.
void consumidor(void* p) {
  int recebido;

  for (;;) {
    if (xQueueReceive(fila, &recebido, portMAX_DELAY) == pdTRUE) {
      Serial.print("[consumidor] a processar ");
      Serial.println(recebido);

      bool interrompido = false;

      // Simula 5 passos lentos (como escrever palavra a palavra)
      for (int i = 1; i <= 5; i++) {
        vTaskDelay(pdMS_TO_TICKS(400));

        // Espreita sem retirar: chegou coisa nova?
        int espreita;
        if (xQueuePeek(fila, &espreita, 0) == pdTRUE) {
          Serial.println("[consumidor] ABANDONOU — chegou novo");
          interrompido = true;
          break;
        }
        Serial.print("  passo ");
        Serial.println(i);
      }

      if (!interrompido) Serial.println("[consumidor] terminou\n");
    }
  }
}

void setup() {
  Serial.begin(115200);
  delay(600);
  Serial.println("\n=== Teste 11.2 — fila, cooldown, preempcao ===\n");

  fila = xQueueCreate(1, sizeof(int));

  xTaskCreatePinnedToCore(produtor,   "prod", 2048, NULL, 2, NULL, 0);
  xTaskCreatePinnedToCore(consumidor, "cons", 4096, NULL, 1, NULL, 1);
}

void loop() {
  vTaskDelay(pdMS_TO_TICKS(1000));
}
