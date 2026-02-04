# 🎮 Tetris Stack — Gerenciamento de Fila e Pilha de Peças (Nível Mestre)

## 📋 Visão Geral

Este projeto implementa, em **C**, a versão **Nível Mestre** do sistema de gerenciamento de peças do jogo educativo **Tetris Stack**. A solução combina duas estruturas de dados: uma **fila circular** para as peças futuras e uma **pilha** para as peças reservadas, além de operações avançadas de **troca entre fila e pilha**.

### 🎯 Objetivo

Aplicar conceitos avançados de estruturas de dados (fila + pilha) em um cenário interativo, incluindo **troca simples** e **troca múltipla** entre as estruturas.

## ✨ Funcionalidades Principais

| Operação                 | Código | Descrição                                            |
| ------------------------ | ------ | ---------------------------------------------------- |
| **Jogar Peça**           | `1`    | Remove a peça do início da fila (_dequeue_)          |
| **Reservar Peça**        | `2`    | Move a peça da fila para a pilha de reserva (_push_) |
| **Usar Peça Reservada**  | `3`    | Remove e usa a peça do topo da pilha (_pop_)         |
| **Trocar Peça Atual**    | `4`    | Troca a peça da frente da fila com o topo da pilha   |
| **Troca Múltipla (3x3)** | `5`    | Troca as 3 primeiras da fila com as 3 peças da pilha |
| **Sair**                 | `0`    | Encerra o programa                                   |

## 📦 Estrutura das Peças

Cada peça possui:

- **`nome`**: caractere indicando o tipo (`I`, `O`, `T` ou `L`)
- **`id`**: número inteiro único e sequencial

Exemplo: `[T 7]` = Peça tipo T com ID 7

## 🏗️ Arquitetura do Código

### Estruturas de Dados

```c
/**
 * @brief Representa uma peça individual do jogo
 */
typedef struct {
    char nome;  ///< Tipo: I, O, T, L
    int id;     ///< Identificador único
} Peca;

/**
 * @brief Fila circular para peças futuras
 */
typedef struct {
    Peca itens[MAX_FILA];  ///< Array de peças (MAX_FILA = 5)
    int inicio;            ///< Índice do primeiro elemento
    int fim;               ///< Índice do próximo espaço livre
    int total;             ///< Quantidade de peças na fila
} Fila;

/**
 * @brief Pilha linear para peças reservadas
 */
typedef struct {
    Peca itens[MAX_PILHA]; ///< Array de peças (MAX_PILHA = 3)
    int topo;              ///< Índice do topo da pilha
} Pilha;
```

### Funções Principais

#### Gerenciamento de Fila

- `void inicializarFila(Fila *f)` — Inicializa a fila vazia
- `int filaCheia(Fila *f)` — Verifica se a fila está cheia
- `int filaVazia(Fila *f)` — Verifica se a fila está vazia
- `void enfileirar(Fila *f, Peca p)` — Adiciona peça ao final da fila
- `int desenfileirar(Fila *f, Peca *p)` — Remove peça do início da fila
- `void mostrarFila(Fila *f)` — Exibe o estado da fila

#### Gerenciamento de Pilha

- `void inicializarPilha(Pilha *p)` — Inicializa a pilha vazia
- `int pilhaCheia(Pilha *p)` — Verifica se a pilha está cheia
- `int pilhaVazia(Pilha *p)` — Verifica se a pilha está vazia
- `int push(Pilha *p, Peca peca)` — Adiciona peça ao topo da pilha
- `int pop(Pilha *p, Peca *peca)` — Remove peça do topo da pilha
- `void mostrarPilha(Pilha *p)` — Exibe o estado da pilha

#### Trocas Avançadas

- `int trocarPecaAtual(Fila *f, Pilha *p)` — Troca a frente da fila com o topo da pilha
- `int trocaMultipla(Fila *f, Pilha *p)` — Troca 3 peças da fila com 3 da pilha preservando a ordem

#### Utilidades

- `Peca gerarPeca(void)` — Gera uma peça aleatória automaticamente

## 🎯 Conceitos Aplicados

### Fila Circular (FIFO)

- Reaproveitamento eficiente de espaço no array
- Operação circular usando `(indice + 1) % MAX_FILA`
- Mantém sempre 5 peças na fila
- A cada remoção da fila, uma nova peça é gerada automaticamente

### Pilha Linear (LIFO)

- Capacidade limitada a 3 peças
- Permite reservar peças para uso posterior
- Acesso apenas pelo topo (última peça inserida)

### Trocas Avançadas

- **Troca simples**: troca a peça da frente da fila com o topo da pilha
- **Troca múltipla**: troca as 3 primeiras peças da fila com as 3 peças da pilha
  - A ordem do topo da pilha é preservada ao entrar na fila
  - A ordem das peças da fila é preservada ao entrar na pilha

## 🚀 Como Usar

### Compilação

```bash
gcc -g tetris.c -o tetris.exe
```

### Execução

```bash
./tetris.exe
```

### Exemplo de Uso

```
=== Estado Atual ===

Fila de Pecas: [I 0] [L 1] [T 2] [O 3] [I 4]
Pilha de Reserva (Topo -> Base): [O 8] [L 7] [T 6]

Opcoes:
1 - Jogar peca da frente da fila
2 - Enviar peca da fila para reserva (pilha)
3 - Usar peca da reserva (pilha)
4 - Trocar peca da frente da fila com o topo da pilha
5 - Trocar os 3 primeiros da fila com as 3 pecas da pilha
0 - Sair

Opcao: 5

Acao: troca realizada entre os 3 primeiros da fila e os 3 da pilha.

=== Novo Estado ===

Fila de Pecas: [O 8] [L 7] [T 6] [O 3] [I 4]
Pilha de Reserva (Topo -> Base): [T 2] [L 1] [I 0]
```

## 🎓 Requisitos Cumpridos

### Funcionais

✅ Inicialização automática da fila com 5 peças  
✅ Inicialização da pilha com capacidade para 3 peças  
✅ Operações de jogar, reservar e usar peça reservada  
✅ Troca simples entre fila e pilha  
✅ Troca múltipla (3x3) entre fila e pilha  
✅ Geração automática de novas peças após remoções da fila  
✅ Exibição clara do estado atual

### Não Funcionais

✅ Interface clara e intuitiva  
✅ Código bem documentado  
✅ Mensagens de erro descritivas  
✅ Feedback visual imediato após cada ação

## 🔧 Detalhes Técnicos

### Capacidades

- **Fila**: 5 peças (fixo)
- **Pilha**: 3 peças (fixo)
- **Tipos de peças**: I, O, T, L (geradas aleatoriamente)

### Comportamento

- Peças removidas da fila ou pilha não voltam ao jogo
- A cada remoção da fila, uma nova peça é gerada automaticamente
- A troca múltipla só ocorre quando há pelo menos 3 peças na fila e na pilha

## 👨‍💻 Autor

Desenvolvido como parte das atividades de Estrutura de Dados - Tema 3: Pilhas e Filas.

---

**Status**: ✅ Funcionando corretamente  
**Última atualização**: 03/02/2026
