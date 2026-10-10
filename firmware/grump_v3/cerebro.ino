/* ============================================================
   nano-grump v3 — cerebro.ino
   Tudo o que corre no CORE 1: o rosto e a fala.

   As frases vêm de tabelas fixas, logo abaixo. Mude-as à
   vontade: é o que dá personalidade ao seu robô. A regra é
   simples — entra um marcador, sai uma frase.
   ============================================================ */

#include <U8g2lib.h>
#include <string.h>
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
  switch (m) {
    case MARC_START:         return frasesStart[random(sizeof(frasesStart) / sizeof(frasesStart[0]))];
    case MARC_EXPLORE:       return frasesExplore[random(sizeof(frasesExplore) / sizeof(frasesExplore[0]))];
    case MARC_OBSTACLE:      return frasesObstacle[random(sizeof(frasesObstacle) / sizeof(frasesObstacle[0]))];
    case MARC_TURN_LEFT:     return frasesTurnLeft[random(sizeof(frasesTurnLeft) / sizeof(frasesTurnLeft[0]))];
    case MARC_TURN_RIGHT:    return frasesTurnRight[random(sizeof(frasesTurnRight) / sizeof(frasesTurnRight[0]))];
    case MARC_BACKUP:        return frasesBackup[random(sizeof(frasesBackup) / sizeof(frasesBackup[0]))];
    case MARC_STUCK:         return frasesStuck[random(sizeof(frasesStuck) / sizeof(frasesStuck[0]))];
    case MARC_CLEAR:         return frasesClear[random(sizeof(frasesClear) / sizeof(frasesClear[0]))];
    case MARC_BATERIA_FRACA: return frasesBateria[random(sizeof(frasesBateria) / sizeof(frasesBateria[0]))];
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

static bool amarelosPulsar(int passos) {
  for (int b = 0; b <= 255; b += passos) {
    Marcador espreita;
    if (xQueuePeek(filaMarcadores, &espreita, 0) == pdTRUE) {
      analogWrite(PIN_LED_AMARELOS, 0);
      return false;
    }
    analogWrite(PIN_LED_AMARELOS, b);
    vTaskDelay(pdMS_TO_TICKS(8));
  }
  for (int b = 255; b >= 0; b -= passos) {
    Marcador espreita;
    if (xQueuePeek(filaMarcadores, &espreita, 0) == pdTRUE) {
      analogWrite(PIN_LED_AMARELOS, 0);
      return false;
    }
    analogWrite(PIN_LED_AMARELOS, b);
    vTaskDelay(pdMS_TO_TICKS(8));
  }
  analogWrite(PIN_LED_AMARELOS, 0);
  return true;
}

// ---------- ESCRITA PALAVRA A PALAVRA ----------

// A interrupcao e cooperativa: verificamos a fila durante as pausas.
static bool esperarApresentacao(unsigned long tempoMs) {
  unsigned long inicio = millis();
  for (;;) {
    Marcador espreita;
    if (xQueuePeek(filaMarcadores, &espreita, 0) == pdTRUE) return false;
    unsigned long decorrido = millis() - inicio;
    if (decorrido >= tempoMs) return true;
    unsigned long restante = tempoMs - decorrido;
    auto ticks = pdMS_TO_TICKS(restante > 20 ? 20 : restante);
    vTaskDelay(ticks > 0 ? ticks : 1);
  }
}

static void mostrarTexto(const char linhas[2][22], Expressao e) {
  oled.clearBuffer();
  desenharRosto(e);
  oled.setFont(u8g2_font_6x10_tf);
  if (linhas[1][0] == '\0') {
    oled.drawStr(2, 56, linhas[0]);
  } else {
    oled.drawStr(2, 50, linhas[0]);
    oled.drawStr(2, 62, linhas[1]);
  }
  oled.sendBuffer();
}

// Duas linhas de 21 caracteres. Frases maiores continuam na pagina seguinte.
// Uma palavra que exceda a linha e dividida, sem perder caracteres.
static bool escreverFrase(const char* frase, Expressao e) {
  char linhas[2][22] = {{0}, {0}};
  int linha = 0, pos = 0;
  const char* p = frase;

  while (*p) {
    while (*p == ' ') p++;
    if (!*p) break;
    size_t palavra = strcspn(p, " ");

    // Move uma palavra inteira para a linha seguinte quando ela cabe nela.
    if (pos && (pos == 21 || (palavra <= 21 && pos + 1 + palavra > 21))) {
      if (linha == 0) linha = 1;
      else { linha = 0; linhas[0][0] = linhas[1][0] = '\0'; }
      pos = 0;
    } else if (pos) {
      linhas[linha][pos++] = ' ';
      linhas[linha][pos] = '\0';
    }

    while (palavra) {
      if (pos == 21) {
        if (linha == 0) linha = 1;
        else { linha = 0; linhas[0][0] = linhas[1][0] = '\0'; }
        pos = 0;
      }
      size_t n = palavra < size_t(21 - pos) ? palavra : size_t(21 - pos);
      memcpy(linhas[linha] + pos, p, n);
      pos += n; p += n; palavra -= n;
      linhas[linha][pos] = '\0';
      mostrarTexto(linhas, e);
      if (!esperarApresentacao(280)) return false;
    }
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
      if (!amarelosPulsar(15)) continue;

      const char* frase = escolherFrase(m);
      bool completou = escreverFrase(frase, e);

      if (!completou) {
        Serial.println("[cerebro] frase interrompida (marcador novo)");
        continue;   // volta ao topo e apanha o marcador novo
      }

      // Deixa a frase no ecrã por um momento.
      esperarApresentacao(1400);
    }
  }
}
