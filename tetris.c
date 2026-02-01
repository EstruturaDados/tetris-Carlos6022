/**
 * TETRIS STACK - Sistema de Fila de Pecas
 *
 * Arquivo: tetris.c
 * Proposito: Simular a fila de pecas futuras do jogo Tetris Stack
 *            utilizando estrutura de fila circular.
 *
 * Funcionalidades:
 * - Inicializacao automatica da fila com 5 pecas
 * - Operacao de dequeue (jogar peca)
 * - Operacao de enqueue (inserir nova peca)
 * - Visualizacao do estado da fila
 * - Menu interativo para o jogador
 *
 * Conceitos-chave:
 * - Fila circular: reutilizacao eficiente de espaco com indices circulares
 * - Structs: tipos personalizados para Peca e Fila
 * - Geracao automatica: funcao gerarPeca() cria pecas aleatorias
 */

#include <stdio.h>  // Entrada e saida (printf, scanf)
#include <stdlib.h> // Funcoes gerais (rand, etc)
#include <time.h>   // Funcoes de tempo para seeding aleatorio

#define MAX 5 // Capacidade maxima da fila circular

/**
 * Estrutura Peca
 *
 * Representa uma peca individual do jogo Tetris Stack.
 * - nome: caractere indicando o tipo da peca (I, O, T ou L)
 * - id: numero inteiro unico que identifica a peca
 */
typedef struct {
    char nome; // Tipo de peca: 'I', 'O', 'T' ou 'L'
    int id;    // Identificador unico (sequencial)
} Peca;

/**
 * Estrutura Fila
 *
 * Implementa uma fila circular para armazenar as pecas.
 * - itens[MAX]: array com as pecas armazenadas
 * - inicio: indice que aponta para a primeira peca da fila
 * - fim: indice que aponta para a proxima posicao livre
 * - total: quantidade de pecas atualmente na fila
 *
 * A circularidade eh mantida usando (indice + 1) % MAX
 */
typedef struct {
    Peca itens[MAX]; // Array de pecas (capacidade fixa)
    int inicio;      // Posicao do primeiro elemento
    int fim;         // Posicao do proximo elemento a ser inserido
    int total;       // Quantidade de elementos na fila
} Fila;

// Contador global para gerar ids unicos
// Incrementa a cada nova peca criada, garantindo identificadores sequenciais
static int proximoId = 0;

/**
 * gerarPeca()
 *
 * Propósito: Gerar automaticamente uma nova peca com tipo aleatorio
 *
 * Funcionamento:
 * 1. Seleciona aleatoriamente um dos 4 tipos (I, O, T, L)
 * 2. Atribui o proximo ID disponivel
 * 3. Incrementa o contador global de IDs
 *
 * Retorno: Estrutura Peca com nome aleatorio e ID unico
 */
Peca gerarPeca(void) {
    // Array com os tipos de pecas possiveis
    const char tipos[] = {'I', 'O', 'T', 'L'};

    // Gera indice aleatorio entre 0 e 3
    int indice = rand() % 4;

    // Cria e inicializa a nova peca
    Peca p;
    p.nome = tipos[indice]; // Tipo de peca aleatorio
    p.id = proximoId++;     // Atribui ID e incrementa contador

    return p;
}

/**
 * inicializarFila(Fila *f)
 *
 * Propósito: Inicializar uma fila vazia
 *
 * Parametro: ponteiro para a fila a ser inicializada
 *
 * Efeito:
 * - Define inicio = 0 (nenhuma peca ainda)
 * - Define fim = 0 (proxima insercao sera na posicao 0)
 * - Define total = 0 (fila vazia)
 */
void inicializarFila(Fila *f) {
    f->inicio = 0; // Indice de inicio
    f->fim = 0;    // Indice do fim (onde proximo elemento sera inserido)
    f->total = 0;  // Quantidade de elementos
}

/**
 * filaCheia(Fila *f)
 *
 * Propósito: Verificar se a fila atingiu sua capacidade maxima
 *
 * Parametro: ponteiro para a fila a ser verificada
 *
 * Retorno:
 * - 1 (verdadeiro): fila esta cheia (total == MAX)
 * - 0 (falso): fila tem espaco disponivel
 */
int filaCheia(Fila *f) {
    return f->total == MAX;
}

/**
 * filaVazia(Fila *f)
 *
 * Propósito: Verificar se a fila nao contem nenhuma peca
 *
 * Parametro: ponteiro para a fila a ser verificada
 *
 * Retorno:
 * - 1 (verdadeiro): fila esta vazia (total == 0)
 * - 0 (falso): fila contem pecas
 */
int filaVazia(Fila *f) {
    return f->total == 0;
}

/**
 * enfileirar(Fila *f, Peca p)
 *
 * Propósito: Adicionar uma nova peca ao final da fila (enqueue)
 *
 * Parametros:
 * - f: ponteiro para a fila
 * - p: peca a ser inserida
 *
 * Logica:
 * 1. Verifica se a fila ja esta cheia
 * 2. Se nao estiver cheia:
 *    - Insere a peca na posicao 'fim'
 *    - Avanca o indice 'fim' de forma circular usando modulo
 *    - Incrementa o contador total
 *
 * Nota: A circularidade eh implementada com (fim + 1) % MAX
 */
void enfileirar(Fila *f, Peca p) {
    // Valida se ha espaco disponivel
    if(filaCheia(f)) {
        printf("Fila cheia. Nao e possivel inserir.\n");
        return;
    }

    // Insere a peca na posicao 'fim'
    f->itens[f->fim] = p;

    // Avanca o indice 'fim' de forma circular
    // (fim + 1) % MAX volta a 0 quando atinge MAX
    f->fim = (f->fim + 1) % MAX;

    // Incrementa a quantidade de pecas na fila
    f->total++;
}

/**
 * desenfileirar(Fila *f, Peca *p)
 *
 * Propósito: Remover a peca do inicio da fila (dequeue)
 *
 * Parametros:
 * - f: ponteiro para a fila
 * - p: ponteiro para armazenar a peca removida
 *
 * Retorno:
 * - 1: peca foi removida com sucesso
 * - 0: fila estava vazia, nenhuma peca removida
 *
 * Logica:
 * 1. Verifica se a fila esta vazia
 * 2. Se nao estiver vazia:
 *    - Copia a peca do inicio para o parametro p
 *    - Avanca o indice 'inicio' de forma circular
 *    - Decrementa o contador total
 */
int desenfileirar(Fila *f, Peca *p) {
    // Valida se ha pecas para remover
    if(filaVazia(f)) {
        printf("Fila vazia. Nao e possivel remover.\n");
        return 0;
    }

    // Copia a peca do inicio para o ponteiro fornecido
    *p = f->itens[f->inicio];

    // Avanca o indice 'inicio' de forma circular
    f->inicio = (f->inicio + 1) % MAX;

    // Decrementa a quantidade de pecas na fila
    f->total--;

    return 1; // Sucesso na remocao
}

/**
 * mostrarFila(Fila *f)
 *
 * Propósito: Exibir o estado atual da fila no terminal
 *
 * Parametro: ponteiro para a fila a ser exibida
 *
 * Formato de saida:
 * "Fila de Pecas: [T 0] [O 1] [L 2] [I 3] [I 4]"
 *
 * Logica:
 * 1. Imprime o titulo "Fila de Pecas: "
 * 2. Itera sobre os elementos da fila usando indice circular
 * 3. Para cada peca, exibe: [TIPO ID]
 * 4. A circularidade eh mantida com (idx + 1) % MAX
 */
void mostrarFila(Fila *f) {
    printf("Fila de Pecas: ");

    // Itera sobre todos os elementos da fila
    for(int i = 0, idx = f->inicio; i < f->total; i++, idx = (idx + 1) % MAX) {
        // Exibe cada peca no formato [TIPO ID]
        printf("[%c %d] ", f->itens[idx].nome, f->itens[idx].id);
    }

    printf("\n\n");
}

/**
 * mostrarMenu(void)
 *
 * Propósito: Exibir o menu de opcoes para o jogador
 *
 * Opcoes disponíveis:
 * 1 - Jogar Peca (remove do inicio da fila - dequeue)
 * 2 - Inserir Nova Peca (adiciona ao final da fila - enqueue)
 * 0 - Sair (encerra o programa)
 */
void mostrarMenu(void) {
    printf("1 - Jogar Peca (dequeue)\n");
    printf("2 - Inserir Nova Peca (enqueue)\n");
    printf("0 - Sair\n");
    printf("Escolha: ");
}

/**
 * main(void)
 *
 * Propósito: Funcao principal que implementa o loop de interacao com o jogador
 *
 * Fluxo do programa:
 * 1. Inicializa a fila de pecas
 * 2. Popula a fila com MAX pecas aleatorias
 * 3. Entra em um loop que:
 *    - Exibe o estado da fila
 *    - Exibe o menu de opcoes
 *    - Le a escolha do jogador
 *    - Executa a acao correspondente
 *    - Repete ate que o jogador escolha sair (opcao 0)
 */
int main(void) {
    // Declaracoes locais
    Fila fila;      // Estrutura da fila de pecas
    int opcao = -1; // Opcao selecionada pelo jogador (-1 = nao definido)

    // Inicializa o gerador de numeros aleatorios com seed baseado no tempo
    // Garante que cada execucao gere pecas diferentes
    srand((unsigned int)time(NULL));

    // Inicializa a fila vazia
    inicializarFila(&fila);

    // Popula a fila com MAX (5) pecas aleatorias
    // Isso simula o estado inicial do jogo
    for(int i = 0; i < MAX; i++) {
        enfileirar(&fila, gerarPeca());
    }

    // Loop principal de interacao
    // Continua enquanto a opcao nao for 0 (sair)
    while(opcao != 0) {
        // Exibe o estado atual da fila
        mostrarFila(&fila);

        // Exibe o menu de opcoes
        mostrarMenu();

        // Le a entrada do usuario
        // Verifica se a leitura foi bem-sucedida
        if(scanf("%d", &opcao) != 1) {
            printf("Entrada invalida. Encerrando.\n");
            break; // Sai do loop em caso de erro
        }

        // Processa a opcao escolhida
        if(opcao == 1) {
            // Opcao 1: Jogar peca (dequeue)
            // Remove a peca do inicio da fila
            Peca removida;
            if(desenfileirar(&fila, &removida)) {
                // Se foi bem-sucedido, exibe a peca removida
                printf("Peca jogada: [%c %d]\n\n", removida.nome, removida.id);
            }
        } else if(opcao == 2) {
            // Opcao 2: Inserir nova peca (enqueue)
            // Gera uma peca aleatoria e insere na fila
            enfileirar(&fila, gerarPeca());
            printf("Nova peca inserida.\n\n");
        } else if(opcao == 0) {
            // Opcao 0: Sair
            // Encerra o programa com mensagem de despedida
            printf("Saindo...\n");
        } else {
            // Opcao invalida
            // Informa ao usuario e retorna ao menu
            printf("Opcao invalida.\n\n");
        }
    }

    // Retorna 0 indicando sucesso na execucao
    return 0;
}
