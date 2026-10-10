/* ============================================================
   BitVolts — O meu primeiro robô · Capítulos 16 e 17
   A fila, o cooldown e a interrupção cooperativa

   Demonstra as três regras de comunicação entre os núcleos,
   sem sensor nem motor nenhum. Se entender este sketch,
   pode observar este mecanismo antes do firmware completo.
   ============================================================ */

#define COOLDOWN_MS 3000
#define PASSOS_PROCESSAMENTO 10
#define PAUSA_PASSO_MS 400

// 10 * 400 = 4000 ms: com cooldown de 3000 ms, chega um novo recado
// durante o trabalho. Para observar a conclusao, use cooldown de 6000 ms.

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

      // Simula 10 passos lentos (como escrever palavra a palavra)
      for (int i = 1; i <= PASSOS_PROCESSAMENTO; i++) {
        vTaskDelay(pdMS_TO_TICKS(PAUSA_PASSO_MS));

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
  Serial.println("\n=== Fila, cooldown e interrupcao cooperativa ===\n");

  fila = xQueueCreate(1, sizeof(int));
  if (fila == NULL) {
    Serial.println("ERRO: nao foi possivel criar a fila.");
    while (true) vTaskDelay(pdMS_TO_TICKS(1000));
  }

  TaskHandle_t handleProdutor = NULL, handleConsumidor = NULL;
  BaseType_t criouProdutor = xTaskCreatePinnedToCore(
    produtor, "prod", 2048, NULL, 2, &handleProdutor, 0);
  BaseType_t criouConsumidor = xTaskCreatePinnedToCore(
    consumidor, "cons", 4096, NULL, 1, &handleConsumidor, 1);
  if (criouProdutor != pdPASS || criouConsumidor != pdPASS) {
    if (criouProdutor == pdPASS) vTaskDelete(handleProdutor);
    if (criouConsumidor == pdPASS) vTaskDelete(handleConsumidor);
    Serial.println("ERRO: nao foi possivel criar as duas tarefas. Reinicie.");
    while (true) vTaskDelay(pdMS_TO_TICKS(1000));
  }
}

void loop() {
  vTaskDelay(pdMS_TO_TICKS(1000));
}
