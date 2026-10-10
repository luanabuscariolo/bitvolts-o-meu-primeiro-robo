/* ============================================================
   BitVolts — O meu primeiro robô
   Capítulo 10 · Teste 2 — O display

   Ligações: Figura 38 do livro. VCC ao 3V3, GND, CLK 12, MOSI 11, RES 10, DC 9, CS 8.
   Monte com a energia desligada. Confira antes de energizar.
   ============================================================ */

#include <U8g2lib.h>

U8G2_SH1106_128X64_NONAME_F_4W_SW_SPI display(
  U8G2_R2, 12, 11, 8, 9, 10);

void setup() {
  display.begin();
  display.clearBuffer();
  display.setFont(u8g2_font_6x10_tf);
  display.drawStr(10, 20, "Ola!");
  display.drawStr(10, 40, "O rosto funciona.");
  display.sendBuffer();
}

void loop() { delay(1000); }
