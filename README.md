# 🎮 Tetris Stack — Sistema de Fila de Peças (Nível Novato)

## 📋 Visão Geral

Este projeto implementa, em **C**, uma simulação completa e funcional da **fila de peças futuras** do jogo educativo **Tetris Stack**. A solução utiliza uma estrutura de **fila circular** para gerenciar peças de forma eficiente, oferecendo ao jogador interatividade total através de um menu intuitivo.

### 🎯 Objetivo

Simular o comportamento de uma fila de peças em um jogo tipo Tetris, aplicando conceitos fundamentais de estruturas de dados em um contexto prático e educativo.

## ✨ Funcionalidades Principais

O programa oferece três operações fundamentais:

| Operação         | Código | Descrição                                           |
| ---------------- | ------ | --------------------------------------------------- |
| **Jogar Peça**   | `1`    | Remove a peça do início da fila (_dequeue_)         |
| **Inserir Peça** | `2`    | Adiciona uma nova peça ao final da fila (_enqueue_) |
| **Sair**         | `0`    | Encerra o programa                                  |

### 📦 Estrutura das Peças

Cada peça possui:

- **`nome`**: caractere indicando o tipo (`I`, `O`, `T` ou `L`)
- **`id`**: número inteiro único e sequencial

Exemplo: `[T 0]` = Peça tipo T com ID 0

## 🏗️ Arquitetura do Código

### Estruturas de Dados

```c
// Representa uma peça individual
typedef struct {
    char nome;  // Tipo: I, O, T, L
    int id;     // Identificador único
} Peca;

// Fila circular com capacidade fixa
typedef struct {
    Peca itens[MAX];  // Array de peças (MAX = 5)
    int inicio;       // Índice do primeiro elemento
    int fim;          // Índice do próximo espaço livre
    int total;        // Quantidade de peças
} Fila;
```

### Funções Principais

| Função              | Propósito                                            |
| ------------------- | ---------------------------------------------------- |
| `gerarPeca()`       | Gera automaticamente uma peça aleatória com ID único |
| `inicializarFila()` | Inicializa uma fila vazia                            |
| `filaCheia()`       | Verifica se atingiu capacidade máxima                |
| `filaVazia()`       | Verifica se está vazia                               |
| `enfileirar()`      | Insere peça no final (_enqueue_)                     |
| `desenfileirar()`   | Remove peça do início (_dequeue_)                    |
| `mostrarFila()`     | Exibe o estado atual da fila                         |
| `mostrarMenu()`     | Exibe menu de opções                                 |

## 📋 Requisitos Atendidos

### ✅ Requisitos Funcionais

- [x] Inicialização automática da fila com **5 peças**
- [x] Operação de **dequeue** com validação
- [x] Operação de **enqueue** com validação
- [x] Exibição clara do estado após cada ação
- [x] Menu interativo com 3 opções

### ✅ Requisitos Não-Funcionais

- [x] **Usabilidade**: Saída clara e intuitiva
- [x] **Legibilidade**: Código bem organizado com nomes descritivos
- [x] **Documentação**: Comentários explicando cada função e lógica

## 📸 Exemplo de Saída

```
Fila de Pecas: [T 0] [O 1] [L 2] [I 3] [I 4]

1 - Jogar Peca (dequeue)
2 - Inserir Nova Peca (enqueue)
0 - Sair
Escolha: 1
Peca jogada: [T 0]

Fila de Pecas: [O 1] [L 2] [I 3] [I 4]

1 - Jogar Peca (dequeue)
2 - Inserir Nova Peca (enqueue)
0 - Sair
Escolha: 2
Nova peca inserida.

Fila de Pecas: [O 1] [L 2] [I 3] [I 4] [T 5]
```

## 🛠️ Como Compilar

### Requisitos

- Compilador C (GCC recomendado)
- Windows, Linux ou macOS

### Windows (CMD ou PowerShell)

```bash
gcc -g desafioNovato.c -o desafioNovato.exe
```

### Linux/macOS (Terminal)

```bash
gcc -g desafioNovato.c -o desafioNovato
```

## ▶️ Como Executar

### Windows

```bash
.\desafioNovato.exe
```

### Linux/macOS

```bash
./desafioNovato
```

## 🔑 Conceitos Chave Implementados

### Fila Circular

A fila utiliza **índices circulares** para reutilizar espaço eficientemente:

- Quando `fim` atinge `MAX`, volta a 0
- Usa operação módulo: `(índice + 1) % MAX`

### Operações Fundamental

- **Enqueue**: Adiciona ao `fim` e avança circularmente
- **Dequeue**: Remove do `inicio` e avança circularmente
- **Validação**: Verifica `total == MAX` (cheia) e `total == 0` (vazia)

### Geração Automática de Peças

- Função `gerarPeca()` cria peças aleatórias
- Cada peça recebe um ID sequencial único
- Usa `srand()` com `time()` para aleatoriedade

## 📊 Fluxo de Execução

```
1. Inicializa a fila
2. Popula com 5 peças aleatórias
3. Loop interativo:
   ├─ Exibe fila
   ├─ Exibe menu
   ├─ Lê escolha do usuário
   ├─ Executa operação
   └─ Repete até sair (opção 0)
```

## ⚠️ Observações Importantes

1. **Capacidade Fixa**: A fila tem capacidade máxima de 5 peças
2. **Circularidade**: Espaço é reutilizado após remoção
3. **IDs Sequenciais**: Cada peça tem um ID único incremental
4. **Aleatoriedade**: Tipos de peças são aleatórios, mas IDs são ordenados
5. **Validação Completa**: Todas as operações verificam limites

## 🐛 Tratamento de Erros

O programa valida:

- **Fila Cheia**: Rejeita enqueue quando capacidade é atingida
- **Fila Vazia**: Rejeita dequeue quando vazia
- **Entrada Inválida**: Trata entradas não-numéricas
- **Menu Inválido**: Rejeita opções fora de 0-2

---

📚 **Desenvolvido como prática de estruturas de dados em C**
