/* ============================================================
   nano-grump v3 — cerebro.ino
   Tudo o que corre no CORE 1: o rosto e a fala.

   As frases vêm de tabelas fixas, logo abaixo. Mude-as à
   vontade: é o que dá personalidade ao seu robô. A regra é
   simples — entra um marcador, sai uma frase.
   ============================================================ */

#include <U8g2lib.h>
#include "config.h"
#include "tipos.h"

extern QueueHandle_t filaMarcadores;

/* SPI por software: mais lento que o hardware, mas funciona com
   qualquer pino e evita a configuração de barramento do S3.
   U8G2_R2 = display rodado 180°, porque foi montado com os
   pinos do conector virados para baixo.                       */
static U8G2_SH1106_128X64_NONAME_F_4W_SW_SPI oled(
  U8G2_R2,
  PIN_OLED_CLK,
  PIN_OLED_MOSI,
  PIN_OLED_CS,
  PIN_OLED_DC,
  PIN_OLED_RES
);

// ---------- FRASES ----------
// Três variantes por marcador, escolhidas ao acaso, para o
// grump não repetir sempre a mesma coisa.

static const char* frasesStart[] = {
  "ligado. que alegria.",
  "acordei. de novo.",
  "ah. e estamos de volta."
};
static const char* frasesExplore[] = {
  "andando. nada de novo.",
  "isto aqui e um corredor.",
  "que paisagem fascinante."
};
static const char* frasesObstacle[] = {
  "tinha algo ai. claro.",
  "parede. previsivel.",
  "opa. que surpresa."
};
static const char* frasesTurnLeft[] = {
  "esquerda entao.",
  "vamos por aqui. tanto faz.",
  "a esquerda parece menos ma."
};
static const char* frasesTurnRight[] = {
  "direita. porque nao.",
  "por aqui, suponho.",
  "a direita esta mais livre."
};
static const char* frasesBackup[] = {
  "recuando. otimo.",
  "para tras. de novo.",
  "marcha a re, que elegante."
};
static const char* frasesStuck[] = {
  "estou preso. perfeito.",
  "sem saida. adorei.",
  "alguem me tira daqui."
};
static const char* frasesClear[] = {
  "livre. finalmente.",
  "ate que enfim espaco.",
  "olha, da para andar."
};
static const char* frasesBateria[] = {
  "sem bateria. tchau.",
  "acabou. me carregue.",
  "energia no fim. adeus."
};

static const char* escolherFrase(Marcador m) {
  int i = random(3);
  switch (m) {
    case MARC_START:         return frasesStart[i];
    case MARC_EXPLORE:       return frasesExplore[i];
    case MARC_OBSTACLE:      return frasesObstacle[i];
    case MARC_TURN_LEFT:     return frasesTurnLeft[i];
    case MARC_TURN_RIGHT:    return frasesTurnRight[i];
    case MARC_BACKUP:        return frasesBackup[i];
    case MARC_STUCK:         return frasesStuck[i];
    case MARC_CLEAR:         return frasesClear[i];
    case MARC_BATERIA_FRACA: return frasesBateria[i];
  }
  return "...";
}

// ---------- OLHOS ----------
// Cada marcador tem uma expressão. São desenhados com
// retângulos e linhas simples — nada de bitmaps.

// O enum Expressao vive em tipos.h: o Arduino IDE gera os
// protótipos das funções antes das declarações feitas aqui.

static Expressao expressaoDe(Marcador m) {
  switch (m) {
    case MARC_START:         return OLHOS_NORMAL;
    case MARC_EXPLORE:       return OLHOS_ENTEDIADO;
    case MARC_OBSTACLE:      return OLHOS_SURPRESO;
    case MARC_TURN_LEFT:     return OLHOS_OLHANDO_ESQ;
    case MARC_TURN_RIGHT:    return OLHOS_OLHANDO_DIR;
    case MARC_BACKUP:        return OLHOS_SURPRESO;
    case MARC_STUCK:         return OLHOS_IRRITADO;
    case MARC_CLEAR:         return OLHOS_FELIZ;
    case MARC_BATERIA_FRACA: return OLHOS_CANSADO;
  }
  return OLHOS_NORMAL;
}

// Desenha um olho na posição (cx, cy) com deslocamento da pupila.
static void desenharOlho(int cx, int cy, int desvX, int desvY,
                         int altura) {
  oled.drawRBox(cx - 16, cy - altura/2, 32, altura, 6);
  oled.setDrawColor(0);
  oled.drawBox(cx - 5 + desvX, cy - 6 + desvY, 10, 12);
  oled.setDrawColor(1);
}

static void desenharRosto(Expressao e) {
  int esqX = 36, dirX = 92, cy = 26;

  switch (e) {
    case OLHOS_NORMAL:
      desenharOlho(esqX, cy, 0, 0, 30);
      desenharOlho(dirX, cy, 0, 0, 30);
      break;

    case OLHOS_ENTEDIADO:
      // pálpebras baixas: olho achatado
      desenharOlho(esqX, cy, 0, 2, 18);
      desenharOlho(dirX, cy, 0, 2, 18);
      break;

    case OLHOS_SURPRESO:
      desenharOlho(esqX, cy, 0, 0, 36);
      desenharOlho(dirX, cy, 0, 0, 36);
      break;

    case OLHOS_OLHANDO_ESQ:
      desenharOlho(esqX, cy, -7, 0, 30);
      desenharOlho(dirX, cy, -7, 0, 30);
      break;

    case OLHOS_OLHANDO_DIR:
      desenharOlho(esqX, cy, 7, 0, 30);
      desenharOlho(dirX, cy, 7, 0, 30);
      break;

    case OLHOS_IRRITADO:
      desenharOlho(esqX, cy, 0, 3, 22);
      desenharOlho(dirX, cy, 0, 3, 22);
      // sobrancelhas inclinadas para dentro
      oled.drawLine(esqX - 16, cy - 16, esqX + 14, cy - 9);
      oled.drawLine(dirX + 16, cy - 16, dirX - 14, cy - 9);
      break;

    case OLHOS_FELIZ:
      // arcos virados para cima
      oled.drawLine(esqX - 14, cy + 4, esqX - 4, cy - 8);
      oled.drawLine(esqX - 4, cy - 8, esqX + 12, cy + 4);
      oled.drawLine(dirX - 14, cy + 4, dirX - 4, cy - 8);
      oled.drawLine(dirX - 4, cy - 8, dirX + 12, cy + 4);
      break;

    case OLHOS_CANSADO:
      // linhas horizontais: olhos fechados
      oled.drawBox(esqX - 16, cy - 2, 32, 4);
      oled.drawBox(dirX - 16, cy - 2, 32, 4);
      break;
  }
}

// ---------- LEDS AMARELOS ----------
// Pulsam enquanto o cérebro trabalha. É o único LED que este
// núcleo controla — os outros pertencem ao Core 0.

static void amarelosPulsar(int passos) {
  for (int b = 0; b <= 255; b += passos) {
    analogWrite(PIN_LED_AMARELOS, b);
    vTaskDelay(pdMS_TO_TICKS(8));
  }
  for (int b = 255; b >= 0; b -= passos) {
    analogWrite(PIN_LED_AMARELOS, b);
    vTaskDelay(pdMS_TO_TICKS(8));
  }
  analogWrite(PIN_LED_AMARELOS, 0);
}

// ---------- ESCRITA PALAVRA A PALAVRA ----------

/* Escreve a frase acrescentando uma palavra de cada vez, para
   dar a sensação de que está a ser pensada agora.

   Devolve false se um marcador novo chegou a meio — nesse caso
   abandona a frase atual. É a PREEMPÇÃO: o presente ganha
   sempre do passado.                                          */
static bool escreverFrase(const char* frase, Expressao e) {
  char buffer[96];
  int pos = 0;
  const char* p = frase;

  buffer[0] = '\0';

  while (*p) {
    // copia até ao próximo espaço
    while (*p && *p != ' ' && pos < 90) buffer[pos++] = *p++;
    if (*p == ' ' && pos < 90) buffer[pos++] = *p++;
    buffer[pos] = '\0';

    oled.clearBuffer();
    desenharRosto(e);
    oled.setFont(u8g2_font_6x10_tf);

    // quebra o texto em duas linhas se for longo
    if (pos <= 21) {
      oled.drawStr(2, 56, buffer);
    } else {
      char l1[24], l2[24];
      int corte = 21;
      while (corte > 0 && buffer[corte] != ' ') corte--;
      strncpy(l1, buffer, corte); l1[corte] = '\0';
      strncpy(l2, buffer + corte + 1, 23); l2[23] = '\0';
      oled.drawStr(2, 50, l1);
      oled.drawStr(2, 62, l2);
    }
    oled.sendBuffer();

    // Espreita a fila sem retirar nada. Se há marcador novo,
    // abandona esta frase imediatamente.
    Marcador espreita;
    if (xQueuePeek(filaMarcadores, &espreita, 0) == pdTRUE) {
      return false;
    }

    vTaskDelay(pdMS_TO_TICKS(280));
  }
  return true;
}

// ---------- TAREFA PRINCIPAL DO CORE 1 ----------

void tarefaCerebro(void* param) {
  pinMode(PIN_LED_AMARELOS, OUTPUT);
  analogWrite(PIN_LED_AMARELOS, 0);

  oled.begin();
  oled.clearBuffer();
  oled.setFont(u8g2_font_6x10_tf);
  oled.drawStr(20, 34, "nano-grump v3");
  oled.sendBuffer();

  randomSeed(esp_random());

  Serial.println("[cerebro] pronto (Core 1)");

  Marcador m;

  for (;;) {
    // Espera por um marcador. portMAX_DELAY = espera para
    // sempre, sem gastar CPU. O núcleo fica livre.
    if (xQueueReceive(filaMarcadores, &m, portMAX_DELAY) == pdTRUE) {

      Serial.print("[cerebro] recebeu ");
      Serial.println(nomeMarcador(m));

      Expressao e = expressaoDe(m);

      // Mostra o rosto imediatamente, antes de "pensar".
      oled.clearBuffer();
      desenharRosto(e);
      oled.sendBuffer();

      // Pulsa os amarelos: o cérebro está a trabalhar.
      amarelosPulsar(15);

      const char* frase = escolherFrase(m);
      bool completou = escreverFrase(frase, e);

      if (!completou) {
        Serial.println("[cerebro] frase interrompida (marcador novo)");
        continue;   // volta ao topo e apanha o marcador novo
      }

      // Deixa a frase no ecrã por um momento.
      vTaskDelay(pdMS_TO_TICKS(1400));
    }
  }
}
