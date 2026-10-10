/* ============================================================
   nano-grump v3 — firmware do corpo
   ESP32-S3 N16R8 · FreeRTOS · dois núcleos

   Core 0 → NAVEGAÇÃO: sensor, motores, servo, LEDs, buzzer,
            bateria. Pausa de 50 ms entre ciclos; as manobras demoram mais.
   Core 1 → CÉREBRO: display, olhos, frases. Ciclo lento.

   Regra de ouro:
   "O corpo nunca espera o cérebro.
    O cérebro comenta o que o corpo já fez."
   ============================================================ */

#include "config.h"
#include "tipos.h"

// A fila é o único canal de eventos entre os núcleos.
// Guarda apenas 1 marcador: se chegar um novo antes de o
// cérebro consumir o anterior, o antigo é descartado. Isso é
// intencional — só o presente interessa.
QueueHandle_t filaMarcadores;

// Declaradas nos outros ficheiros do projeto.
void tarefaNavegacao(void* param);
void tarefaCerebro(void* param);

void setup() {
  // Mantém a ponte desabilitada mesmo se faltar memória para iniciar.
  pinMode(PIN_ENA, OUTPUT); pinMode(PIN_ENB, OUTPUT);
  pinMode(PIN_IN1, OUTPUT); pinMode(PIN_IN2, OUTPUT);
  pinMode(PIN_IN3, OUTPUT); pinMode(PIN_IN4, OUTPUT);
  digitalWrite(PIN_ENA, LOW); digitalWrite(PIN_ENB, LOW);
  digitalWrite(PIN_IN1, LOW); digitalWrite(PIN_IN2, LOW);
  digitalWrite(PIN_IN3, LOW); digitalWrite(PIN_IN4, LOW);
  Serial.begin(115200);
  delay(600);

  Serial.println();
  Serial.println("=================================");
  Serial.println("  nano-grump v3 — a acordar...");
  Serial.println("=================================");

  // Fila com espaço para 1 marcador.
  filaMarcadores = xQueueCreate(TAMANHO_FILA, sizeof(Marcador));
  if (filaMarcadores == NULL) {
    Serial.println("ERRO: não foi possível criar a fila.");
    while (true) delay(1000);
  }

  // As tarefas aguardam uma notificação: nenhuma inicia pela metade.
  TaskHandle_t navegacao = NULL;
  TaskHandle_t cerebro = NULL;
  BaseType_t criouNavegacao = xTaskCreatePinnedToCore(
    tarefaNavegacao, "navegacao", 4096, NULL, 2, &navegacao, 0);
  BaseType_t criouCerebro = xTaskCreatePinnedToCore(
    tarefaCerebro, "cerebro", 8192, NULL, 1, &cerebro, 1);
  if (criouNavegacao != pdPASS || criouCerebro != pdPASS) {
    if (navegacao != NULL) vTaskDelete(navegacao);
    if (cerebro != NULL) vTaskDelete(cerebro);
    vQueueDelete(filaMarcadores);
    filaMarcadores = NULL;
    Serial.println("ERRO: não foi possível criar as duas tarefas. Motores desligados.");
    while (true) delay(1000);
  }
  xTaskNotifyGive(cerebro);
  xTaskNotifyGive(navegacao);

  Serial.println("Tarefas criadas. Core 0 = corpo, Core 1 = cérebro.");
}

void loop() {
  // Vazio de propósito. Todo o trabalho vive nas duas tarefas.
  // Este delay evita que o watchdog do núcleo 1 se queixe.
  vTaskDelay(pdMS_TO_TICKS(1000));
}

const char* nomeMarcador(Marcador m) {
  switch (m) {
    case MARC_START:         return "<start>";
    case MARC_EXPLORE:       return "<explore>";
    case MARC_OBSTACLE:      return "<obstacle>";
    case MARC_TURN_LEFT:     return "<turn_left>";
    case MARC_TURN_RIGHT:    return "<turn_right>";
    case MARC_BACKUP:        return "<backup>";
    case MARC_STUCK:         return "<stuck>";
    case MARC_CLEAR:         return "<clear>";
    case MARC_BATERIA_FRACA: return "<bateria_fraca>";
  }
  return "<?>";
}
