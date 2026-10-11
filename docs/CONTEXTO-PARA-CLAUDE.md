# Contexto da revisão do livro BitVolts para continuidade no Claude

## Atualização de 11 de outubro de 2026 — ler primeiro

A revisão manual posterior está concluída nesta rodada. O Word atual é **ROOT/outputs/BitVolts-livro-revisado-final.docx**, renderizado e conferido em **178 páginas**. O arquivo de 182 páginas descrito abaixo é a fonte preservada de 10/10. Consulte [Revisão manual de 11/10](REVISAO-MANUAL-2026-10-11.md) para todas as alterações desta rodada, hash do DOCX, evidências e pendências físicas. As 13 compilações e 14 testes simulados abaixo pertencem à etapa anterior; nenhum firmware foi modificado nesta rodada. A branch continua sendo codex/correcoes-bitvolts e o Word comercial permanece fora do repositório público.

## Registro histórico de 10 de outubro

Registro de 10 de outubro de 2026. Autora: Luana Buscariolo. Projeto: **BitVolts — O meu primeiro robô**, um robô autônomo com frases sarcásticas predefinidas. Este documento atualiza o parecer que apontava problemas no livro e descreve o que foi efetivamente feito depois dele.

## Estado atual e conclusão

Existe um Word revisado, renderizado em **182 páginas**, e uma branch pública de correções com os programas, documentação e diagramas atualizados. Foram compilados **13 de 13 sketches para ESP32-S3** e passaram **14 cenários de lógica com interfaces simuladas**. Os nove sketches completos impressos no Word correspondem aos arquivos atuais do repositório, desconsiderando comentários e espaços.

**A revisão corrigida ainda não foi executada novamente no robô físico.** O protótipo anterior da autora funcionava; isso não comprova automaticamente a revisão atual. A montagem elétrica de referência também continua exigindo fechamento de especificações e validação sob carga. A palavra “final” no nome do Word identifica o arquivo entregue nesta etapa; não é uma certificação de que todos os critérios de venda estejam satisfeitos.

Este é um registro de continuidade técnica e editorial, não uma transcrição literal de cada mensagem ou chamada de ferramenta. A revisão anterior e o parecer permanecem úteis, mas vários de seus bloqueios já foram resolvidos, como indicado abaixo.

## Pedidos e decisões da autora

- Entregar o livro em Word editável. PDF e imagens de páginas servem apenas para conferência interna.
- Continuar o documento atual desta conversa, preservando capítulos, capa, aberturas, voz e identidade visual: azul `#222362` e laranja `#F3A537`.
- Fazer correções localizadas. Não reconstruir o livro nem executar scripts antigos indiscriminadamente.
- Não usar COM do Word como dependência. Empregar uma alternativa concreta de conversão quando necessário.
- Manter arte simples, chapada, com cores sólidas e silhuetas reconhecíveis. A autora rejeitou artes confusas e telas inventadas que não correspondiam à aplicação.
- Não pressupor conhecimentos que ainda não foram apresentados. Explicar a primeira ocorrência, fornecer exemplos completos e ser honesto sobre o apoio que um iniciante pode precisar.
- Incluir alternativa sem solda, sem fazer motores e servo passarem pelos contatos da protoboard.
- Usar links oficiais legíveis e clicáveis; manter endereços e caminhos utilizáveis em impressão. A autora pediu atenção à apresentação de referências segundo ABNT, sem descaracterizar o ebook.
- Informar versões exatas, sem “.x”.
- Disponibilizar código em repositório público. Não prometer um pacote ZIP produzido pela autora. Digitar os programas curtos continua recomendado para aprendizagem, mas é opcional.
- Retirar comentários dispensáveis do código impresso; os comentários de apoio podem permanecer no repositório.
- Cabeçalho: título do livro à esquerda e capítulo atual à direita, sem nome da autora no final.
- Preservar liberdade de organização no chassi quando couberem as peças; registrar que o barramento do protótipo ficou embaixo para organizar os fios.
- Preferir termos amplamente reconhecidos, como watchdog, sem traduções artificiais.
- Investigar conteúdo, código, contradições e qualidade didática com rigor de uma avaliação de bancada.

A autora inicialmente pediu apenas armazenamento de observações, depois uma comparação sem alterações e, posteriormente, autorizou as correções em branch. A etapa atual corresponde à autorização para corrigir e registrar, não ao período de somente observação.

## Repositório e histórico Git

- Repositório público: [luanabuscariolo/bitvolts-o-meu-primeiro-robo](https://github.com/luanabuscariolo/bitvolts-o-meu-primeiro-robo).
- Branch de teste/correção usada nesta conversa: **`codex/correcoes-bitvolts`**. Não foi criada uma segunda branch chamada “teste”.
- Base preservada: `65d5cde7b12d785199c6363e6ea36e37daa5c16c`, registro do material recebido.
- Não houve merge para a branch principal nem criação de PR nesta etapa.
- O diretório original `F:/GitHub/bitvolts-o-meu-primeiro-robo` permaneceu preservado. A comparação dos arquivos do snapshot recebido não identificou alterações no original.
- O diretório inicial da sessão `F:/GitHub/nano-grump-v3` não é o checkout do material de alunos usado para essas correções.

| Commit | Alteração registrada |
|---|---|
| `65d5cde` | Material recebido registrado sem alterações. |
| `594ffbc33e7e2dca043617850b4e1d87b0924b90` | Eventos pendentes, quebra/paginação de frases, seleção de variantes e demonstração de fila. |
| `fd3e3b06b3c71b809b9bb4470fc53aa6e8c5b4cb` | Diagnóstico integrado, arranque, servo, ADC, documentação e mapas de montagem sincronizados com o livro. |
| `6373200` | Diagrama dos quatro nós e exemplo sem solda, com SVGs/PNGs e documentação. |

Os três commits de correção acima já haviam sido enviados ao GitHub antes deste registro de continuidade. Este Markdown recebe seu próprio commit na mesma branch. Seu hash deve ser consultado no histórico Git; não é inserido antecipadamente no próprio arquivo.

O repositório público contém o código e material de apoio aos alunos. O ebook comercial não foi acrescentado ao repositório público; seu conteúdo revisado está no Word local indicado a seguir.

## Arquivos e versão correta do livro

Para interpretar os caminhos locais, use:

```text
ROOT = C:/Users/luana_qf6csq7/.codex/visualizations/2026/10/05/01a10e0b-fb37-7a31-bebb-89b27e66ae9f/bitvolts-finalizacao
ANTERIOR = C:/Users/luana_qf6csq7/Documents/Codex/2026-10-05/referenced-chatgpt-conversation-this-is-an
CHECKOUT = ROOT/work/repositorio-correcao
WORD_ATUAL = ROOT/outputs/BitVolts-livro-final.docx
```

O arquivo atual foi obtido desta sequência:

1. `BitVolts-livro-revisado_2.docx`, citado pela autora como documento desta conversa.
2. Revisões ilustradas anteriores, consolidadas em `ANTERIOR/outputs/BitVolts-ilustracoes-revisadas.docx`.
3. `ROOT/outputs/BitVolts-revisao-tecnica.docx`, revisão cruzada com o repositório, renderizada em 181 páginas.
4. `ROOT/outputs/BitVolts-revisao-visual.docx`, correções de prints, diagramas e tabelas, renderizada em 182 páginas.
5. `ROOT/outputs/BitVolts-livro-final.docx`, cópia idêntica do item anterior entregue à autora.

**Não foi usado um livro antigo do repositório como fonte do Word atual.**

SHA-256 do Word entregue:

```text
4b1c5211f228f4fa9df68d4db3ab2b31467384da0757138cba3e6d29f5f14fde
```

SHA-256 da fonte ilustrada anterior preservada:

```text
ad5e722a7caf73e0c203747fb7ed0e490b823a42d4d62fb6bd12e6caeb585565
```

O parecer antigo está em `ANTERIOR/outputs/Parecer-tecnico-pedagogico-BitVolts.md`, datado de 7 de outubro, relativo à edição de 179 páginas. Referências a páginas desse parecer não devem ser aplicadas literalmente à versão atual.

## Ambiente de desenvolvimento efetivamente conferido

| Item | Versão/configuração |
|---|---|
| Arduino IDE das capturas da autora | 2.3.10 |
| Arduino CLI usada nas compilações | 1.5.1 |
| Pacote esp32 by Espressif Systems | 3.3.11 |
| ESP32Servo | 3.2.1 |
| U8g2 | 2.36.19 |
| Placa de referência | ESP32-S3 DevKitC-1, variante N16R8 |
| Board no IDE | ESP32S3 Dev Module |
| USB CDC On Boot | Enabled |
| USB Mode | Hardware CDC and JTAG |
| Flash Size | 16MB |
| PSRAM | OPI PSRAM |
| Partition Scheme usada para os sketches | Default 4MB with spiffs (1.2MB APP/1.5MB SPIFFS) |

FQBN registrada:

```text
esp32:esp32:esp32s3:USBMode=hwcdc,CDCOnBoot=cdc,FlashSize=16M,PSRAM=opi
```

Pontos que causavam confusão:

- “Arduino ESP32 Boards by Arduino” e “esp32 by Espressif Systems” são pacotes diferentes; a edição usa o segundo.
- “ESP32 Dev Module” não é a seleção da placa ESP32-S3 do projeto.
- A captura real da autora mostra Partition Scheme = Custom, proveniente de outra configuração. O texto e a anotação esclarecem que não se deve copiar esse valor para estes programas.
- Flash e PSRAM dependem da variante. O firmware de frases não carrega um modelo de linguagem, arquivos de pesos ou dados na PSRAM.
- COM12 é o exemplo do computador da autora; o aluno deve identificar sua própria porta.
- 115200 deve corresponder à UART quando utilizada. Na USB CDC nativa esse valor não define a velocidade elétrica da USB.

## Correções de código realizadas

### Eventos, fila e apresentação no display

Arquivos principais: `firmware/grump_v3/cerebro.ino`, `navegacao.ino`, `tipos.h` e `exemplos/cap16/teste_fila/teste_fila.ino`.

1. **Evento de caminho livre perdido:** o estado era considerado comunicado mesmo quando o envio não tinha sido aceito. O evento passa a permanecer pendente até o envio aceito; tentativas recusadas não o reconhecem como entregue.
2. **Frases e palavras longas:** corrigidos os casos que excediam a largura ou não avançavam corretamente. A escrita respeita 21 caracteres por linha, divide palavras maiores e continua em outra tela quando as duas linhas ficam cheias.
3. **Variantes de frases:** a escolha aleatória passou a usar a quantidade de entradas de cada tabela. Acrescentar uma quarta variante não a deixa inacessível por um tamanho fixo antigo.
4. **Interrupção de uma frase:** a fila é consultada durante pausas da escrita, pulsação dos LEDs e manutenção da tela pronta. Um novo marcador pode interromper a apresentação cooperativamente.
5. **Contrato da fila:** transmite somente `Marcador`, um item por vez. Não transmitir `EstadoRobo` por uma fila dimensionada com `sizeof(Marcador)`. O estado global sem consumidor foi removido; `volatile` não foi apresentado como sincronização.
6. **Cooldown:** o texto foi sincronizado com o código. Envios forçados ignoram repetição/cooldown; aumentar o cooldown não espaça esses envios nem garante que todo aviso apareça. A fila de um item pode substituir um evento pendente.
7. **Demonstração de fila:** processamento de 4000 ms e cooldown de 3000 ms permitem observar interrupção. Alterar para 6000 ms permite conclusão no agendamento nominal. O exemplo completo informa falhas de criação da fila e tarefas.
8. **Saída serial ilustrativa:** retiradas afirmações de que o firmware imprime tempos e “forçado” que não fazem parte das mensagens reais. A ordem entre tarefas e os números de varredura exemplificados são identificados como ilustrativos.

O firmware atual desenha texto byte a byte. As frases devem permanecer sem acentos nesta implementação. Não foi acrescentado suporte UTF-8 completo.

### Sensor, bateria, servo e arranque

1. **Ausência de eco:** deixa de equivaler a caminho livre. No firmware corrigido, eco ausente ou distância fora de 2–400 cm provoca parada e nova tentativa. A escolha do lado exige leituras válidas dos dois lados.
2. **Calibração do servo:** o exemplo inicial começa com os três ângulos em 90 graus. A autora/aluno amplia os limites manualmente após conferir centro e folga. A antiga varredura automática de 30–150 graus não era uma descoberta de limites seguros.
3. **ADC inconsistente:** diagnóstico integrado e firmware final passaram a usar `analogReadMilliVolts` e a mesma atenuação dos testes de bateria.
4. **Fator antigo:** o valor 1,056 obtido pelo cálculo anterior não deve ser copiado automaticamente. Refazer a comparação com multímetro; `FATOR_CALIB` no teste corresponde a `BAT_FATOR_CALIB` no integrado/final com a mesma conversão.
5. **Primeiro movimento:** a bateria é verificada antes do primeiro acionamento dos motores. No diagnóstico, a comparação sob carga interrompe o procedimento quando o limiar é atingido.
6. **Falha de recursos:** fila e tarefas têm resultado de criação conferido. Os motores permanecem desabilitados diante da falha.
7. **Arranque coordenado:** cada tarefa aguarda uma notificação; só é liberada depois de ambas terem sido criadas. Isso evita executar a navegação com a apresentação ainda incompleta.
8. **Limites da navegação:** as pausas de ré, sons, servo e curva ainda podem adiar novas leituras frontais e a verificação periódica da bateria. A revisão não converteu toda a navegação em uma máquina de estados sem pausas.

### Correções que já estavam no material recebido

O changelog da base já registrava dois defeitos encontrados anteriormente:

- `teste_leds`: reconfigurar `LED_AMARELOS` como `OUTPUT` no início do `loop()`, para voltar de PWM a controle digital na repetição seguinte. A versão impressa foi sincronizada.
- `enum Expressao`: colocado em `tipos.h`, visível antes das assinaturas que o utilizam, corrigindo `'Expressao' does not name a type`.

Essas mudanças não devem ser atribuídas ao último commit de diagramas. Foram preservadas e incluídas nas verificações da revisão.

## Correções técnicas e pedagógicas no Word

- Repositório, branch e caminhos reais incluídos; diagnóstico integrado e firmware final passaram a ser confrontados com arquivos disponíveis.
- Indicados os exemplos completos dos capítulos 15 e 16 para praticar tarefas/fila antes do firmware. Fragmentos foram diferenciados dos sketches completos que podem ser gravados.
- Acrescentadas explicações iniciais de chaves, `setup()`, `loop()`, `#define`, tipos, `for`, `if` e ponto e vírgula, sem exigir que o capítulo 13 fosse removido.
- Corrigida a referência que atribuía escrita de frases ao programa de LED do capítulo 13.
- Apresentada também a organização cooperativa por estados/`millis()`, para explicar a escolha de FreeRTOS sem falsear a alternativa.
- Corrigida a transição do divisor de ECHO: teste temporário com 5 V, ECHO e GPIO desligados; desligar alimentação, retirar 5 V de teste e conectar ECHO/GPIO na montagem final.
- Eliminada a comparação incorreta de consumo dos resistores. Dois resistores de 1 kΩ mudariam a divisão da bateria e produziriam 4,2 V na junção com 8,4 V de entrada; não são uma substituição admissível de 100 kΩ/47 kΩ.
- Corrigidas afirmações de que aquecimento sem carga prova sozinho falha interna do LM2596.
- Diagnósticos serial/display/sensor passaram a considerar hipóteses e verificações, em vez de atribuir um sintoma a uma causa única. Display em branco não foi reduzido a rotação.
- O relato da retirada do XL6009 conserva os resultados relatados do protótipo, mas não atribui uma causa única sem ensaio que isole bateria, contatos, módulo, carga e estado de carga.
- USB e 5 V externo: pino 5V do ESP32 separado do regulador durante alimentação USB; para alimentar a placa pelo LM2596, USB desconectado. O texto orienta conferir a documentação da placa.
- Explicados IN+/IN− e OUT+/OUT− do LM2596. Os negativos são comuns no módulo ilustrado.
- A compra de motores continua condicionada à faixa real da alimentação: BAT+ pode chegar a 8,4 V. Motores TT de 3–6 V exigem adaptação adequada; a queda do L298N não é garantia suficiente.
- Removidos comentários dispensáveis dos sketches impressos; mantidos no material de apoio quando úteis.
- Corrigidas tabelas sobre cooldown, fila, mensagens, calibração e ligação do pino 5V.
- Corrigida a distribuição dos LEDs entre tarefas: verdes/vermelhos na navegação; amarelos na apresentação.
- Corrigida a tabela que confundia duração de frase com tempo ocupando o processador: há cessão de tempo entre palavras; não existe duração fixa universal de 2240 ms.
- O tamanho de pilha em `xTaskCreatePinnedToCore` foi explicado em bytes no ESP32. Nome, parâmetro de entrada e handle foram diferenciados; prioridade não é velocidade nem número de núcleo.

## Ilustrações e capturas reais

### Capturas do Arduino IDE

A autora forneceu oito capturas de 10 de outubro. Sete foram usadas como referência visual anotada; a captura “Sobre” confirma a versão. Não foi fabricado um print do Monitor Série que ela não conseguiu fornecer.

| Sufixo do arquivo PNG | Uso |
|---|---|
| 151956 | Editor, Verificar, Carregar e seletor de placa. |
| 151850 | Janela Sobre: evidência da versão 2.3.10/CLI 1.5.1. |
| 152324 | Gestor de placas, pacote Espressif 3.3.11. |
| 154214 | ESP32Servo 3.2.1. |
| 154236 | U8g2 2.36.19. |
| 153843 | Seleção ESP32S3 Dev Module. |
| 153925 | Porta marcada no menu Tools → Port. |
| 154416 | Opções da placa S3. |

Arquivos originais em `C:/Users/luana_qf6csq7/OneDrive/Desktop/Captura de ecrã 2026-10-10 HHMMSS.png`.

As anotações usam setas e caixas **DrawingML nativas do Word**, editáveis. O recorte é definido por OOXML e os PNGs originais permanecem incorporados sem alteração de seus bytes. A presença dos sete PNGs foi verificada por SHA-256 no pacote DOCX.

Páginas atuais: 34–40. Figuras 21A/21B mostram ambas as bibliotecas e 22A/22B distinguem placa e porta.

### Diagramas refeitos ou corrigidos após o parecer

- Mapas completos de sinais e alimentação: divisores representados, seis ramos de LEDs, retorno L/P, ponte dos GNDs e distinção entre conexão e cruzamento. No capítulo 19 ocupam páginas próprias, atualmente 138 e 139.
- Divisor de bateria: BAT+, BAT−, GPIO1, retorno comum e filtro de 100 nF.
- Caixa de um item: obstáculo pendente substituído por curva, com eventos concretos, em vez de letras abstratas.
- Três regras: mudança, cooldown de eventos normais e interrupção da apresentação; envio forçado contorna as duas primeiras.
- Ajuste de curva: corrigido corte e comparação que alterava duas variáveis; PWM mantido em 200, tempo comparado de 450 para 250 ms.
- Sensor sem solda, página 65: R1 b3–b6, R2 d6–d9 e R3 b9–b12, todos 1 kΩ. ECHO entra em a3, GPIO5 na junção e6, GND em a12. VCC, GND e TRIG são completados por ligações nomeadas.
- Quatro nós, página 67: componentes e seus terminais ligados a quatro faixas distintas na placa verde; BAT+, 5 V, GND lógica e GND potência. Ponte curta entre os GNDs, OLED alimentado separadamente por 3V3.
- Perfboard: furos não são unidos por si só. Sem solda, usar blocos de distribuição com contatos comuns ou pontes especificadas. Bloco de parafusos comum não torna automaticamente todos os contatos um nó.
- Corrigida a bateria do novo desenho dos quatro nós para o pack fechado da arte existente. A aparência continua não comprovando proteção interna do produto comprado.
- Corrigido o capacitor cerâmico de 100 nF: não tem indicação artificial de polo negativo.
- Duas tarefas, página 115: sensor/motor e display associados a linhas do tempo, com fila e acontecimentos; preservadas pausas próprias da navegação.
- Ciclo de tarefa, página 119: preparação, medir, decidir validade, atualizar ou parar, pausa gerida pelo FreeRTOS e repetição.
- Sete argumentos de criação, página 120: chamada real com função, nome, pilha, NULL, prioridade, handle e núcleo.
- Espera, página 133: Running → Blocked → Ready → Running; outra tarefa ou idle usa o núcleo. O fim do prazo não garante execução imediata.

Os desenhos mantêm os componentes do acervo vetorial e as cores da marca. Não são fotografias nem uma certificação do posicionamento dos terminais de todo módulo vendido.

## Processo de revisão e problemas encontrados durante a execução

1. Inventário e comparação da versão da conversa, repositório recebido, exemplos e documentação técnica.
2. Preservação do original e criação/publicação do repositório com branch de correção.
3. Correções em lotes, ensaios de lógica, compilação nativa e sincronização do Word com os arquivos reais.
4. Substituição das telas inventadas pelos prints reais e revisão dos diagramas.
5. Conversão do Word usando **LibreOffice portátil** e `render_docx.py`, sem COM.
6. Extração de texto e comparação de geometria/conteúdo, seguida de inspeção visual das páginas.
7. Iterações de diagramação, atualização dos números em cache do sumário e entrega.

Problemas de execução que foram tratados:

- O parecer antigo registrava falha do compilador nativo deste Windows por DLL antes de analisar o sketch. A situação foi superada no ambiente usado depois: existem resultados reais de compilação para ESP32-S3. Não continuar dizendo que só houve WebAssembly.
- As primeiras tentativas de anotação em VML não preservaram a aparência desejada na renderização; foi adotado DrawingML nativo.
- Algumas setas de anotação apontavam para a linha errada ou cobriam informações do menu. Alvos de seletor de versão, flash, partição, PSRAM, USB Mode e porta foram reposicionados e conferidos no print/renderização.
- A primeira paginação da última etapa ficou em 183 páginas, com uma página esparsa no fim do capítulo 14. O diagrama foi compactado preservando textos e componentes; a tabela seguinte voltou à página anterior e o total final passou a 182.
- A revisão das tabelas revelou, já no fechamento, a divergência dos LEDs amarelos e a confusão entre duração da fala/ocupação da CPU. Ambas foram corrigidas antes da renderização final.
- Arquivos Markdown escritos no Windows geraram diffs por CRLF; foram normalizados para LF antes do commit.
- Um caminho de trabalho inválido criou um arquivo auxiliar em um diretório `undefined`; o arquivo foi movido para a pasta de trabalho correta. Não há mudança funcional no projeto associada a esse incidente.
- Scripts auxiliares que substituem imagens, acrescentam parágrafos ou atualizam TOC não são todos idempotentes. Reexecutá-los pode duplicar texto ou sobrescrever uma etapa posterior; eles não devem ser tratados como uma pipeline pronta.

## Verificações realizadas e seus limites

### Compilação nativa

Passaram estes 13 sketches, com as versões e FQBN declaradas:

1. `exemplos/cap04/primeiro_teste`
2. `exemplos/cap10/teste_bateria`
3. `exemplos/cap10/teste_buzzer`
4. `exemplos/cap10/teste_display`
5. `exemplos/cap10/teste_leds`
6. `exemplos/cap10/teste_motores`
7. `exemplos/cap10/teste_sensor`
8. `exemplos/cap10/teste_servo`
9. `exemplos/cap13/estudar_led`
10. `exemplos/cap15/teste_dois_nucleos`
11. `exemplos/cap16/teste_fila`
12. `firmware/grump_v3`
13. `firmware/teste_corpo_completo`

Relatório local: `ROOT/work/native-compile-results.json`; logs em `ROOT/work/build-check`. Existe workflow `.github/workflows/compilar.yml` no repositório com versões fixadas. Este registro não afirma que foi consultado um resultado recente do GitHub Actions; a prova utilizada aqui é a compilação local.

### Lógica simulada

Os testes compilam C++ para WebAssembly e substituem periféricos, filas e relógio. Não emulam eletricamente o ESP32-S3, PWM real, escalonamento real ou alimentação.

| Cenário | Evidência exercitada |
|---|---|
| clear_retry | Caminho livre continua pendente até envio aceito. |
| long_text | Palavra de 105 caracteres termina e conserva o conteúdo em trechos. |
| long_word | Palavra de 25 caracteres é dividida sem perder caracteres. |
| phrases | As 27 frases atuais cabem nas linhas/páginas; texto vazio não fica preso. |
| more_variants | Quarta variante selecionável; tamanhos independentes. |
| interruption | Fila consultada nas pausas de escrita, LEDs e manutenção da tela. |
| sensor_unknown | Sem eco/fora da faixa são desconhecidos; conversões válidas preservadas. |
| battery_consistent | Conversões do integrado e final coincidem para 7,4 e 6,2 V simulados. |
| servo_center_first | Primeiro teste só comanda 90 graus. |
| startup_failure | Arranque normal mantém motores baixos antes de liberar tarefas. |
| startup_task_failure_1 | Falha da primeira tarefa não libera movimento. |
| startup_task_failure_2 | Falha da segunda tarefa não libera movimento. |
| startup_queue_failure | Falha da fila mantém motores desabilitados. |
| queue_demo_timing | 4000 ms > 3000 ms demonstra interrupção; 6000 ms permite conclusão nominal. |

Relatório final: `ROOT/work/batch2-test-results.json`. O relatório `batch1-test-results.json` é anterior e não substitui o final.

### Integridade e paginação do Word

- Pacote ZIP do DOCX íntegro e abertura com biblioteca de documentos bem-sucedida.
- Conversão/renderização concreta bem-sucedida em LibreOffice.
- 1827 parágrafos, 67 tabelas e 65 seções em orientação vertical.
- 182 páginas na renderização final.
- 27 entradas do sumário correspondem às aberturas dos 20 capítulos e sete apêndices.
- Nove sketches completos impressos correspondem aos arquivos do repo, ignorando comentários/espaços. Isso não certifica automaticamente cada fragmento didático isolado.
- Sete PNGs originais das capturas preservados por hash no DOCX.
- Na comparação com a renderização de 181 páginas, 163 corpos de página permaneceram idênticos pela assinatura de texto/imagens/posição, excluindo rodapé.
- Inspeção integral das folhas de contato da renderização final e inspeção em tamanho de leitura das 19 páginas alteradas: **3, 34–40, 65–67, 115–116, 119–121 e 133–135**.
- As páginas preservadas já tinham sido examinadas na revisão anterior. Não interpretar a conferência final como uma nova leitura independente palavra por palavra de todas as 182 páginas.

Arquivos de evidência:

- `ROOT/work/visual4-integrity.json`
- `ROOT/work/visual4-delivery.json`
- `ROOT/work/visual4-toc.json`
- `ROOT/work/book-qa-visual4.json`
- `ROOT/work/page-text-visual4.json`
- Renderização final: `ROOT/work/render-visual4-entrega` — PDF e PNGs internos.

## Situação dos principais problemas do parecer anterior

| Problema do parecer de 7 de outubro | Situação após esta conversa |
|---|---|
| Firmware e diagnóstico indisponíveis | Resolvido quanto à disponibilidade, caminhos, revisão e compilação; bancada permanece pendente. |
| Montagem de referência incompleta | Parcial: condições elétricas esclarecidas e desenhos melhorados; especificações e carga real ainda precisam ser fechadas. |
| Transição de teste do divisor ambígua | Corrigida no procedimento e desenho. |
| LEDs falham após primeira repetição | Correção recebida preservada, Word sincronizado e compilação realizada; verificar fisicamente PWM/GPIO. |
| Marcador e EstadoRobo incompatíveis na fila | Corrigido para contrato somente Marcador e retirada do estado global sem consumidor. |
| Servo varre antes da calibração | Corrigido para centro e ampliação manual. |
| Cooldown não controla eventos forçados | Texto/tabelas corrigidos; comportamento descrito honestamente. |
| Conta incorreta dos resistores | Corrigida; substituição de valores que elevaria o GPIO foi explicitamente rejeitada. |
| Aquecimento sem carga prova falha interna | Afirmação corrigida. |
| Progressão não atende plenamente iniciante | Melhorada com base inicial e exemplos completos; teste com leitor iniciante ainda necessário. |
| Justificativa inadequada para duas tarefas | Corrigida referência ao capítulo 13 e apresentada alternativa cooperativa. |
| Diagnósticos excessivamente conclusivos | Corrigidos vários casos; não equivale a validar cada hipótese fisicamente. |
| Causa do problema do boost afirmada sem isolamento | Relato reescrito como evidência observada e hipótese causal. |
| Mapas insuficientes para montagem física | Parcial: completos por terminais/nós e protoboard do sensor; falta comprovar roteiro físico completo com conjunto definido. |
| Telas do IDE inventadas | Substituídas por capturas reais anotadas. Monitor Série real ainda não recebido. |
| Imagens pequenas/abstratas/cortadas | Diversas corrigidas: eventos, regras, curva, rotinas, tarefas, argumentos, espera e quatro nós. Demais pontos específicos devem ser reavaliados na versão atual. |

## O que falta antes de considerar o percurso pronto para venda

### Prioridade 1 — montagem elétrica reproduzível e bancada

1. Conferir o conjunto real existente e registrar modelos/especificações: motores, corrente de arranque/bloqueio, bateria protegida, capacidade de descarga, proteção 2S, carregador, LM2596, fios e conectores.
2. Fechar a solução para motores de 3–6 V, se forem esses os usados. Não orientar compra condicionada a uma adaptação que o livro ainda não entrega completamente.
3. Medir o comportamento do LM2596 e do pack na faixa de descarga, especialmente perto do limiar de 6,2 V, com servo/motores/display ativos. Não prometer 5 V estáveis em toda a faixa sem dados.
4. Repetir todos os testes no robô com a revisão corrigida: centro/limites do servo, sentido dos motores, LEDs contínuos/PWM, buzzer, display e leitura de bateria.
5. Testar uso simultâneo de servo, buzzer, PWM dos motores e LEDs; compilação não comprova ausência de conflito de recursos no hardware.
6. Verificar sem eco, obstáculos durante frases, eventos consecutivos, bateria baixa em repouso/sob carga e retorno após reinício. Registrar mensagens realmente observadas.
7. Confirmar alimentação USB versus externa conforme o esquema da placa real, sem inferir possibilidade de simultaneidade apenas pela medição do pino 5V.
8. Avaliar quedas rápidas e temperaturas quando houver instabilidade. Multímetro não comprova ausência de transitórios.

### Prioridade 2 — roteiro físico e teste com iniciante

1. Conferir se o mapa por terminais é suficiente para localizar cada pino nos módulos reais. Se necessário, acrescentar detalhes físicos anotados e uma montagem completa sem solda com peças definidas.
2. A alternativa sem solda atual reúne exemplo completo do sensor, blocos de distribuição e esquemas dos demais componentes; não foi construído/testado um novo protótipo inteiro dessa alternativa.
3. Reavaliar os pontos ainda citados no parecer: detalhe do barramento nas fotos, localização física dos três jumpers, detalhe legível do display e figuras antigas densas no capítulo 13/apêndice do boost. Não marcá-los todos como resolvidos só porque novas artes foram feitas.
4. Obter, se a autora quiser incluir, uma captura real do Monitor Série após gravar o programa correspondente. A instrução textual existe; a captura continua pendente.
5. Fazer alguém do público iniciante seguir o percurso e anotar dúvidas/necessidade de ajuda. O público pretendido não foi “certificado” por simulação.

### Prioridade 3 — fechamento editorial e distribuição

1. A autora deve revisar e aprovar as novas artes e textos.
2. Conferir o Word no ambiente de distribuição. Paginação pode variar por fontes/versão de Word; uma abertura sem erro não garante paginação idêntica à do LibreOffice.
3. Se houver mudança, renderizar novamente, conferir páginas afetadas e atualizar sumário. Não fixar para sempre o total de 182 páginas.
4. Conferir todas as referências e a normalização pretendida pela autora; não houve certificação formal de conformidade integral com ABNT.
5. Depois da bancada e aprovação, decidir integração da branch de teste e identificação da edição pública do código. A branch principal continua com o material recebido.
6. Rever as instruções transitórias “durante esta revisão, selecione codex/correcoes-bitvolts” quando houver uma edição oficial integrada/tagueada.
7. Não considerar o relato histórico do XL6009 uma comparação causal controlada. Só novas medições podem fechar essa hipótese.

## Como continuar sem perder as correções

Usar `WORD_ATUAL` e `codex/correcoes-bitvolts` como ponto de partida. Não aplicar novamente a lista de erros antiga como se nada tivesse sido corrigido. Consultar primeiro a tabela de situação e o diff Git.

Ferramentas/scripts locais existem em `ROOT/work`. São registros e auxiliares dos lotes, não comandos para executar automaticamente:

- `correct_code_batch2.py`, `correct_book_batch2.py`, `finalize_book_batch2.py` e `close_batch2.py`: revisão técnica.
- `build_visual4.py`, `render_visual4.cjs`, `native_annotations.py` e `update_book_visual4.py`: diagramas e anotações.
- `prepare_visual4_pagination.py`, `finish_visual4_assets.py`, `qa_visual4.py`, `check_visual4_integrity.py` e `close_visual4_delivery.py`: paginação, QA e fechamento.
- `sync_visual4_repo.py`: já executado; repetir acrescenta documentação duplicada.
- `update_book_visual4.py`: lê a versão técnica anterior; repetir agora pode sobrescrever refinamentos/TOC da versão entregue.

Runtime usado: Python e Node empacotados em `C:/Users/luana_qf6csq7/.cache/codex-runtimes/codex-primary-runtime/dependencies`. LibreOffice portátil em `ANTERIOR/work/LibreOffice/SourceDir/LibreOffice/program`. O renderer pertence à skill de documentos em `C:/Users/luana_qf6csq7/.codex/plugins/cache/openai-primary-runtime/documents/26.1007.11041/skills/documents/render_docx.py`.

Caso o Claude esteja em outro ambiente, os caminhos locais não estarão automaticamente disponíveis. Ele precisa receber o Word atual e trabalhar com a branch correta. Este Markdown fornece o contexto, mas não substitui os arquivos, relatórios de teste ou medições físicas.

O próximo trabalho substancial é fechar os critérios de bancada e as lacunas de reprodução por um iniciante, preservando as correções já feitas.
