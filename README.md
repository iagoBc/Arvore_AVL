# Árvore AVL em C

Implementação de uma árvore binária de busca balanceada (AVL) em C, com
inserção, remoção e rebalanceamento automático via rotações simples e
duplas, garantindo altura O(log n) mesmo em sequências de inserção
adversárias.

## Funcionalidades

- **Inserção** (`incluir`) e **remoção** (`excluir`) de chaves inteiras,
  com busca binária para localizar a posição/nó correto.
- **Rebalanceamento automático** (`balancear`) após cada inserção ou
  remoção, cobrindo os 4 casos clássicos de desbalanceamento:
  - Rotação simples à esquerda / à direita
  - Rotação dupla esquerda-direita / direita-esquerda
- **Remoção com os três cenários** de nó folha, nó com um filho e nó com
  dois filhos (substituição pelo antecessor, isto é, o maior valor da
  subárvore esquerda).
- **Impressão em ordem** da árvore, mostrando cada chave junto do seu
  nível na árvore.

## Estrutura do projeto

| Arquivo | Responsabilidade |
| --- | --- |
| `main.c` | Ponto de entrada: lê operações da entrada padrão e imprime a árvore ao final |
| `avl.c` | Implementação das operações da árvore (inserção, remoção, rotações, balanceamento) |
| `avl.h` | Definição da struct `No`, da struct `arvore` e assinaturas das funções |
| `Makefile` | Compila o projeto gerando o binário `myavl` |
| `AVL.pdf` | Relatório técnico descrevendo a implementação (inclusão, exclusão, balanceamento e rotações) |

## Como compilar e executar

```bash
make
./myavl
```

## Formato de entrada

O programa lê operações da **entrada padrão (stdin)**, uma por linha, no
formato:

```
<operação> <chave>
```

Onde `<operação>` é:
- `i` — insere a chave na árvore
- `r` — remove a chave da árvore

Exemplo:

```
i 10
i 20
i 30
i 5
i 15
r 20
```

Pode ser digitado interativamente (finalizando com `Ctrl+D`) ou fornecido
via redirecionamento/pipe:

```bash
./myavl < entrada.txt
# ou
printf "i 10\ni 20\ni 30\ni 5\ni 15\nr 20\n" | ./myavl
```

## Formato de saída

Ao final da leitura (EOF), o programa imprime a árvore resultante em
**ordem simétrica** (in-order), uma chave por linha, no formato:

```
<chave>,<nível>
```

Para o exemplo de entrada acima, a saída é:

```
5,2
10,1
15,0
30,1
```

Ou seja: `15` é a raiz (nível 0), `10` e `30` são seus filhos (nível 1), e
`5` é filho de `10` (nível 2) — a árvore permanece balanceada mesmo após a
remoção do `20`.

## Complexidade

Como a árvore é mantida balanceada a cada inserção/remoção, as operações
de busca, inserção e remoção têm complexidade **O(log n)** no pior caso,
diferente de uma árvore binária de busca comum, que pode degenerar para
O(n) em sequências de entrada ordenadas.

## Autor

Iago Cardoso Bariuka — Ciência da Computação @ UFPR
