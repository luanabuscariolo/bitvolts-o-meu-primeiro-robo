# Firmware

Dois programas completos. Cada pasta é um sketch: abra o `.ino` com o mesmo nome da pasta.

## `teste_corpo_completo/` — capítulos 11 e 12

Todos os componentes ligados ao mesmo tempo, num único núcleo, com frases fixas no display. Serve para confirmar que a alimentação aguenta tudo junto **antes** de fixar as peças no chassi.

Faça o diagnóstico com **rodas suspensas**: a comparação de tensão aciona os motores antes da próxima leitura frontal. Esse teste não mede a corrente de motores travados nem garante a alimentação em qualquer piso.

Antes de gravar, copie os ângulos calibrados e o fator do teste 9. O teste integrado e o firmware final usam agora a mesma conversão `analogReadMilliVolts` e a mesma atenuação. Um fator medido com o antigo cálculo a partir de `analogRead` precisa ser recalculado.

Só passe à montagem definitiva depois de conferir movimento, leituras e alimentação sem reinícios nem aquecimento anormal.

## `grump_v3/` — capítulos 19 e 20

O firmware final do robô. Cinco arquivos na mesma pasta:

| Arquivo | O que contém | Quando se mexe |
|---|---|---|
| `grump_v3.ino` | Arranque: cria a fila e as duas tarefas | Quase nunca |
| `config.h` | Pinos e constantes de comportamento | **Para ajustar o robô** |
| `tipos.h` | Os marcadores e as expressões dos olhos | Quase nunca |
| `navegacao.ino` | O corpo — núcleo 0: sensor, motores, servo, LEDs, buzzer, bateria | Problemas de movimento |
| `cerebro.ino` | O rosto e a fala — núcleo 1: display, olhos, frases | Problemas de display |

Abra **só o `grump_v3.ino`**. O Arduino IDE encontra os outros quatro na mesma pasta e mostra-os em separadores.

### Antes de gravar: ponha os seus valores

Em `config.h`, troque estas constantes pelos valores que mediu no capítulo 10:

```cpp
#define ANG_CENTRO       85     // servo a apontar para a frente
#define ANG_ESQUERDA     140
#define ANG_DIREITA      30
#define BAT_FATOR_CALIB  1.00   // o fator que calculou no teste 9
```

No `teste_bateria` esse fator chama-se `FATOR_CALIB`; aqui chama-se `BAT_FATOR_CALIB`. É a mesma calibração.

### As frases

Estão no topo do `cerebro.ino`, agrupadas por situação. Mude-as ou acrescente variantes — a seleção usa a quantidade de cada tabela. O texto ocupa duas linhas de até 21 caracteres; frases maiores continuam em outra página. A navegação mantém sua tarefa enquanto o display escreve. **Escreva sem acentos**: o programa desenha o texto byte a byte, e uma letra acentuada ocupa dois bytes — no display aparecem símbolos estranhos no lugar dela.

### Ajustar o comportamento

O capítulo 20 explica a ordem certa. As constantes mais usadas, todas em `config.h`:

| Constante | O que controla |
|---|---|
| `DIST_OBSTACULO_CM` | A que distância o robô considera um obstáculo |
| `VEL_CRUZEIRO` | Velocidade a andar em frente (0–255) |
| `VEL_MANOBRA` | Velocidade nas curvas |
| `TEMPO_CURVA_MS` | Quanto tempo dura cada curva |
| `COOLDOWN_MARCADOR_MS` | Intervalo entre eventos normais; envios forçados ignoram este intervalo |
| `BAT_V_FRACA` | Tensão abaixo da qual o robô para |

Mude **uma de cada vez**, grave e observe.

### Comportamentos que devem ser conferidos

- Sem eco ou distância fora da faixa de 2–400 cm: motores param e o sensor é consultado novamente. Ausência de eco pode significar distância grande, superfície que não reflete bem ou falha de ligação; não comprova caminho livre.
- Na varredura, ambos os lados precisam ter uma leitura válida para escolher a direção.
- A bateria é medida antes do primeiro movimento e nas verificações periódicas. Manobras podem atrasar a próxima leitura; a proteção 2S continua necessária.
- Se a fila ou uma tarefa não puder ser criada, os motores permanecem desabilitados. As tarefas só iniciam depois de ambas terem sido criadas.
- As pausas da navegação cedem tempo ao sistema, mas o sensor não é lido continuamente durante a ré, a varredura, os sons e a curva. Use piso livre, longe de bordas e escadas.

A fila transmite somente `Marcador`, um evento por item. Esta versão não usa uma estrutura global compartilhada entre as tarefas.
