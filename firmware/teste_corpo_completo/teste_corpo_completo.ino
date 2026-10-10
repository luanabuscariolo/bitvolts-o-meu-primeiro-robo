/* ============================================================
   nano-grump v3 — TESTE DO CORPO COMPLETO
   Uma rotina loop(). Sem fila e sem duas tarefas de aplicação.

   Objetivo: provar que todos os componentes JÁ TESTADOS
   ISOLADAMENTE funcionam bem quando estão todos ligados ao
   mesmo tempo, antes de soldar qualquer coisa em definitivo.

   O display mostra frases fixas e olhos simples — só para você
   ACOMPANHAR o que o robô está a decidir, sem a complexidade
   dos dois núcleos. Isso vem depois, já com tudo soldado.

   Só vale soldar se este sketch correr sem problemas.
   ============================================================ */

#include <ESP32Servo.h>
#include <U8g2lib.h>

// ---------- PINOS (iguais ao config.h do firmware final) ----------
#define PIN_TRIG            4
#define PIN_ECHO             5
#define PIN_SERVO            6
#define PIN_BUZZER           7
#define PIN_OLED_CS          8
#define PIN_OLED_DC          9
#define PIN_OLED_RES        10
#define PIN_OLED_MOSI       11
#define PIN_OLED_CLK        12
#define PIN_ENA             15
#define PIN_IN1             16
#define PIN_IN2             17
#define PIN_IN3             18
#define PIN_IN4             21
#define PIN_ENB             13
#define PIN_LED_VERDE_ESQ   40
#define PIN_LED_VERDE_DIR   41
#define PIN_LED_VERM_ESQ    42
#define PIN_LED_VERM_DIR     2
#define PIN_LED_AMARELOS    39
#define PIN_BATERIA          1

// ---------- CONSTANTES ----------
#define ANG_CENTRO      85
#define ANG_ESQUERDA    140
#define ANG_DIREITA     30

#define DIST_OBSTACULO_CM  25
#define DIST_MIN_CM        2.0
#define DIST_MAX_CM        400.0
#define ECHO_TIMEOUT_US    30000UL

#define VEL_CRUZEIRO    170
#define VEL_MANOBRA     200
#define TEMPO_RE_MS     500
#define TEMPO_CURVA_MS  450

#define BAT_R1_KOHM     100.0
#define BAT_R2_KOHM     47.0
#define BAT_N_AMOSTRAS  20
#define BAT_V_FRACA     6.2
#define BAT_FATOR_CALIB      1.00   // copie FATOR_CALIB do teste_bateria

Servo servo;

// SPI por software. U8G2_R2 = 180 graus, conector para baixo.
U8G2_SH1106_128X64_NONAME_F_4W_SW_SPI oled(
  U8G2_R2, PIN_OLED_CLK, PIN_OLED_MOSI, PIN_OLED_CS, PIN_OLED_DC, PIN_OLED_RES);

// ============================================================
// DISPLAY — frases fixas e olhos simples
// ============================================================

enum Expressao { OLHOS_NORMAL, OLHOS_ENTEDIADO, OLHOS_SURPRESO,
                  OLHOS_ESQ, OLHOS_DIR, OLHOS_IRRITADO, OLHOS_CANSADO };

void desenharOlho(int cx, int cy, int dx, int dy, int altura) {
  oled.drawRBox(cx - 16, cy - altura / 2, 32, altura, 6);
  oled.setDrawColor(0);
  oled.drawBox(cx - 5 + dx, cy - 6 + dy, 10, 12);
  oled.setDrawColor(1);
}

void desenharRosto(Expressao e) {
  int esqX = 36, dirX = 92, cy = 26;
  switch (e) {
    case OLHOS_NORMAL:    desenharOlho(esqX, cy, 0, 0, 30); desenharOlho(dirX, cy, 0, 0, 30); break;
    case OLHOS_ENTEDIADO: desenharOlho(esqX, cy, 0, 2, 18); desenharOlho(dirX, cy, 0, 2, 18); break;
    case OLHOS_SURPRESO:  desenharOlho(esqX, cy, 0, 0, 36); desenharOlho(dirX, cy, 0, 0, 36); break;
    case OLHOS_ESQ:       desenharOlho(esqX, cy, -7, 0, 30); desenharOlho(dirX, cy, -7, 0, 30); break;
    case OLHOS_DIR:       desenharOlho(esqX, cy, 7, 0, 30); desenharOlho(dirX, cy, 7, 0, 30); break;
    case OLHOS_IRRITADO:
      desenharOlho(esqX, cy, 0, 3, 22); desenharOlho(dirX, cy, 0, 3, 22);
      oled.drawLine(esqX - 16, cy - 16, esqX + 14, cy - 9);
      oled.drawLine(dirX + 16, cy - 16, dirX - 14, cy - 9);
      break;
    case OLHOS_CANSADO:
      oled.drawBox(esqX - 16, cy - 2, 32, 4);
      oled.drawBox(dirX - 16, cy - 2, 32, 4);
      break;
  }
}

// Mostra rosto + frase fixa de uma vez (sem palavra a palavra —
// isso fica para a versão com dois núcleos).
void mostrarNoDisplay(Expressao e, const char* linha1, const char* linha2 = "") {
  oled.clearBuffer();
  desenharRosto(e);
  oled.setFont(u8g2_font_6x10_tf);
  oled.drawStr(2, 50, linha1);
  if (linha2[0] != '\0') oled.drawStr(2, 62, linha2);
  oled.sendBuffer();
}

// ============================================================
// LEDS
// ============================================================

void ledsApagar() {
  digitalWrite(PIN_LED_VERDE_ESQ, LOW);
  digitalWrite(PIN_LED_VERDE_DIR, LOW);
  digitalWrite(PIN_LED_VERM_ESQ, LOW);
  digitalWrite(PIN_LED_VERM_DIR, LOW);
}
void ledsFrente()        { ledsApagar(); digitalWrite(PIN_LED_VERDE_ESQ, HIGH); digitalWrite(PIN_LED_VERDE_DIR, HIGH); }
void ledsParar()         { ledsApagar(); digitalWrite(PIN_LED_VERM_ESQ, HIGH); digitalWrite(PIN_LED_VERM_DIR, HIGH); }
void ledsCurvaEsquerda() { ledsApagar(); digitalWrite(PIN_LED_VERDE_ESQ, HIGH); }
void ledsCurvaDireita()  { ledsApagar(); digitalWrite(PIN_LED_VERDE_DIR, HIGH); }

void amarelosPulsar() {
  for (int b = 0; b <= 255; b += 15)  { analogWrite(PIN_LED_AMARELOS, b); delay(6); }
  for (int b = 255; b >= 0; b -= 15)  { analogWrite(PIN_LED_AMARELOS, b); delay(6); }
  analogWrite(PIN_LED_AMARELOS, 0);
}

// ============================================================
// BUZZER
// ============================================================

void somArranque()  { tone(PIN_BUZZER, 392); delay(110); tone(PIN_BUZZER, 523); delay(110); tone(PIN_BUZZER, 659); delay(180); noTone(PIN_BUZZER); }
void somObstaculo()  { tone(PIN_BUZZER, 330); delay(110); tone(PIN_BUZZER, 220); delay(170); noTone(PIN_BUZZER); }
void somPreso()      { for (int i = 0; i < 3; i++) { tone(PIN_BUZZER, 660); delay(70); noTone(PIN_BUZZER); delay(50); } }
void somBateriaFraca() { tone(PIN_BUZZER, 165); delay(300); noTone(PIN_BUZZER); }

// ============================================================
// MOTORES
// ============================================================

void motoresParar() {
  analogWrite(PIN_ENA, 0); analogWrite(PIN_ENB, 0);
  digitalWrite(PIN_IN1, LOW); digitalWrite(PIN_IN2, LOW);
  digitalWrite(PIN_IN3, LOW); digitalWrite(PIN_IN4, LOW);
}
void motoresFrente(int v) {
  digitalWrite(PIN_IN1, HIGH); digitalWrite(PIN_IN2, LOW);
  digitalWrite(PIN_IN3, HIGH); digitalWrite(PIN_IN4, LOW);
  analogWrite(PIN_ENA, v); analogWrite(PIN_ENB, v);
}
void motoresRe(int v) {
  digitalWrite(PIN_IN1, LOW); digitalWrite(PIN_IN2, HIGH);
  digitalWrite(PIN_IN3, LOW); digitalWrite(PIN_IN4, HIGH);
  analogWrite(PIN_ENA, v); analogWrite(PIN_ENB, v);
}
void motoresGirarEsquerda(int v) {
  digitalWrite(PIN_IN1, LOW);  digitalWrite(PIN_IN2, HIGH);
  digitalWrite(PIN_IN3, HIGH); digitalWrite(PIN_IN4, LOW);
  analogWrite(PIN_ENA, v); analogWrite(PIN_ENB, v);
}
void motoresGirarDireita(int v) {
  digitalWrite(PIN_IN1, HIGH); digitalWrite(PIN_IN2, LOW);
  digitalWrite(PIN_IN3, LOW);  digitalWrite(PIN_IN4, HIGH);
  analogWrite(PIN_ENA, v); analogWrite(PIN_ENB, v);
}

// ============================================================
// SENSOR
// ============================================================

float medirDistanciaCm() {
  digitalWrite(PIN_TRIG, LOW);
  delayMicroseconds(2);
  digitalWrite(PIN_TRIG, HIGH);
  delayMicroseconds(10);
  digitalWrite(PIN_TRIG, LOW);

  unsigned long dur = pulseIn(PIN_ECHO, HIGH, ECHO_TIMEOUT_US);
  if (dur == 0) return -1.0f;

  float d = dur / 58.0;
  if (d < DIST_MIN_CM || d > DIST_MAX_CM) return -1.0f;
  return d;
}

float medirNoAngulo(int angulo, int anguloAtual) {
  int passo = (angulo > anguloAtual) ? 1 : -1;
  for (int a = anguloAtual; a != angulo; a += passo) {
    servo.write(a);
    delay(12);
  }
  servo.write(angulo);
  delay(180);
  return medirDistanciaCm();
}

// ============================================================
// BATERIA
// ============================================================

float lerTensaoBateria() {
  long soma = 0;
  for (int i = 0; i < BAT_N_AMOSTRAS; i++) {
    soma += analogReadMilliVolts(PIN_BATERIA);
    delay(2);
  }
  float vGpio = (soma / (float)BAT_N_AMOSTRAS) / 1000.0f;
  float fator = BAT_R2_KOHM / (BAT_R1_KOHM + BAT_R2_KOHM);
  return (vGpio / fator) * BAT_FATOR_CALIB;
}

// ============================================================
// MANOBRA DE DESVIO
// ============================================================

int tentativasPreso = 0;

void desviarObstaculo() {
  motoresParar();
  ledsParar();
  mostrarNoDisplay(OLHOS_SURPRESO, "opa. tinha algo ai.");
  somObstaculo();
  delay(400);

  mostrarNoDisplay(OLHOS_SURPRESO, "recuando...");
  motoresRe(VEL_MANOBRA);
  delay(TEMPO_RE_MS);
  motoresParar();

  float distEsq = medirNoAngulo(ANG_ESQUERDA, ANG_CENTRO);
  float distDir = medirNoAngulo(ANG_DIREITA, ANG_ESQUERDA);
  medirNoAngulo(ANG_CENTRO, ANG_DIREITA);

  Serial.print("varredura  esq=");
  Serial.print(distEsq, 0);
  Serial.print(" cm  dir=");
  Serial.print(distDir, 0);
  Serial.println(" cm");

  if (distEsq < 0 || distDir < 0) {
    mostrarNoDisplay(OLHOS_CANSADO, "sem leitura valida.", "confira o sensor.");
    Serial.println("Varredura sem leitura válida; motores parados.");
    return;
  }

  if (distEsq < DIST_OBSTACULO_CM && distDir < DIST_OBSTACULO_CM) {
    tentativasPreso++;
    if (tentativasPreso >= 4) {
      mostrarNoDisplay(OLHOS_IRRITADO, "estou preso.", "perfeito.");
      somPreso();
      motoresGirarEsquerda(VEL_MANOBRA);
      delay(TEMPO_CURVA_MS * 2);
      motoresParar();
      tentativasPreso = 0;
      delay(600);
      return;
    }
  } else {
    tentativasPreso = 0;
  }

  if (distEsq >= distDir) {
    mostrarNoDisplay(OLHOS_ESQ, "vamos por aqui.");
    ledsCurvaEsquerda();
    motoresGirarEsquerda(VEL_MANOBRA);
  } else {
    mostrarNoDisplay(OLHOS_DIR, "por aqui entao.");
    ledsCurvaDireita();
    motoresGirarDireita(VEL_MANOBRA);
  }
  delay(TEMPO_CURVA_MS);
  motoresParar();
}

// ============================================================
// SETUP / LOOP
// ============================================================

bool obstaculoAnterior = false;
unsigned long ultimaLeituraBat = 0;
bool bateriaVerificada = false;

void setup() {
  Serial.begin(115200);
  delay(600);

  Serial.println();
  Serial.println("==================================================");
  Serial.println("  nano-grump v3 — TESTE DO CORPO COMPLETO");
  Serial.println("  (uma rotina loop — sem duas tarefas de aplicacao)");
  Serial.println("==================================================");
  Serial.println("Rodas no ar? Confirme antes de continuar.");

  pinMode(PIN_TRIG, OUTPUT);
  pinMode(PIN_ECHO, INPUT);
  digitalWrite(PIN_TRIG, LOW);

  pinMode(PIN_ENA, OUTPUT); pinMode(PIN_ENB, OUTPUT);
  pinMode(PIN_IN1, OUTPUT); pinMode(PIN_IN2, OUTPUT);
  pinMode(PIN_IN3, OUTPUT); pinMode(PIN_IN4, OUTPUT);

  pinMode(PIN_LED_VERDE_ESQ, OUTPUT);
  pinMode(PIN_LED_VERDE_DIR, OUTPUT);
  pinMode(PIN_LED_VERM_ESQ, OUTPUT);
  pinMode(PIN_LED_VERM_DIR, OUTPUT);
  pinMode(PIN_LED_AMARELOS, OUTPUT);

  analogReadResolution(12);
  analogSetPinAttenuation(PIN_BATERIA, ADC_11db);

  servo.setPeriodHertz(50);
  servo.attach(PIN_SERVO, 500, 2400);
  servo.write(ANG_CENTRO);

  oled.begin();
  mostrarNoDisplay(OLHOS_NORMAL, "nano-grump v3", "teste do corpo");

  motoresParar();
  ledsApagar();
  delay(2500);   // tempo para confirmar rodas no ar

  Serial.println("A arrancar...\n");
  mostrarNoDisplay(OLHOS_NORMAL, "ligado. vamos la.");
  somArranque();
  amarelosPulsar();
  delay(500);
}

void loop() {
  // Bateria antes do primeiro movimento e depois a cada 5 s.
  if (!bateriaVerificada || millis() - ultimaLeituraBat >= 5000) {
    // Compara motores parados e em movimento. Ambas as leituras
    // são tensões reais em condições diferentes; rodas suspensas.
    motoresParar();
    delay(250);                       // deixa a tensão recuperar
    float vRepouso = lerTensaoBateria();

    if (vRepouso < BAT_V_FRACA) {
      ledsParar();
      mostrarNoDisplay(OLHOS_CANSADO, "sem bateria.", "me carregue.");
      Serial.println("BATERIA FRACA antes do teste de carga — parando.");
      while (true) { somBateriaFraca(); delay(2500); }
    }

    // Agora mede outra vez com os motores a puxar, para saber
    // o tamanho da queda.
    motoresFrente(VEL_CRUZEIRO);
    delay(250);
    float vCarga = lerTensaoBateria();
    motoresParar();

    ultimaLeituraBat = millis();
    bateriaVerificada = true;

    Serial.print("Bateria: repouso ");
    Serial.print(vRepouso, 2);
    Serial.print(" V | sob carga ");
    Serial.print(vCarga, 2);
    Serial.print(" V | queda ");
    Serial.print(vRepouso - vCarga, 2);
    Serial.println(" V");

    // Para também se a tensão cair abaixo do limiar sob esta carga.
    // Este valor não mede diretamente a porcentagem de carga.
    if (vCarga < BAT_V_FRACA) {
      motoresParar();
      ledsParar();
      mostrarNoDisplay(OLHOS_CANSADO, "sem bateria.", "me carregue.");
      Serial.println("BATERIA FRACA — parando.");
      while (true) { somBateriaFraca(); delay(2500); }
    }
  }

  float d = medirDistanciaCm();
  if (d < 0) {
    motoresParar();
    ledsParar();
    mostrarNoDisplay(OLHOS_CANSADO, "sem leitura valida.", "confira o sensor.");
    Serial.println("Sem leitura válida; motores parados.");
    delay(150);
    return;
  }
  bool obstaculo = (d < DIST_OBSTACULO_CM);

  Serial.print("Distancia: ");
  Serial.print(d, 1);
  Serial.println(" cm");

  if (obstaculo) {
    desviarObstaculo();
    obstaculoAnterior = true;
  } else {
    if (obstaculoAnterior) {
      mostrarNoDisplay(OLHOS_NORMAL, "livre de novo.");
      delay(300);
      obstaculoAnterior = false;
    }
    motoresFrente(VEL_CRUZEIRO);
    ledsFrente();
    mostrarNoDisplay(OLHOS_ENTEDIADO, "andando por ai.");
  }

  delay(150);
}
