# Registo de alterações

Correções ao código que acompanha o livro. A versão do repositório corresponde à edição do livro.

## [Correção de escopo] — 2026-10-11

- Retirado o capacitor de 100 nF do divisor da bateria: foi introduzido na revisão sem fazer parte do projeto original. Removido das instruções, compras, comentário do teste e diagramas.
- Retirada a proposta de uma fonte ou regulador adicional para os motores. Mantida a montagem original e a explicação de que é necessário conferir a tensão admissível dos motores.
- O divisor original usa apenas os resistores de 100 kΩ e 47 kΩ, com o ponto entre eles no GPIO 1.
- Nenhuma instrução executável de firmware foi alterada nesta correção. A revisão deve explicar o projeto existente; não acrescentar componentes, circuitos ou funcionalidades sem autorização expressa.

## [Em revisão] — 2026-10-10

- Teste do servo começa no centro, com limites ampliados manualmente após conferência.
- Diagnóstico integrado usa a mesma leitura calibrada em milivolts e atenuação dos demais testes.
- Ausência de eco ou leitura fora da faixa mantém os motores parados, sem presumir caminho livre.
- Bateria verificada antes do primeiro movimento; diagnóstico interrompido se o limiar for atingido sob carga.
- Criação das duas tarefas conferida e início coordenado por notificações; motores desabilitados na falha.
- Removido o estado global sem consumidor e corrigidas as descrições de fila, cooldown e tempo de ciclo.

- O evento de caminho livre permanece pendente até que o envio seja aceito.
- A escrita do display respeita 21 caracteres por linha, divide palavras longas e continua frases maiores em novas páginas.
- A seleção aleatória considera o tamanho de cada tabela de frases.
- A apresentação consulta a fila durante as pausas e a pulsação dos LEDs.
- O exemplo da fila passa a demonstrar interrupção cooperativa com processamento de 4000 ms e cooldown de 3000 ms; informa falhas de criação da fila e das tarefas.

Verificação desta revisão: 13 de 13 sketches compilados para ESP32-S3, com esp32 3.3.11, ESP32Servo 3.2.1 e U8g2 2.36.19. Passaram também 14 cenários de lógica em C++ com periféricos, filas e relógio simulados. Esses cenários não são execução em hardware. A execução desta revisão no robô ainda precisa ser repetida.

Ilustrações do barramento atualizadas com os componentes e terminais de cada nó. Acrescentado o exemplo do sensor e divisor na protoboard, com os furos identificados e orientação para blocos de distribuição sem solda.

Registro histórico: esta revisão chegou a incluir um filtro de 100 nF no divisor da bateria. Essa adição indevida foi retirada na correção de escopo de 11/10 acima.

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
