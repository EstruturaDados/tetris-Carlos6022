# 🎮 Tetris Stack — Gerenciamento de Fila e Pilha de Peças (Nível Aventureiro)

## 📋 Visão Geral

Este projeto implementa, em **C**, uma simulação avançada do **gerenciamento de peças** no jogo educativo **Tetris Stack**. A solução combina duas estruturas de dados fundamentais: uma **fila circular** para as peças futuras e uma **pilha** para as peças reservadas, oferecendo ao jogador um sistema completo de gerenciamento estratégico de peças.

### 🎯 Objetivo

Simular o comportamento realista do sistema de reserva de peças em um jogo tipo Tetris, aplicando conceitos avançados de estruturas de dados (fila + pilha) em um contexto prático e interativo.

## ✨ Funcionalidades Principais

O programa oferece quatro operações fundamentais:

| Operação                | Código | Descrição                                            |
| ----------------------- | ------ | ---------------------------------------------------- |
| **Jogar Peça**          | `1`    | Remove a peça do início da fila (_dequeue_)          |
| **Reservar Peça**       | `2`    | Move a peça da fila para a pilha de reserva (_push_) |
| **Usar Peça Reservada** | `3`    | Remove e usa a peça do topo da pilha (_pop_)         |
| **Sair**                | `0`    | Encerra o programa                                   |

### 📦 Estrutura das Peças

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

#### Utilidades

- `Peca gerarPeca(void)` — Gera uma peça aleatória automaticamente

## 🎯 Conceitos Aplicados

### Fila Circular (FIFO)

- Reaproveitamento eficiente de espaço no array
- Operação circular usando `(indice + 1) % MAX_FILA`
- Mantém sempre 5 peças na fila
- A cada remoção, uma nova peça é gerada automaticamente

### Pilha Linear (LIFO)

- Capacidade limitada a 3 peças
- Permite reservar peças para uso posterior
- Acesso apenas pelo topo (última peça inserida)

### Fluxo de Dados

```
Fila → Jogar (dequeue)      → Peça usada
Fila → Reservar (dequeue)   → Pilha (push)
Pilha → Usar (pop)          → Peça usada
```

## 🚀 Como Usar

### Compilação

```bash
gcc -g desafioAventureiro.c -o desafioAventureiro.exe
```

### Execução

```bash
./desafioAventureiro.exe
```

### Exemplo de Uso

```
===== TETRIS STACK - GERENCIAMENTO DE PECAS =====

Fila de Pecas: [T 0] [O 1] [L 2] [I 3] [I 4]
Pilha de Reserva (Topo -> Base): (vazia)

1 - Jogar Peca
2 - Reservar Peca
3 - Usar Peca Reservada
0 - Sair

Opcao: 2

===== RESERVANDO PECA =====

Peca [T 0] foi movida para a pilha de reserva!

Nova peca gerada automaticamente!

Estado atual:
Fila de Pecas: [O 1] [L 2] [I 3] [I 4] [T 5]
Pilha de Reserva (Topo -> Base): [T 0]

Pressione ENTER para continuar...
```

## 📊 Exemplo de Execução Completa

1. **Estado Inicial**: Fila com 5 peças, pilha vazia
2. **Reservar** (`2`): Move `[T 0]` da fila para a pilha → Nova peça gerada
3. **Reservar** (`2`): Move `[O 1]` da fila para a pilha → Nova peça gerada
4. **Reservar** (`2`): Move `[L 2]` da fila para a pilha → Nova peça gerada
5. **Pilha cheia**: Tentativa de reservar é bloqueada
6. **Usar reservada** (`3`): Remove `[L 2]` da pilha e usa
7. **Jogar** (`1`): Remove e joga peça direto da fila

## 🎓 Requisitos Cumpridos

### Funcionais

✅ Inicialização automática da fila com 5 peças  
✅ Inicialização da pilha vazia com capacidade para 3 peças  
✅ Operação de jogar peça (dequeue)  
✅ Operação de reservar peça (move da fila para pilha)  
✅ Operação de usar peça reservada (pop)  
✅ Geração automática de novas peças  
✅ Validações de fila/pilha cheia ou vazia  
✅ Exibição clara do estado atual

### Não Funcionais

✅ Interface clara e intuitiva  
✅ Código bem documentado com comentários Doxygen  
✅ Separação de responsabilidades  
✅ Mensagens de erro descritivas  
✅ Feedback visual imediato após cada ação  
✅ Exibição automática do estado atualizado da fila e pilha após operações

## 🔧 Detalhes Técnicos

### Capacidades

- **Fila**: 5 peças (fixo)
- **Pilha**: 3 peças (fixo)
- **Tipos de peças**: I, O, T, L (geradas aleatoriamente)

### Comportamento

- Peças removidas da fila ou pilha não voltam ao jogo
- A cada remoção da fila, uma nova peça é gerada automaticamente
- Não é possível reservar quando a pilha está cheia
- Não é possível usar reservada quando a pilha está vazia

## 📝 Observações

- O programa limpa apenas o buffer de entrada para evitar comportamentos inesperados
- IDs são sequenciais e únicos durante toda a execução
- Gerador de números aleatórios é inicializado com o tempo atual
- Estado da fila e pilha é exibido imediatamente após cada operação bem-sucedida

## 👨‍💻 Autor

Desenvolvido como parte das atividades de Estrutura de Dados - Tema 3: Pilhas e Filas.

---

**Status**: ✅ Funcionando perfeitamente  
**Última atualização**: 02/02/2026
