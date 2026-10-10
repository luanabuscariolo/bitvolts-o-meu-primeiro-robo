# Registo de alterações

Correções ao código que acompanha o livro. A versão do repositório corresponde à edição do livro.

## [Em revisão] — 2026-10-10

- O evento de caminho livre permanece pendente até que o envio seja aceito.
- A escrita do display respeita 21 caracteres por linha, divide palavras longas e continua frases maiores em novas páginas.
- A seleção aleatória considera o tamanho de cada tabela de frases.
- A apresentação consulta a fila durante as pausas e a pulsação dos LEDs.
- O exemplo da fila passa a demonstrar interrupção cooperativa com processamento de 4000 ms e cooldown de 3000 ms; informa falhas de criação da fila e das tarefas.

Verificação desta revisão: testes locais de lógica com periféricos simulados.
A compilação para ESP32-S3 desta revisão e sua execução no robô ainda não foram repetidas; o registro abaixo corresponde à versão anterior.

## [1.0.0] — 2026-10-08

Primeira versão pública, para a 1.ª edição de *BitVolts — O meu primeiro robô*.

- Programas curtos dos capítulos 4, 10, 13, 15 e 16.
- `teste_corpo_completo` para os capítulos 11 e 12.
- Firmware final `grump_v3` com frases predefinidas, para os capítulos 19 e 20.
- Tabela de ligações, lista de compras e diagramas de referência.

### Corrigido em relação ao texto impresso

- `teste_leds`: acrescentado `pinMode(LED_AMARELOS, OUTPUT)` no início do `loop()`. Sem ele, a partir da segunda repetição os LEDs amarelos não acendiam na fase contínua, porque o `analogWrite` do fim do ciclo deixa o pino preso ao PWM.
- `grump_v3`: o `enum Expressao` passou de `cerebro.ino` para `tipos.h`. Sem isso o firmware não compilava (`'Expressao' does not name a type`) — o mesmo erro e a mesma solução descritos no capítulo 19.

### Verificação

Todos os programas foram compilados para `ESP32S3 Dev Module` (USB CDC On Boot = Enabled, USB Mode = Hardware CDC and JTAG, Flash 16MB, PSRAM OPI), com o pacote esp32 3.3.11, ESP32Servo 3.2.1 e U8g2 2.36.19: 13 de 13 sem erros e sem avisos no código do repositório. A compilação repete-se automaticamente no GitHub a cada alteração.

Compilar prova que o código está bem escrito para a placa e as bibliotecas declaradas; o comportamento no robô foi validado no protótipo da autora.
