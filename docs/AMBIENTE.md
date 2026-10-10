# Ambiente de referência

Todo o código deste repositório foi preparado para estas versões. Outras versões exigem nova verificação: opções e funções podem mudar. Se a verificação falhar, compare primeiro as versões.

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
| Partition Scheme | Default 4MB with spiffs (1.2MB APP/1.5MB SPIFFS) |

Se a sua placa for de outra variante, use o tamanho de flash e o tipo de PSRAM indicados pelo fabricante. Os programas deste livro não precisam de PSRAM.

> **Se o monitor série ficar mudo** depois de gravar, confira primeiro o **USB CDC On Boot**. Com ele desligado, o programa corre mas as mensagens não chegam à porta USB nativa.

## Monitor série

Selecione **115200** no Monitor Série. Essa velocidade deve corresponder à UART quando ela for usada; na USB CDC nativa, não define a velocidade elétrica da USB. Confira também a porta selecionada, o cabo de dados e se a gravação terminou.

## Ligar a placa

Use a porta marcada **USB** (a nativa do ESP32-S3), com um cabo **de dados**. Se a gravação parar em `Connecting...`, segure o botão **BOOT** até começar a escrever.

Com a placa alimentada por USB, deixe o pino 5V separado da saída externa do LM2596. Os periféricos podem usar o LM2596 com GND comum. Para alimentar a placa pelo LM2596, desconecte o USB e siga a documentação do modelo.
