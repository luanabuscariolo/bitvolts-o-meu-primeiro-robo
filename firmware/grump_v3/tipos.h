/* ============================================================
   nano-grump v3 — tipos.h
   Os marcadores que o corpo envia ao cérebro, e o estado
   partilhado entre os dois núcleos.
   ============================================================ */

#ifndef TIPOS_H
#define TIPOS_H

// As 8 situações que o corpo comunica, mais a de emergência.
// O corpo envia um destes; o cérebro traduz numa frase.
enum Marcador {
  MARC_START,        // acabou de ligar
  MARC_EXPLORE,      // a andar em frente, sem novidades
  MARC_OBSTACLE,     // detetou algo à frente
  MARC_TURN_LEFT,    // decidiu virar à esquerda
  MARC_TURN_RIGHT,   // decidiu virar à direita
  MARC_BACKUP,       // está a recuar
  MARC_STUCK,        // tentou desviar várias vezes e não saiu
  MARC_CLEAR,        // caminho voltou a ficar livre
  MARC_BATERIA_FRACA // emergência: o robô para
};

// Nome textual do marcador, para depuração no Serial Monitor.
const char* nomeMarcador(Marcador m);

// As expressões dos olhos, desenhadas pelo cérebro.
// Tem de estar num .h: é usada como parâmetro e retorno de funções
// em cerebro.ino, e o Arduino IDE declara essas funções antes de
// chegar à linha onde o enum estaria definido.
enum Expressao {
  OLHOS_NORMAL, OLHOS_ENTEDIADO, OLHOS_SURPRESO,
  OLHOS_OLHANDO_ESQ, OLHOS_OLHANDO_DIR,
  OLHOS_IRRITADO, OLHOS_FELIZ, OLHOS_CANSADO
};

// Estado que o Core 0 escreve e o Core 1 lê para desenhar o rosto.
// Não usa fila porque não é um evento: é uma fotografia do agora.
struct EstadoRobo {
  float distanciaCm;
  float tensaoBateria;
  bool  emMovimento;
  bool  bateriaFraca;
};

extern volatile EstadoRobo estadoAtual;

#endif
