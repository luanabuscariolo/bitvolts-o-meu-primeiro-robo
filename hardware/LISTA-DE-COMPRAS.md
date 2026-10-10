# Lista de compras

> Apêndice D do livro *BitVolts — O meu primeiro robô*. Em caso de divergência, vale o livro.

Para imprimir e levar.

## Eletrónica principal

- [ ] 1 placa de desenvolvimento ESP32-S3 compatível com DevKitC-1, módulo N16R8, pinagem conferida e pinos já instalados para a opção sem solda
- [ ] 1× Cabo USB-C de dados
- [ ] 1× Display OLED SH1106 128×64 SPI (7 pinos)
- [ ] 1× Sensor ultrassónico HC-SR04
- [ ] 1× Servo SG90
- [ ] 1× Ponte H L298N (módulo)
- [ ] 1× Buzzer passivo

## Mecânica

- [ ] 1× Chassi 2WD
- [ ] 2 motores DC com redução e rodas compatíveis. Para BAT+ no VS do L298N, confirme alimentação máxima de 8,4 V; motores TT de 3–6 V exigem o ramo regulado específico do capítulo 5
- [ ] 2× Roda para motor TT
- [ ] 1× Roda boba
- [ ] 1× Suporte para o sensor no servo

## Alimentação

- [ ] Conjunto de duas células de lítio em série, com corrente de descarga adequada e proteção compatível; escolha o tamanho pelo espaço disponível e pela ficha técnica
- [ ] Escolha um pacote 2S protegido completo ou o conjunto de células equivalentes, suporte e proteção compatíveis; não compre células soltas adicionais se o pacote já as incluir
- [ ] Carregador compatível com o conjunto escolhido: pacote 2S conforme fabricante, ou carregamento individual das células removidas do suporte
- [ ] 1× Módulo regulador LM2596
- [ ] 1× Capacitor eletrolítico 1000 µF 25 V

## Componentes passivos

- [ ] 6× LED 5 mm — 2 verdes, 2 vermelhos, 2 amarelos
- [ ] 6× Resistor 220 Ω
- [ ] 3× Resistor 1 kΩ
- [ ] 1× Resistor 100 kΩ
- [ ] 1 capacitor cerâmico de 100 nF para o filtro de leitura da bateria
- [ ] 1× Resistor 47 kΩ

## Montagem

- [ ] PCB perfurada: apenas se escolher a montagem soldada
- [ ] Pinos macho 2,54 mm (uma tira)
- [ ] Fios e bornes de potência especificados para bateria, motores e servo; jumpers para sinais e pequenas cargas
- [ ] Fios jumper macho-macho, macho-fêmea e fêmea-fêmea
- [ ] Blocos de parafuso pequenos, para a alimentação dos motores
- [ ] Termorretrátil ou fita isoladora
- [ ] Abraçadeiras pequenas
- [ ] Protoboard e módulos com pinos já soldados para os testes sem solda

## Ferramentas

- [ ] Multímetro (obrigatório)
- [ ] Ferro de soldar e estanho: apenas para a opção soldada, com prática prévia
- [ ] Alicate de corte
- [ ] Chave de fendas pequena
- [ ] Descarnador de fios (opcional)
- [ ] Terceira mão (opcional)

## Comprar em etapas

As três etapas de compra e os testes possíveis com cada uma estão detalhados no capítulo 3 do livro. Use esta lista para conferir as quantidades e as especificações; não repita a compra de células se elas já vierem num pacote protegido completo.

## Cuidados na compra

**Especificações para a compra**

| Componente | O que confirmar |
|---|---|
| Placa | Que é S3 e N16R8 |
| Display | SH1106, não SSD1306. SPI, não I²C |
| Buzzer | Passivo, não ativo |
| Capacitor | 1000 µF, tensão nominal acima de 5 V; referência: 25 V |
| Células | Modelo e corrente de descarga compatíveis, com proteção adequada |
| Cabo USB | Que seja de dados |

Confira essas características no anúncio e na ficha técnica antes de comprar.
