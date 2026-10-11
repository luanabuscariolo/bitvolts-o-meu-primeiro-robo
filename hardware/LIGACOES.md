# Tabela de todas as ligações

> Apêndice C do livro *BitVolts — O meu primeiro robô*. Use a edição do livro correspondente à branch descarregada. Se uma ligação divergir, interrompa a montagem e confira a correção publicada antes de energizar.

Referência completa, fio a fio. Vale imprimir e riscar cada linha à medida que confirma a ligação no robô.

## Microcontrolador → componentes (sinal)

**GPIOs e componentes**

| GPIO | Vai para | Componente |
|---|---|---|
| 1 | Fio do meio do divisor 100k/47k | Monitor de bateria |
| 2 | Resistor 220 Ω → ânodo | LED vermelho direito |
| 4 | TRIG | HC-SR04 |
| 5 | Fio do meio do divisor 1k/1k/1k | HC-SR04 ECHO |
| 6 | Fio laranja | Servo SG90 |
| 7 | Pino + | Buzzer passivo |
| 8 | CS | Display |
| 9 | DC | Display |
| 10 | RES | Display |
| 11 | MOSI | Display |
| 12 | CLK | Display |
| 13 | ENB | L298N |
| 15 | ENA | L298N |
| 16 | IN1 | L298N |
| 17 | IN2 | L298N |
| 18 | IN3 | L298N |
| 21 | IN4 | L298N |
| 39 | Dois ramos em paralelo, cada um com resistor 220 Ω + LED | LEDs amarelos |
| 40 | Resistor 220 Ω → ânodo | LED verde esquerdo |
| 41 | Resistor 220 Ω → ânodo | LED verde direito |
| 42 | Resistor 220 Ω → ânodo | LED vermelho esquerdo |

O GPIO 3 é um pino de configuração de arranque (strapping) e não deve ser tratado como livre para qualquer ligação. Antes de expandir, confira os pinos reservados, a memória do módulo, a USB nativa e a documentação da sua placa.

## Trilho BAT+ · 7,4 V

**Nó BAT+**

| Ponto | Ligação |
|---|---|
| Entrada | Bateria positivo |
| Saída | LM2596 IN+ |
| Saída | L298N VS/12V: somente com motores compatíveis com até 8,4 V; caso contrário, adaptar a fonte dos motores |
| Saída | R1 (100 kΩ) do monitor de bateria |

## Trilho 5 V lógica

**Nó de 5 V**

| Ponto | Ligação |
|---|---|
| Entrada | LM2596 OUT+ |
| Saída | Microcontrolador pino 5V, somente com USB desconectado |
| Saída | HC-SR04 VCC |
| Saída | Servo fio vermelho |
| Saída | L298N pino 5V |
| Saída | Capacitor 1000 µF, terminal positivo (+) |

## Trilho GND lógica

**GND lógica**

| Componente | Ponto |
|---|---|
| Microcontrolador | GND |
| Display | GND |
| HC-SR04 | GND |
| Servo | Fio castanho |
| Buzzer | Pino − |
| Divisor do ECHO | R3, perna livre |
| Divisor da bateria | R2, perna livre |
| Capacitor | Terminal negativo (−), marcado pela faixa no corpo |
| 6 LEDs | Cátodos; conferir a face achatada ou a ficha se as pernas foram cortadas |
| Filtro ADC 100 nF | Uma perna ao GPIO 1; a outra ao GND lógica |

## Trilho GND potência

**GND potência**

| Componente | Ponto |
|---|---|
| Bateria | Negativo |
| LM2596 | IN−/OUT−, internamente comuns; uma ligação adequada ao barramento |
| L298N | GND |

Ponte: um fio grosso e curto entre GND potência e GND lógica.

## Potência dos motores

**Ramo de potência dos motores**

| De | Para |
|---|---|
| Fonte dos motores | L298N VS/12V. BAT+ só com motores compatíveis até 8,4 V; senão, fonte regulada adequada |
| L298N OUT1 + OUT2 | Motor esquerdo |
| L298N OUT3 + OUT4 | Motor direito |

## Display — alimentação

**Alimentação do display**

| Pino | Vai para |
|---|---|
| VCC | Pino 3V3 do microcontrolador (fio direto) |
| GND | Trilho GND lógica |

## Divisores

ECHO — proteção do GPIO 5: três resistores de 1 kΩ em série.

**Divisor do ECHO**

| Ponto | Ligação |
|---|---|
| Topo (R1) | HC-SR04 ECHO |
| Entre R1 e R2 | GPIO 5 |
| Base (R3) | GND lógica |

Bateria — monitor no GPIO 1: 100 kΩ + 47 kΩ.

**Divisor da bateria**

| Ponto | Ligação |
|---|---|
| Topo (R1 = 100 kΩ) | Trilho BAT+ |
| Entre R1 e R2 | GPIO 1 |
| Base (R2 = 47 kΩ) | GND lógica |

## Jumpers do L298N

No módulo ilustrado, remova 5V_EN, ENA e ENB. Confira os nomes na serigrafia, pois podem variar entre módulos.

O pino 5V passa a ser alimentado pelo LM2596.

## Diagramas

- [Pinagem dos sinais](diagramas/pinagem.png)
- [Mapa completo dos sinais](diagramas/mapa-sinais.png)
- [Mapa completo da alimentação](diagramas/mapa-alimentacao.png)
- [Os quatro nós do barramento](diagramas/quatro-nos.png)


No LM2596, **IN+ / IN−** são a entrada da bateria; **OUT+ / OUT−** são a saída regulada de 5 V. Os negativos são comuns neste módulo. Confira as inscrições reais, pois a posição dos terminais varia.

Os mapas mostram os fios nos terminais dos componentes. GND lógica e GND potência têm caminhos separados e uma ponte curta entre eles. Pontos marcam junções; cruzamentos sem ponto são fios separados, representados com um intervalo branco. A disposição é organizada para leitura e não representa o chassi. No mapa de sinais, E e D indicam os lados esquerdo e direito do robô; as alimentações e os motores são completados no mapa seguinte.

Com USB conectado, mantenha o 5 V externo separado do pino 5V da placa, como descrito em [AMBIENTE.md](../docs/AMBIENTE.md).

Para testar o divisor do ECHO com 5 V, mantenha ECHO e GPIO 5 desconectados dessa entrada temporária. Remova os 5 V e desligue a alimentação antes de fazer a ligação final ao sensor e ao GPIO.

- [Divisor da bateria com retorno e filtro](diagramas/divisor-bateria.png)

## Montagem sem solda

A figura dos quatro nós amplia fileiras da placa perfurada e mostra os terminais que chegam a elas. Cada fileira precisa ser unida com fio e solda: os furos de uma perfboard comum são ilhas separadas. As duas vistas de GND lógica representam o mesmo nó. A montagem do barramento exige prática ou ajuda de alguém que saiba soldar.

Os testes de sinais e pequenos componentes podem usar protoboard. Mantenha bateria, motores e servo em fios e conexões adequados à corrente, fora dos contatos da protoboard. Prepare previamente as peças que precisarem de fios ou pinos soldados.

- [Exemplo do sensor e do divisor na protoboard](diagramas/sensor-sem-solda.png)

Este exemplo marca os furos dos três resistores de 1 kΩ e completa VCC, GND e TRIG nos terminais físicos dos componentes. Servo e motores usam conectores externos adequados, sem atravessar os contactos da protoboard. O mapa completo dos sinais continua a indicar as ligações dos restantes componentes.
