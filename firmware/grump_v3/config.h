/* ============================================================
   nano-grump v3 — config.h
   Todos os pinos, constantes e ajustes ficam neste ficheiro.
   Se precisar mudar um pino ou um tempo, mude AQUI e em mais
   nenhum lado.
   ============================================================ */

#ifndef CONFIG_H
#define CONFIG_H

// ---------- SENSOR ULTRASSÓNICO ----------
#define PIN_TRIG            4
#define PIN_ECHO            5      // via divisor 3× 1 kΩ
#define ECHO_TIMEOUT_US     30000UL
#define DIST_MIN_CM         2.0    // abaixo disto a leitura não é fiável
#define DIST_MAX_CM         400.0

// ---------- SERVO ----------
#define PIN_SERVO           6
#define ANG_CENTRO          85     // calibrado fisicamente
#define ANG_ESQUERDA        140
#define ANG_DIREITA         30
#define SERVO_PASSO_MS      12     // pausa entre cada grau

// ---------- BUZZER ----------
#define PIN_BUZZER          7

// ---------- DISPLAY OLED SH1106 (SPI por software) ----------
#define PIN_OLED_CS         8
#define PIN_OLED_DC         9
#define PIN_OLED_RES        10
#define PIN_OLED_MOSI       11
#define PIN_OLED_CLK        12

// ---------- PONTE H L298N ----------
#define PIN_ENA             15     // PWM motor esquerdo
#define PIN_IN1             16
#define PIN_IN2             17
#define PIN_IN3             18
#define PIN_IN4             21
#define PIN_ENB             13     // PWM motor direito

// ---------- LEDS ----------
#define PIN_LED_VERDE_ESQ   40
#define PIN_LED_VERDE_DIR   41
#define PIN_LED_VERM_ESQ    42
#define PIN_LED_VERM_DIR    2
#define PIN_LED_AMARELOS    39     // os dois amarelos em paralelo

// ---------- MONITOR DE BATERIA ----------
#define PIN_BATERIA         1      // ADC1
#define BAT_R1_KOHM         100.0
#define BAT_R2_KOHM         47.0
#define BAT_V_REF           3.3
#define BAT_ADC_MAX         4095.0
#define BAT_N_AMOSTRAS      20
#define BAT_V_FRACA         6.2    // abaixo disto o robô para
#define BAT_FATOR_CALIB     1.00   // ajuste com o multímetro

// ---------- NAVEGAÇÃO ----------
#define DIST_OBSTACULO_CM   25     // distância que dispara o desvio
#define VEL_CRUZEIRO        170    // 0–255
#define VEL_MANOBRA         200    // curvas precisam de mais força
#define TEMPO_RE_MS         500
#define TEMPO_CURVA_MS      450
#define CICLO_NAVEGACAO_MS  50     // ritmo do Core 0

// Se o robô continuar a ver obstáculo depois de N tentativas
// seguidas de desvio, considera-se preso.
#define TENTATIVAS_PRESO    4

// ---------- COMUNICAÇÃO ENTRE NÚCLEOS ----------
#define COOLDOWN_MARCADOR_MS 3000  // intervalo mínimo entre marcadores
#define TAMANHO_FILA         1     // só o marcador mais recente importa

#endif
