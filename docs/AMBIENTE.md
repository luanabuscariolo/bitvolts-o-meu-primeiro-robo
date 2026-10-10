# Ambiente de referência

Todo o código deste repositório foi preparado para estas versões. Com versões mais recentes os programas devem funcionar, mas opções e funções podem mudar. Se a verificação falhar, compare primeiro as versões.

## Software

| O quê | Versão | Onde obter |
|---|---|---|
| Arduino IDE | 2.3.10 | [releases do Arduino IDE](https://github.com/arduino/arduino-ide/releases/tag/2.3.10) |
| Pacote **esp32** by Espressif Systems | 3.3.11 | Gestor de Placas do IDE |
| **ESP32Servo** (Kevin Harrington, John K. Bennett) | 3.2.1 | Gestor de Bibliotecas do IDE |
| **U8g2** (Oliver Kraus) | 2.36.19 | Gestor de Bibliotecas do IDE |

Endereço para **URLs adicionais para o Gestor de Placas** (Additional Boards Manager URLs):

```
https://espressif.github.io/arduino-esp32/package_esp32_index.json
```

## Opções da placa

Em **Ferramentas → Placa → esp32**, escolha **ESP32S3 Dev Module**. Não escolha *ESP32 Dev Module*, que é outra família.

| Opção | Valor (placa N16R8) |
|---|---|
| USB CDC On Boot | **Enabled** |
| USB Mode | Hardware CDC and JTAG |
| Flash Size | 16MB |
| PSRAM | OPI PSRAM |

Se a sua placa for de outra variante, use o tamanho de flash e o tipo de PSRAM indicados pelo fabricante. Os programas deste livro não precisam de PSRAM.

> **Se o monitor série ficar mudo** depois de gravar, confira primeiro o **USB CDC On Boot**. Com ele desligado, o programa corre mas as mensagens não chegam à porta USB nativa.

## Monitor série

Velocidade **115200** em todos os programas.

## Ligar a placa

Use a porta marcada **USB** (a nativa do ESP32-S3), com um cabo **de dados**. Se a gravação parar em `Connecting...`, segure o botão **BOOT** até começar a escrever.
