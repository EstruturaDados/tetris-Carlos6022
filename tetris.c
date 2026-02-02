/**
 * TETRIS STACK - Gerenciamento de Fila e Pilha de Pecas
 *
 * Arquivo: tetris.c
 * Proposito: Simular o gerenciamento de pecas no jogo Tetris Stack,
 *            utilizando uma fila circular para as proximas pecas
 *            e uma pilha para as pecas reservadas.
 *
 * Funcionalidades:
 * - Fila circular de pecas futuras (sempre com 5 pecas)
 * - Pilha de reserva com capacidade limitada (3 pecas)
 * - Jogar peca (remove da frente da fila)
 * - Reservar peca (move da fila para a pilha de reserva)
 * - Usar peca reservada (remove do topo da pilha)
 * - Exibir estado da fila e da pilha
 * - Geracao automatica de novas pecas apos cada acao
 */

#include <stdio.h>  // Entrada e saida (printf, scanf)
#include <stdlib.h> // Funcoes gerais (rand, etc)
#include <time.h>   // Funcoes de tempo para seeding aleatorio

#define MAX_FILA 5  // Capacidade maxima da fila circular
#define MAX_PILHA 3 // Capacidade maxima da pilha de reserva

/**
 * @brief Estrutura Peca
 *
 * Representa uma peca individual do jogo Tetris Stack.
 * @struct Peca
 */
typedef struct {
    char nome; ///< Tipo de peca: 'I', 'O', 'T' ou 'L'
    int id;    ///< Identificador unico (sequencial)
} Peca;

/**
 * @brief Estrutura Fila
 *
 * Implementa uma fila circular para armazenar as pecas futuras.
 * @struct Fila
 */
typedef struct {
    Peca itens[MAX_FILA]; ///< Array de pecas (capacidade fixa)
    int inicio;           ///< Posicao do primeiro elemento
    int fim;              ///< Posicao do proximo elemento a ser inserido
    int total;            ///< Quantidade de elementos na fila
} Fila;

/**
 * @brief Estrutura Pilha
 *
 * Implementa uma pilha linear para armazenar as pecas reservadas.
 * @struct Pilha
 */
typedef struct {
    Peca itens[MAX_PILHA]; ///< Array de pecas (capacidade fixa)
    int topo;              ///< Indice do topo da pilha
} Pilha;

// Contador global para gerar ids unicos
static int proximoId = 0;

/**
 * @brief Gera uma nova peca com tipo aleatorio
 *
 * Seleciona aleatoriamente um dos 4 tipos (I, O, T, L),
 * atribui o proximo ID disponivel e incrementa o contador global.
 *
 * @return Peca Estrutura Peca com nome aleatorio e ID unico
 */
Peca gerarPeca(void) {
    const char tipos[] = {'I', 'O', 'T', 'L'};
    int indice = rand() % 4;

    Peca p;
    p.nome = tipos[indice];
    p.id = proximoId++;

    return p;
}

/**
 * @brief Inicializa uma fila vazia
 *
 * Define os indices inicio e fim como 0 e o total como 0.
 *
 * @param f Ponteiro para a fila a ser inicializada
 */
void inicializarFila(Fila *f) {
    f->inicio = 0;
    f->fim = 0;
    f->total = 0;
}

/**
 * @brief Inicializa uma pilha vazia
 *
 * Define o topo como -1, indicando pilha vazia.
 *
 * @param p Ponteiro para a pilha a ser inicializada
 */
void inicializarPilha(Pilha *p) {
    p->topo = -1;
}

/**
 * @brief Verifica se a fila esta cheia
 *
 * @param f Ponteiro para a fila a ser verificada
 * @return int 1 se cheia, 0 se tem espaco
 */
int filaCheia(Fila *f) {
    return f->total == MAX_FILA;
}

/**
 * @brief Verifica se a fila esta vazia
 *
 * @param f Ponteiro para a fila a ser verificada
 * @return int 1 se vazia, 0 se contem pecas
 */
int filaVazia(Fila *f) {
    return f->total == 0;
}

/**
 * @brief Verifica se a pilha esta cheia
 *
 * @param p Ponteiro para a pilha a ser verificada
 * @return int 1 se cheia, 0 se tem espaco
 */
int pilhaCheia(Pilha *p) {
    return p->topo == MAX_PILHA - 1;
}

/**
 * @brief Verifica se a pilha esta vazia
 *
 * @param p Ponteiro para a pilha a ser verificada
 * @return int 1 se vazia, 0 se contem pecas
 */
int pilhaVazia(Pilha *p) {
    return p->topo == -1;
}

/**
 * @brief Adiciona uma peca ao final da fila (enqueue)
 *
 * Insere a peca na posicao 'fim' e avanca o indice de forma circular.
 *
 * @param f Ponteiro para a fila
 * @param p Peca a ser inserida
 */
void enfileirar(Fila *f, Peca p) {
    if(filaCheia(f)) {
        printf("Fila cheia. Nao e possivel inserir.\n");
        return;
    }

    f->itens[f->fim] = p;
    f->fim = (f->fim + 1) % MAX_FILA;
    f->total++;
}

/**
 * @brief Remove a peca do inicio da fila (dequeue)
 *
 * Copia a peca do inicio para o parametro p e avanca o indice.
 *
 * @param f Ponteiro para a fila
 * @param p Ponteiro para armazenar a peca removida
 * @return int 1 se sucesso, 0 se fila vazia
 */
int desenfileirar(Fila *f, Peca *p) {
    if(filaVazia(f)) {
        printf("Fila vazia. Nao e possivel remover.\n");
        return 0;
    }

    *p = f->itens[f->inicio];
    f->inicio = (f->inicio + 1) % MAX_FILA;
    f->total--;

    return 1;
}

/**
 * @brief Adiciona uma peca ao topo da pilha (push)
 *
 * Incrementa o topo e insere a peca na nova posicao.
 *
 * @param p Ponteiro para a pilha
 * @param peca Peca a ser adicionada
 * @return int 1 se sucesso, 0 se pilha cheia
 */
int push(Pilha *p, Peca peca) {
    if(pilhaCheia(p)) {
        return 0;
    }

    p->topo++;
    p->itens[p->topo] = peca;
    return 1;
}

/**
 * @brief Remove a peca do topo da pilha (pop)
 *
 * Copia a peca do topo para o parametro peca e decrementa o topo.
 *
 * @param p Ponteiro para a pilha
 * @param peca Ponteiro para armazenar a peca removida
 * @return int 1 se sucesso, 0 se pilha vazia
 */
int pop(Pilha *p, Peca *peca) {
    if(pilhaVazia(p)) {
        return 0;
    }

    *peca = p->itens[p->topo];
    p->topo--;

    return 1;
}

/**
 * @brief Exibe o estado atual da fila no terminal
 *
 * Mostra todas as pecas da fila no formato [TIPO ID].
 *
 * @param f Ponteiro para a fila a ser exibida
 */
void mostrarFila(Fila *f) {
    printf("Fila de Pecas: ");

    for(int i = 0, idx = f->inicio; i < f->total; i++, idx = (idx + 1) % MAX_FILA) {
        printf("[%c %d] ", f->itens[idx].nome, f->itens[idx].id);
    }

    printf("\n");
}

/**
 * @brief Exibe o estado atual da pilha no terminal
 *
 * Mostra todas as pecas da pilha do topo para a base.
 * Exibe "(vazia)" se a pilha nao contem pecas.
 *
 * @param p Ponteiro para a pilha a ser exibida
 */
void mostrarPilha(Pilha *p) {
    printf("Pilha de Reserva (Topo -> Base): ");

    if(pilhaVazia(p)) {
        printf("(vazia)");
    } else {
        for(int i = p->topo; i >= 0; i--) {
            printf("[%c %d] ", p->itens[i].nome, p->itens[i].id);
        }
    }

    printf("\n\n");
}

/**
 * @brief Exibe o menu de opcoes para o jogador
 *
 * Mostra as 4 opcoes disponiveis: Jogar, Reservar, Usar Reservada e Sair.
 */
void mostrarMenu(void) {
    printf("\n1 - Jogar Peca (dequeue)\n");
    printf("2 - Reservar Peca (push)\n");
    printf("3 - Usar Peca Reservada (pop)\n");
    printf("0 - Sair\n");
    printf("\nOpcao: ");
}

/**
 * @brief Funcao principal do programa
 *
 * Implementa o loop de interacao com o jogador:
 * 1. Inicializa fila e pilha
 * 2. Popula a fila com 5 pecas aleatorias
 * 3. Exibe menu e processa opcoes ate o jogador sair
 *
 * @return int 0 indicando sucesso na execucao
 */
int main(void) {
    Fila fila;      // Estrutura da fila de pecas futuras
    Pilha pilha;    // Estrutura da pilha de pecas reservadas
    int opcao = -1; // Opcao selecionada pelo jogador
    Peca temp;      // Variavel temporaria para operacoes

    // Inicializa o gerador de numeros aleatorios
    srand((unsigned int)time(NULL));

    // Inicializa a fila e a pilha
    inicializarFila(&fila);
    inicializarPilha(&pilha);

    // Popula a fila com MAX_FILA pecas aleatorias
    for(int i = 0; i < MAX_FILA; i++) {
        enfileirar(&fila, gerarPeca());
    }

    // Loop principal de interacao
    while(opcao != 0) {

        printf("\n\n===== TETRIS STACK - GERENCIAMENTO DE PECAS =====\n\n");

        // Exibe o estado atual da fila e da pilha
        mostrarFila(&fila);
        mostrarPilha(&pilha);

        // Exibe o menu de opcoes
        mostrarMenu();

        // Le a entrada do usuario
        if(scanf("%d", &opcao) != 1) {
            printf("\nEntrada invalida. Encerrando.\n");
            break;
        }

        // Limpa o buffer de entrada (consome o \n que sobrou do scanf)
        while(getchar() != '\n')
            ;

        if(opcao == 1) {

            if(desenfileirar(&fila, &temp)) {
                printf("\n===== JOGANDO PECA =====\n\n");
                printf("Peca jogada: [%c %d]\n", temp.nome, temp.id);
                enfileirar(&fila, gerarPeca());
                printf("\nNova peca gerada automaticamente!\n\n");

                // Exibe o estado atualizado
                printf("Estado atual:\n");
                mostrarFila(&fila);
                mostrarPilha(&pilha);
            }
            printf("\nPressione ENTER para continuar...");
            getchar();

        } else if(opcao == 2) {

            if(pilhaCheia(&pilha)) {
                printf("\n===== ERRO =====\n\n");
                printf("Pilha de reserva cheia! Nao e possivel reservar.\n\n");

                // Exibe o estado (sem alteracoes)
                printf("Estado atual:\n");
                mostrarFila(&fila);
                mostrarPilha(&pilha);
            } else if(desenfileirar(&fila, &temp)) {
                push(&pilha, temp);
                printf("\n===== RESERVANDO PECA =====\n\n");
                printf("Peca [%c %d] foi movida para a pilha de reserva!\n", temp.nome, temp.id);
                enfileirar(&fila, gerarPeca());
                printf("\nNova peca gerada automaticamente!\n\n");

                // Exibe o estado atualizado
                printf("Estado atual:\n");
                mostrarFila(&fila);
                mostrarPilha(&pilha);
            }

            printf("\nPressione ENTER para continuar...");
            getchar();

        } else if(opcao == 3) {

            if(pop(&pilha, &temp)) {
                printf("\n===== USANDO PECA RESERVADA =====\n\n");
                printf("Peca [%c %d] foi removida da pilha de reserva e usada!\n\n", temp.nome, temp.id);

                // Exibe o estado atualizado
                printf("Estado atual:\n");
                mostrarFila(&fila);
                mostrarPilha(&pilha);
            } else {
                printf("\n===== ERRO =====\n\n");
                printf("Pilha de reserva vazia! Nao ha pecas para usar.\n\n");

                // Exibe o estado (sem alteracoes)
                printf("Estado atual:\n");
                mostrarFila(&fila);
                mostrarPilha(&pilha);
            }

            printf("\nPressione ENTER para continuar...");
            getchar();

        } else if(opcao == 0) {
            printf("\n===== ENCERRANDO =====\n\n");
            printf("Obrigado por jogar!\n\n");

        } else {

            printf("\n===== ERRO =====\n\n");
            printf("Opcao invalida! Escolha entre 0 e 3.\n");
            printf("\nPressione ENTER para continuar...");
            getchar();
        }
    }

    return 0;
}
