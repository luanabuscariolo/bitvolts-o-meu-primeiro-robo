# Firmware

Dois programas completos. Cada pasta é um sketch: abra o `.ino` com o mesmo nome da pasta.

## `teste_corpo_completo/` — capítulos 11 e 12

Todos os componentes ligados ao mesmo tempo, num único núcleo, com frases fixas no display. Serve para confirmar que a alimentação aguenta tudo junto **antes** de fixar as peças no chassi.

Só passe à montagem definitiva se este programa correr sem reinícios.

## `grump_v3/` — capítulos 19 e 20

O firmware final do robô. Cinco arquivos na mesma pasta:

| Arquivo | O que contém | Quando se mexe |
|---|---|---|
| `grump_v3.ino` | Arranque: cria a fila e as duas tarefas | Quase nunca |
| `config.h` | Pinos e constantes de comportamento | **Para ajustar o robô** |
| `tipos.h` | Os marcadores e o estado partilhado | Quase nunca |
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

Estão no topo do `cerebro.ino`, agrupadas por situação. Mude-as à vontade — é o que dá personalidade ao robô. **Escreva sem acentos**: o programa desenha o texto byte a byte, e uma letra acentuada ocupa dois bytes — no display aparecem símbolos estranhos no lugar dela.

### Ajustar o comportamento

O capítulo 20 explica a ordem certa. As constantes mais usadas, todas em `config.h`:

| Constante | O que controla |
|---|---|
| `DIST_OBSTACULO_CM` | A que distância o robô considera um obstáculo |
| `VEL_CRUZEIRO` | Velocidade a andar em frente (0–255) |
| `VEL_MANOBRA` | Velocidade nas curvas |
| `TEMPO_CURVA_MS` | Quanto tempo dura cada curva |
| `COOLDOWN_MARCADOR_MS` | Intervalo mínimo entre falas |
| `BAT_V_FRACA` | Tensão abaixo da qual o robô para |

Mude **uma de cada vez**, grave e observe.
