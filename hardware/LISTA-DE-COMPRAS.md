# Lista de compras

> Apêndice D do livro *BitVolts — O meu primeiro robô*. Em caso de divergência, vale o livro.

Para imprimir e levar.

## Eletrónica principal

- [ ] 1 placa de desenvolvimento ESP32-S3 compatível com DevKitC-1, módulo N16R8, pinagem conferida
- [ ] 1× Cabo USB-C de dados
- [ ] 1× Display OLED SH1106 128×64 SPI (7 pinos)
- [ ] 1× Sensor ultrassónico HC-SR04
- [ ] 1× Servo SG90
- [ ] 1× Ponte H L298N (módulo)
- [ ] 1× Buzzer piezo passivo compatível com acionamento por GPIO de 3,3 V

## Mecânica

- [ ] 1× Chassi 2WD
- [ ] 2 motores DC com redução e rodas compatíveis. Confira a tensão admitida: na montagem original, BAT+ alimenta VS do L298N e a bateria 2S chega a 8,4 V carregada; veja o capítulo 5
- [ ] 2× Roda para motor TT
- [ ] 1× Roda boba
- [ ] 1× Suporte para o sensor no servo

## Alimentação

- [ ] 1 bateria de íons de lítio 18650 2S, 7,4 V nominais, em pacote protegido; escolha a capacidade em mAh conforme autonomia e espaço e confira a corrente de descarga admitida
- [ ] 1 carregador indicado para esse pacote de íons de lítio 2S, com final de carga em 8,4 V, corrente e conector compatíveis
- [ ] 1× Módulo regulador LM2596
- [ ] 1× Capacitor eletrolítico 1000 µF 25 V

## Componentes passivos

- [ ] 6× LED 5 mm — 2 verdes, 2 vermelhos, 2 amarelos
- [ ] 6× Resistor 220 Ω
- [ ] 3× Resistor 1 kΩ
- [ ] 1× Resistor 100 kΩ
- [ ] 1× Resistor 47 kΩ

## Montagem

- [ ] PCB perfurada: apenas se escolher a montagem soldada
- [ ] Pinos macho 2,54 mm (uma tira)
- [ ] Fios adequados à corrente de bateria, motores e servo; jumpers para sinais e pequenas cargas
- [ ] Fios jumper macho-macho, macho-fêmea e fêmea-fêmea
- [ ] Termorretrátil ou fita isoladora
- [ ] 1 protoboard para testes de sinais, divisores e pequenas cargas

## Ferramentas

- [ ] Multímetro (obrigatório)
- [ ] Ferro de soldar e estanho: apenas para a opção soldada, com prática prévia
- [ ] Alicate de corte
- [ ] Chave de fendas pequena
- [ ] Descarnador de fios (opcional)
- [ ] Terceira mão (opcional)

## Comprar em etapas

1. **Display, sons e LEDs:** placa, USB de dados, SH1106 SPI, piezo, seis LEDs, seis resistores de 220 Ω, protoboard, jumpers e multímetro.
2. **Alimentação, sensor e servo:** pacote 2S e carregador, LM2596, capacitor de 1000 µF/25 V, HC-SR04, SG90, suporte do sensor, três resistores de 1 kΩ, um de 100 kΩ e um de 47 kΩ. Prepare os fios da alimentação externa.
3. **Motores e montagem:** chassi com motores, rodas e roda boba, L298N e fios de alimentação. Para o barramento soldado, acrescente placa perfurada, fio rígido, pinos e material de soldagem.

O pacote de bateria já inclui as células. Não compre suporte ou células separados para essa opção. A montagem original usou um pacote reaproveitado de células 14500, 2S, 7,4 V e 500 mAh. O pacote 18650 recomendado para compra pode oferecer maior capacidade, mas tamanho e mAh não garantem a corrente de descarga necessária.

A protoboard recebe os sinais e pequenas cargas. Não faça a corrente dos motores ou do servo atravessar seus contatos. Se uma peça recebida exigir pinos ou fios soldados, prepare-a com ajuda de alguém com prática antes do teste.

## Cuidados na compra

**Especificações para a compra**

| Componente | O que confirmar |
|---|---|
| Placa | Que é S3 e N16R8 |
| Display | SH1106, não SSD1306. SPI, não I²C |
| Buzzer | Passivo, não ativo |
| Capacitor | 1000 µF, tensão nominal acima de 5 V; referência: 25 V |
| Bateria | Pacote 2S de 7,4 V, capacidade, dimensões, corrente de descarga e proteção compatíveis |
| Cabo USB | Que seja de dados |

Confira essas características no anúncio e na ficha técnica antes de comprar.
