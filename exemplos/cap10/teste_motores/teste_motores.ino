/* ============================================================
   BitVolts — O meu primeiro robô
   Capítulo 10 · Teste 7 — Os motores

   Ligações: Figura 45 do livro. RODAS NO AR. ENA 15, IN1 16, IN2 17, IN3 18, IN4 21, ENB 13. Jumpers 5V_EN, ENA e ENB retirados.
   Monte com a energia desligada. Confira antes de energizar.
   ============================================================ */

#define ENA 15
#define IN1 16
#define IN2 17
#define IN3 18
#define IN4 21
#define ENB 13
#define VEL 153

void setup() {
  Serial.begin(115200);
  int pinos[] = {ENA, IN1, IN2, IN3, IN4, ENB};
  for (int p : pinos) pinMode(p, OUTPUT);
  Serial.println("Rodas no ar? A comecar em 3s.");
  delay(3000);
}
void parar() {
  analogWrite(ENA, 0); analogWrite(ENB, 0);
  digitalWrite(IN1, LOW); digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW); digitalWrite(IN4, LOW);
}

void loop() {
  Serial.println("frente");
  digitalWrite(IN1, HIGH); digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH); digitalWrite(IN4, LOW);
  analogWrite(ENA, VEL); analogWrite(ENB, VEL);
  delay(2000); parar(); delay(800);

  Serial.println("re");
  digitalWrite(IN1, LOW); digitalWrite(IN2, HIGH);
  digitalWrite(IN3, LOW); digitalWrite(IN4, HIGH);
  analogWrite(ENA, VEL); analogWrite(ENB, VEL);
  delay(2000); parar(); delay(800);

  Serial.println("esquerda (so a roda direita gira)");
  digitalWrite(IN3, HIGH); digitalWrite(IN4, LOW);
  analogWrite(ENB, VEL);
  delay(1500); parar(); delay(800);

  Serial.println("direita (so a roda esquerda gira)");
  digitalWrite(IN1, HIGH); digitalWrite(IN2, LOW);
  analogWrite(ENA, VEL);
  delay(1500); parar(); delay(2000);
}
