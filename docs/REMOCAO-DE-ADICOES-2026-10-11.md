# Remoção de adições não autorizadas

## Regra da autora

A revisão deve tornar educativo o projeto existente. Não acrescentar componentes, circuitos, fontes ou funcionalidades sem autorização expressa. Esta instrução substitui sugestões anteriores de ampliar ou modificar o hardware. Se houver incompatibilidade técnica, explicar e registrar a pendência; não redesenhar o projeto por iniciativa própria.

## O que foi retirado

1. Capacitor de 100 nF no monitor da bateria, introduzido indevidamente na revisão. Retirado do texto do Word, compras, tabelas, diagramas e comentário do sketch de teste. O divisor voltou a conter apenas 100 kΩ e 47 kΩ, com o ponto intermediário no GPIO 1. A contagem de pontos do GND lógica foi corrigida para 15, incluindo a ponte.
2. Proposta de fonte ou regulador adicional para os motores. Removida das explicações, tabelas, compras e checklist. Mantida a ligação original BAT+ → VS/12V do L298N. Permanece a explicação da necessidade de conferir a tensão admissível dos motores; a remoção da proposta não comprova a compatibilidade de qualquer motor TT.
3. Referência restante a terminais de parafuso no barramento e sua tabela. A autora já havia solicitado retirar bornes e fixadores da compra. A referência foi retirada do Word; os terminais que pertencem ao próprio módulo L298N permanecem nas figuras.

## Comparação com o projeto original

Foram consultados os dois Word originais de setembro, em Documents/Codex/2026-09-11/referenced-chatgpt-conversation-this-is-an-2/outputs: BitVolts-O-meu-primeiro-robo.docx e BitVolts-O-meu-primeiro-robo-circuitos-e-capitulos.docx. O capacitor de 100 nF não consta nesses originais. O capacitor eletrolítico de 1000 µF/25 V, o piezo passivo, a protoboard e o suporte do sensor já estavam previstos; foram mantidos. A recomendação da bateria 18650 também foi explicitamente solicitada pela autora.

O primeiro commit do repositório de alunos já continha o capacitor indevido, portanto não foi usado sozinho como prova de que o componente pertencia ao projeto. A base editada continua sendo o Word atual da conversa, não o livro antigo do repositório. Não foi encontrada outra adição de hardware na comparação das listas e ligações examinadas.

## Arquivo vigente

- Word local: ROOT/outputs/BitVolts-livro-revisado-final.docx. ROOT é o diretório de trabalho já identificado em CONTEXTO-PARA-CLAUDE.md.
- A cópia ROOT/outputs/BitVolts-revisao-manual.docx tem o mesmo conteúdo.
- SHA-256: 475d07a82916020873f34347e3b2291361af41fe65b006f22c6ce23e2d4b0515.
- 178 páginas; 20 capítulos e sete apêndices; 67 tabelas, 67 figuras e 65 seções em retrato.
- O DOCX comercial permanece fora do repositório público.

## Validação desta correção

O Word foi aberto pela biblioteca de documentos, validado como pacote ZIP íntegro e renderizado novamente com LibreOffice isolado, sem COM. A primeira remoção mudou 17 páginas; todas foram inspecionadas. O complemento mudou somente as páginas 45, 69 e 106, também inspecionadas; as outras 175 ficaram pixel a pixel idênticas à renderização imediatamente anterior. Em relação à entrega anterior à remoção, 18 páginas foram alteradas e as outras 160 preservam a revisão visual anterior. A paginação permanece em 178 páginas.

Os 49 blocos de código do Word permanecem iguais à base revisada; os nove links de sketches apontam para arquivos existentes na branch. Nesta correção, nenhuma instrução executável foi alterada: no teste da bateria, apenas o comentário de ligação e a referência da figura foram atualizados. Não foi realizado novo ensaio físico ou nova compilação nesta rodada. As verificações de compilação registradas anteriormente pertencem à revisão de 10 de outubro.

Uma busca nos XML do DOCX e nos materiais atuais de hardware e exemplos confirmou a ausência de instruções para instalar o capacitor de 100 nF ou uma fonte adicional para os motores. As referências em relatórios e no changelog são histórico da adição indevida e da sua retirada, não instruções de montagem.

## Continuidade

Preservar as correções didáticas e de código já autorizadas. Não reintroduzir as adições removidas. As pendências técnicas ou editoriais anteriores continuam descritas no contexto e na revisão manual; esta rodada resolve a remoção de escopo e não equivale a um novo teste completo de bancada ou certificação de prontidão comercial.
