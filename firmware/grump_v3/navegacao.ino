/* ============================================================
   nano-grump v3 — navegacao.ino
   Tudo o que corre no CORE 0: o corpo.

   Este ficheiro nunca chama nada do display. Se precisar de
   comunicar algo, deposita um marcador na fila e segue em
   frente. Nunca espera resposta.
   ============================================================ */

#include <ESP32Servo.h>
#include "config.h"
#include "tipos.h"

extern QueueHandle_t filaMarcadores;

static Servo servo;
static unsigned long ultimoMarcadorMs = 0;
static Marcador ultimoMarcadorEnviado = MARC_START;
static int tentativasDesvio = 0;

// ---------- ENVIO DE MARCADORES ----------

/* Envia um marcador ao cérebro, com duas travas:
   1. Só envia se a situação MUDOU (não repete o mesmo).
   2. Só envia se passaram COOLDOWN_MARCADOR_MS desde o último.

   Sem estas travas, o Core 0 (que corre a cada 50 ms) encheria
   a fila e o grump falaria sobre coisas já passadas.

   Usa xQueueOverwrite: se já houver um marcador à espera, este
   substitui-o. O cérebro recebe sempre o mais recente.        */
static bool enviarMarcador(Marcador m, bool forcar = false) {
  unsigned long agora = millis();

  if (!forcar) {
    if (m == ultimoMarcadorEnviado) return false;
    if (agora - ultimoMarcadorMs < COOLDOWN_MARCADOR_MS) return false;
  }

  if (xQueueOverwrite(filaMarcadores, &m) != pdPASS) return false;
  ultimoMarcadorEnviado = m;
  ultimoMarcadorMs = agora;

  Serial.print("[corpo] -> ");
  Serial.println(nomeMarcador(m));
  return true;
}

// ---------- LEDS ----------

static void ledsApagar() {
  digitalWrite(PIN_LED_VERDE_ESQ, LOW);
  digitalWrite(PIN_LED_VERDE_DIR, LOW);
  digitalWrite(PIN_LED_VERM_ESQ,  LOW);
  digitalWrite(PIN_LED_VERM_DIR,  LOW);
}

static void ledsFrente() {
  ledsApagar();
  digitalWrite(PIN_LED_VERDE_ESQ, HIGH);
  digitalWrite(PIN_LED_VERDE_DIR, HIGH);
}

static void ledsParar() {
  ledsApagar();
  digitalWrite(PIN_LED_VERM_ESQ, HIGH);
  digitalWrite(PIN_LED_VERM_DIR, HIGH);
}

static void ledsCurvaEsquerda() {
  ledsApagar();
  digitalWrite(PIN_LED_VERDE_ESQ, HIGH);
}

static void ledsCurvaDireita() {
  ledsApagar();
  digitalWrite(PIN_LED_VERDE_DIR, HIGH);
}

// ---------- BUZZER ----------
// Sons curtos. Nenhum deles bloqueia por mais de ~400 ms,
// senão o corpo deixaria de reagir durante o som.

static void somArranque() {
  tone(PIN_BUZZER, 392); delay(110);
  tone(PIN_BUZZER, 523); delay(110);
  tone(PIN_BUZZER, 659); delay(180);
  noTone(PIN_BUZZER);
}

static void somObstaculo() {
  tone(PIN_BUZZER, 330); delay(110);
  tone(PIN_BUZZER, 220); delay(170);
  noTone(PIN_BUZZER);
}

static void somPreso() {
  for (int i = 0; i < 3; i++) {
    tone(PIN_BUZZER, 660); delay(70);
    noTone(PIN_BUZZER);    delay(50);
  }
}

static void somBateriaFraca() {
  tone(PIN_BUZZER, 165); delay(300);
  noTone(PIN_BUZZER);
}

// ---------- MOTORES ----------

static void motoresParar() {
  analogWrite(PIN_ENA, 0);
  analogWrite(PIN_ENB, 0);
  digitalWrite(PIN_IN1, LOW); digitalWrite(PIN_IN2, LOW);
  digitalWrite(PIN_IN3, LOW); digitalWrite(PIN_IN4, LOW);
}

static void motoresFrente(int vel) {
  digitalWrite(PIN_IN1, HIGH); digitalWrite(PIN_IN2, LOW);
  digitalWrite(PIN_IN3, HIGH); digitalWrite(PIN_IN4, LOW);
  analogWrite(PIN_ENA, vel);
  analogWrite(PIN_ENB, vel);
}

static void motoresRe(int vel) {
  digitalWrite(PIN_IN1, LOW); digitalWrite(PIN_IN2, HIGH);
  digitalWrite(PIN_IN3, LOW); digitalWrite(PIN_IN4, HIGH);
  analogWrite(PIN_ENA, vel);
  analogWrite(PIN_ENB, vel);
}

// Curva no próprio eixo: um motor para a frente, outro para trás.
// Gira mais apertado do que parar uma das rodas.
static void motoresGirarEsquerda(int vel) {
  digitalWrite(PIN_IN1, LOW);  digitalWrite(PIN_IN2, HIGH);
  digitalWrite(PIN_IN3, HIGH); digitalWrite(PIN_IN4, LOW);
  analogWrite(PIN_ENA, vel);
  analogWrite(PIN_ENB, vel);
}

static void motoresGirarDireita(int vel) {
  digitalWrite(PIN_IN1, HIGH); digitalWrite(PIN_IN2, LOW);
  digitalWrite(PIN_IN3, LOW);  digitalWrite(PIN_IN4, HIGH);
  analogWrite(PIN_ENA, vel);
  analogWrite(PIN_ENB, vel);
}

// ---------- SENSOR ----------

static float medirDistanciaCm() {
  digitalWrite(PIN_TRIG, LOW);
  delayMicroseconds(2);
  digitalWrite(PIN_TRIG, HIGH);
  delayMicroseconds(10);
  digitalWrite(PIN_TRIG, LOW);

  unsigned long dur = pulseIn(PIN_ECHO, HIGH, ECHO_TIMEOUT_US);
  if (dur == 0) return -1.0f;   // sem eco: distância desconhecida

  float d = dur / 58.0;
  if (d < DIST_MIN_CM || d > DIST_MAX_CM) return -1.0f;
  return d;
}

// Move o servo suavemente e mede no destino.
static float medirNoAngulo(int angulo, int anguloAtual) {
  int passo = (angulo > anguloAtual) ? 1 : -1;
  for (int a = anguloAtual; a != angulo; a += passo) {
    servo.write(a);
    delay(SERVO_PASSO_MS);
  }
  servo.write(angulo);
  delay(180);            // deixa o servo assentar antes de medir
  return medirDistanciaCm();
}

// ---------- BATERIA ----------

static float lerTensaoBateria() {
  // analogReadMilliVolts usa a calibracao de fabrica do chip.
  // E bem mais fiel do que converter o valor bruto a regra de tres.
  long soma = 0;
  for (int i = 0; i < BAT_N_AMOSTRAS; i++) {
    soma += analogReadMilliVolts(PIN_BATERIA);
    delay(2);
  }
  float vGpio  = (soma / (float)BAT_N_AMOSTRAS) / 1000.0f;   // mV -> V
  float fator  = BAT_R2_KOHM / (BAT_R1_KOHM + BAT_R2_KOHM);
  return (vGpio / fator) * BAT_FATOR_CALIB;
}

// ---------- MANOBRA DE DESVIO ----------

/* Sequência completa quando aparece um obstáculo:
   parar → recuar → varrer com o servo → escolher o lado mais
   livre → girar. Os marcadores são enviados DURANTE a manobra,
   não antes: o corpo age primeiro.                            */
static void desviarObstaculo() {
  motoresParar();
  ledsParar();
  enviarMarcador(MARC_OBSTACLE, true);
  somObstaculo();

  // Recuar
  enviarMarcador(MARC_BACKUP, true);
  motoresRe(VEL_MANOBRA);
  delay(TEMPO_RE_MS);
  motoresParar();

  // Varrer os dois lados com o servo
  float distEsq = medirNoAngulo(ANG_ESQUERDA, ANG_CENTRO);
  float distDir = medirNoAngulo(ANG_DIREITA, ANG_ESQUERDA);
  medirNoAngulo(ANG_CENTRO, ANG_DIREITA);   // volta ao centro

  Serial.print("[corpo] varredura  esq=");
  Serial.print(distEsq, 0);
  Serial.print(" cm  dir=");
  Serial.print(distDir, 0);
  Serial.println(" cm");

  if (distEsq < 0 || distDir < 0) {
    // Não escolhe um lado com base numa leitura que não existe.
    Serial.println("[corpo] varredura sem leitura válida; motores parados.");
    return;
  }

  // Os dois lados bloqueados? Conta como tentativa falhada.
  if (distEsq < DIST_OBSTACULO_CM && distDir < DIST_OBSTACULO_CM) {
    tentativasDesvio++;
    if (tentativasDesvio >= TENTATIVAS_PRESO) {
      enviarMarcador(MARC_STUCK, true);
      somPreso();
      // Meia-volta: gira o dobro do tempo.
      motoresGirarEsquerda(VEL_MANOBRA);
      delay(TEMPO_CURVA_MS * 2);
      motoresParar();
      tentativasDesvio = 0;
      return;
    }
  } else {
    tentativasDesvio = 0;
  }

  // Escolhe o lado mais livre
  if (distEsq >= distDir) {
    enviarMarcador(MARC_TURN_LEFT, true);
    ledsCurvaEsquerda();
    motoresGirarEsquerda(VEL_MANOBRA);
  } else {
    enviarMarcador(MARC_TURN_RIGHT, true);
    ledsCurvaDireita();
    motoresGirarDireita(VEL_MANOBRA);
  }
  delay(TEMPO_CURVA_MS);
  motoresParar();
}

// ---------- TAREFA PRINCIPAL DO CORE 0 ----------

void tarefaNavegacao(void* param) {
  ulTaskNotifyTake(pdTRUE, portMAX_DELAY);
  // --- Configuração dos pinos ---
  pinMode(PIN_TRIG, OUTPUT);
  pinMode(PIN_ECHO, INPUT);
  digitalWrite(PIN_TRIG, LOW);

  pinMode(PIN_ENA, OUTPUT); pinMode(PIN_ENB, OUTPUT);
  pinMode(PIN_IN1, OUTPUT); pinMode(PIN_IN2, OUTPUT);
  pinMode(PIN_IN3, OUTPUT); pinMode(PIN_IN4, OUTPUT);

  pinMode(PIN_LED_VERDE_ESQ, OUTPUT);
  pinMode(PIN_LED_VERDE_DIR, OUTPUT);
  pinMode(PIN_LED_VERM_ESQ,  OUTPUT);
  pinMode(PIN_LED_VERM_DIR,  OUTPUT);

  analogReadResolution(12);
  analogSetPinAttenuation(PIN_BATERIA, ADC_11db);  // alarga a faixa de leitura

  servo.setPeriodHertz(50);
  servo.attach(PIN_SERVO, 500, 2400);
  servo.write(ANG_CENTRO);

  motoresParar();
  ledsApagar();
  delay(800);

  Serial.println("[corpo] pronto (Core 0)");
  enviarMarcador(MARC_START, true);
  somArranque();

  bool obstaculoAnterior = false;
  unsigned long ultimaLeituraBat = 0;
  bool bateriaVerificada = false;

  // --- Ciclo infinito ---
  for (;;) {
    // 1. Bateria antes do primeiro movimento e depois a cada 5 s.
    // Uma manobra em curso pode atrasar esta leitura; não substitui o BMS.
    if (!bateriaVerificada || millis() - ultimaLeituraBat >= 5000) {
      float v = lerTensaoBateria();
      ultimaLeituraBat = millis();
      bateriaVerificada = true;

      if (v < BAT_V_FRACA) {
        motoresParar();
        ledsParar();
        enviarMarcador(MARC_BATERIA_FRACA, true);
        Serial.print("[corpo] BATERIA FRACA: ");
        Serial.println(v, 2);
        // Fica preso aqui: bipa devagar e não anda mais.
        while (true) {
          somBateriaFraca();
          vTaskDelay(pdMS_TO_TICKS(2500));
        }
      }
    }

    // 2. Sensor
    float d = medirDistanciaCm();

    if (d < 0) {
      motoresParar();
      ledsParar();
      Serial.println("[corpo] sem leitura válida; motores parados.");
      vTaskDelay(pdMS_TO_TICKS(CICLO_NAVEGACAO_MS));
      continue;
    }

    // 3. Decisão
    bool obstaculo = (d < DIST_OBSTACULO_CM);

    if (obstaculo) {
      desviarObstaculo();
      obstaculoAnterior = true;
    } else {
      // Se o cooldown ainda impedir o recado, tentamos no ciclo seguinte.
      if (obstaculoAnterior && enviarMarcador(MARC_CLEAR)) {
        obstaculoAnterior = false;
      }
      motoresFrente(VEL_CRUZEIRO);
      ledsFrente();
      enviarMarcador(MARC_EXPLORE);
    }

    // 4. Respira. vTaskDelay cede o núcleo ao FreeRTOS —
    //    No Arduino-ESP32, delay() também cede tempo ao escalonador.
    vTaskDelay(pdMS_TO_TICKS(CICLO_NAVEGACAO_MS));
  }
}
