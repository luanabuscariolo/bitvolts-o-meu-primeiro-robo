# Revisão manual BitVolts — 11 de outubro de 2026

## Estado desta entrega

Word: `ROOT/outputs/BitVolts-livro-revisado-final.docx`.
ROOT continua sendo o diretório definido em CONTEXTO-PARA-CLAUDE.md.
SHA-256: `ccfdd3d9d0270b940ff706a311921259782d7b6161961b93f9b3c91d050ed315`.

O documento tem **178 páginas na renderização conferida**, 20 capítulos, sete apêndices, 67 tabelas e 67 figuras. A fonte foi o Word de 182 páginas entregue em 10 de outubro, SHA-256 `4b1c5211f228f4fa9df68d4db3ab2b31467384da0757138cba3e6d29f5f14fde`. O livro antigo do repositório não foi usado como base. O DOCX comercial continua fora do repositório público.

## Observações da autora aplicadas

- As 27 aberturas de capítulos e apêndices receberam tipografia maior e desenho branco de contorno simples sobre #222362. A capa principal foi preservada byte a byte; o laranja #F3A537 continua no restante da identidade.
- O capítulo 1 apresenta os dois núcleos com linguagem mais acessível. Escopo, experiência desejável e preparação foram reunidos no final: computador, cabo de dados, Arduino IDE, GitHub, internet para instalação e acesso ao código. O livro guia um projeto e não promete um curso completo de programação, eletrônica ou soldagem.
- O capítulo 2 passou a “Um pouquinho de teoria antes da prática”, incluindo sumário e cabeçalhos.
- Tensão, corrente, resistência, série/paralelo e GND receberam composição com componentes reconhecíveis, polaridade e caminhos de ligação.
- A bateria reutilizada do protótipo é identificada como 14500, 2S, 7,4 V e 500 mAh. A compra foi simplificada para pacote protegido de íons de lítio 18650 2S com carregador compatível. Capacidade em mAh, corrente de descarga, dimensões e tensão de carga foram distinguidas; 18650 não garante, pelo tamanho sozinho, corrente suficiente.
- Removidos bornes e fixadores separados da lista, a imposição de peças previamente soldadas e a seção de verificação de peças já possuídas.
- Acrescentados protoboard, resistor e suporte do HC-SR04 à apresentação das peças. Lista de compras e apêndice alinhados; três etapas ilustradas, com o resultado de cada etapa.
- Regulador apresentado com a mesma arte que identifica IN+/IN− e OUT+/OUT−, eliminando duplicação.
- Resistores ilustrados com faixas dos valores usados: 220 Ω, 1 kΩ, 100 kΩ e 47 kΩ. Quantidades: seis, três, um e um.
- Ferramentas redesenhadas com silhuetas reconhecíveis, incluindo ferro de solda.
- A figura de opções do Arduino IDE não destaca mais Partition Scheme: Custom como requisito. Foram mantidas as capturas reais e versões exatas da autora.
- Alimentação, divisor de bateria, ECHO na protoboard, retorno dos motores, quatro nós, testes individuais, jumpers do L298N e mapas gerais receberam ligações até os terminais. Cruzamentos sem ponto não significam emenda. Os componentes reaproveitam o desenho vetorial existente.
- As ilustrações de sinais e pequenos componentes não autorizam passar corrente de motores ou servo pelos contatos comuns da protoboard. A placa perfurada tem ilhas que precisam de fio e solda; as duas vistas do GND lógica representam o mesmo nó.
- Descrições extensas foram colocadas como texto editável no Word, inclusive em conhecer a placa, conceitos de tarefas, criação de tarefa, fila, espera e ajuste de comportamento. Nas figuras existentes, recortes nativos do Word preservam a parte visual sem duplicar a explicação.
- Acrescentado o caminho exato e clicável para cada um dos nove programas completos impressos, na branch codex/correcoes-bitvolts.

## Outros problemas corrigidos durante a conferência

- Tabela de comparação de baterias: cabeçalho branco legível e formatação consistente.
- Linha acrescentada do suporte HC-SR04: estilo e bordas alinhados às demais.
- Fontes e legendas mantidas junto das figuras; tabela OLED e imagem ajustadas para caberem juntas.
- Removidos restos cortados de rótulos de GND na figura das fileiras positivas.
- Nota local explica o asterisco de VS: BAT+ no L298N somente quando os motores admitem a alimentação de até 8,4 V; motores de 3–6 V exigem o ramo adaptado do capítulo 5.
- Sequência BOOT/RESET corrigida e unificada no capítulo de ambiente, diagnóstico e apêndice F.
- Medições de resistência e continuidade exigem USB e bateria desligados. Na investigação do divisor ADC, desligar antes de separar o GPIO.
- Correção da afirmação de que um capacitor resolveria qualquer tremor de servo; alimentação, pulsos e folgas mecânicas são causas distintas.
- Especificação de piezo passivo compatível com GPIO de 3,3 V também nas tabelas e compras, evitando a compra genérica de buzzer inadequado.
- Legenda de polaridade alinhada à arte, que inclui piezo.
- Explicação do retorno dos motores reposicionada junto da solução.
- Removido verbete remanescente de bloco de parafuso.
- Sumário: 27 números de página atualizados, preservando campos e links.
- Espaçamento do apêndice E ajustado para eliminar uma página quase vazia com o último aviso. Total passou de 179 páginas intermediárias para 178.

## Processo e validação

1. Fonte preservada; alterações localizadas no DOCX, sem reconstrução do documento.
2. Artes nativas SVG editadas e renderizadas em PNG para o Word. Foram gerados 54 assets locais, incluindo as 27 aberturas.
3. Renderização por LibreOffice 26.2.6 isolado, sem automação COM do Word. PDF usado apenas para conferência.
4. Conferência visual integral das 179 páginas intermediárias, seguida de novas renderizações após correções. Na última comparação, 164 páginas permaneceram pixel a pixel iguais à versão conferida; as 14 páginas diferentes da versão final foram abertas e examinadas novamente, incluindo as páginas deslocadas pela remoção da página quase vazia.
5. Verificação de integridade ZIP do DOCX e abertura com python-docx passaram. Todas as 65 seções permanecem verticais. Não foram encontradas páginas totalmente vazias, cortes ou sobreposições na versão final inspecionada.
6. Os 49 blocos de código impresso permanecem exatamente iguais aos da fonte técnica anterior. Os nove programas completos correspondem ao repositório desconsiderando comentários e espaços; os nove caminhos existem.
7. Nenhum arquivo de firmware foi alterado nesta rodada. As 13 compilações e os 14 testes com interfaces simuladas pertencem à etapa anterior, descrita no contexto de 10/10; não são apresentados como testes novamente executados em 11/10.
8. Diagramas públicos sincronizados em SVG e PNG: mapa de sinais, mapa de alimentação, quatro nós, sensor sem solda e divisor de bateria. Documentação de ambiente, ligações e compras atualizada.
9. Artefatos de trabalho e evidências locais estão em `ROOT/work/revisao-manual-2026-10-11`: changes.json, final-qa-changes.json, validation.json e render-final. Scripts antigos não foram executados indiscriminadamente.
10. Problemas de execução encontrados: o renderizador precisou de permissão de processo/arquivos temporários do ambiente; um XPath do script final precisou de namespace explícito. Ambos foram corrigidos antes da entrega. A autora reiterou que já autoriza o uso do LibreOffice; não pedir confirmação repetida para essa mesma finalidade.

## O que ainda depende de verificação física e decisão de lançamento

- Executar a revisão técnica do firmware no robô real: sensores, sentido dos motores, servo, ADC calibrado, partida, navegação, eventos e frases.
- Registrar os modelos e limites reais dos motores e da bateria escolhida, corrente de partida, funcionamento da proteção, capacidade do regulador e temperaturas sob carga. O funcionamento anterior do protótipo não valida automaticamente qualquer conjunto de componentes comprado pelo aluno.
- A ligação direta BAT+ → VS é condicional à tensão admissível dos motores. O texto explica a condição; isso não equivale a ensaio físico de uma nova montagem.
- O print do monitor serial com execução real continua dependente do hardware/captura. Não foi fabricado um resultado de execução.
- A autora pode fazer a leitura de prova do novo DOCX. Os links de testes apontam para a branch de correção existente; antes de mudar a branch ou consolidar uma versão de lançamento, preservar esses caminhos ou atualizar os links.
- Não houve merge na branch principal. A conclusão editorial desta rodada não é certificação de segurança elétrica nem comprovação de novos testes de bancada.
