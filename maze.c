#include "maze.h"

// Função para preencher o labirinto com caracteres aleatórios
void carregaLabirintoAleatorio(Labirinto *labirinto)
{
    int i, j;

    // Inicializa o gerador de números aleatórios
    srand(time(NULL));

    // Preenche o labirinto com caracteres aleatórios, exceto 'A'
    for (i = 0; i < labirinto->altura; i++)
    {
        for (j = 0; j < labirinto->largura; j++)
        {
            int randChar = rand() % 3; // Gera um número aleatório entre 0 e 2

            switch (randChar)
            {
            case 0:
                labirinto->mapa[i][j] = '.';
                break;
            case 1:
                labirinto->mapa[i][j] = '#';
                break;
            case 2:
                labirinto->mapa[i][j] = 'M';
                break;
            }
        }
    }

    // Garante que há exatamente um 'A' no labirinto
    int posX = rand() % labirinto->altura;
    int posY = rand() % labirinto->largura;
    labirinto->mapa[posX][posY] = 'A';
    labirinto->posicaoInicial.x = posX;
    labirinto->posicaoInicial.y = posY;
}

void carregarLabirinto(Labirinto *labirinto, int linhas, int colunas)
{
    if (linhas < 1 || linhas > TAMANHO_MAX || colunas < 1 || colunas > TAMANHO_MAX)
    {
        printf("Erro: Dimensões do labirinto são inválidas.\n");
        return;
    }

    labirinto->altura = linhas;
    labirinto->largura = colunas;

    int i, j;
    int contadorA = 0;

    // le cada caractere
    for (i = 0; i < labirinto->altura; i++)
    {
        for (j = 0; j < labirinto->largura; j++)
        {
            scanf(" %c", &labirinto->mapa[i][j]);
            if (labirinto->mapa[i][j] == 'A')
            {
                labirinto->posicaoInicial.x = i;
                labirinto->posicaoInicial.y = j;
                contadorA++;
            }
            if (labirinto->mapa[i][j] != 'A' && labirinto->mapa[i][j] != '.' && labirinto->mapa[i][j] != '#' && labirinto->mapa[i][j] != 'M')
            {
                printf("Erro: Caractere inválido '%c' encontrado no labirinto.\n", labirinto->mapa[i][j]);
                exit(1);
            }
        }
    }
    if (contadorA == 0)
    {
        printf("Erro: Nenhum ponto inicial 'A' encontrado no labirinto.\n");
        exit(1);
    }
    else if (contadorA > 1)
    {
        printf("Erro: Mais de um ponto inicial 'A' encontrado no labirinto.\n");
        exit(1);
    }
}

void imprimeLabirinto(Labirinto *labirinto)
{
    int i, j;
    printf("\n");
    for (i = 0; i < labirinto->altura; i++)
    {
        for (j = 0; j < labirinto->largura; j++)
        {
            printf("%c", labirinto->mapa[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

void inicializarPilha(Pilha *pilha, int tamanho_maximo)
{
    // pilha->pilha = (Posicao *)malloc(tamanho_maximo * sizeof(Posicao));
    pilha->movimentos = (char *)malloc(tamanho_maximo * sizeof(char));
    if (pilha->pilha == NULL || pilha->movimentos == NULL)
    {
        printf("Erro ao alocar memória para a pilha.\n");
        exit(1);
    }
    pilha->topo = -1;
    pilha->tamanho_maximo = tamanho_maximo;
}

int pilhaVazia(Pilha *pilha)
{
    return pilha->topo == -1;
}

void empilhar(Pilha *pilha, Posicao pos, char movimento)
{
    if (pilha->topo < pilha->tamanho_maximo - 1)
    {
        pilha->pilha[++(pilha->topo)] = pos;
        pilha->movimentos[pilha->topo] = movimento;
    }
    else
    {
        printf("Pilha cheia. Não é possível empilhar.\n");
    }
}

Posicao desempilhar(Pilha *pilha)
{
    if (pilhaVazia(pilha))
    {
        fprintf(stderr, "Pilha vazia. Não é possível desempilhar.\n");
        exit(1);
    }
    return pilha->pilha[(pilha->topo)--];
}

void imprimirPilha(Pilha *pilha)
{
    // printf("Posição inicial: (Linha: %d, Coluna: %d)\n", pilha->pilha[0].x + 1, pilha->pilha[0].y + 1);
    // for (int i = pilha->topo; i >= 0; i--)
    // {
    //     printf("(%d,%d) -> ", pilha->pilha[i].x + 1, pilha->pilha[i].y + 1);
    // }
    printf("\n");
    for (int i = pilha->topo; i >= 0; i--)
    {
        printf("%c", pilha->movimentos[i]);
    }
    // printf("\nSaiu\n");
    printf("\n");
    printf("%d\n", pilha->topo);
    // printf("Tamanho da pilha: %d\n", pilha->topo);
}

void desalocarPilha(Pilha *pilha)
{
    free(pilha->pilha);
    free(pilha->movimentos);
}

// Funções para a fila
void initializeQueue(Queue *q, int maxSize)
{
    q->items = (Posicao *)malloc(maxSize * sizeof(Posicao));
    q->front = -1;
    q->rear = -1;
    q->size = maxSize;
}

int isQueueEmpty(Queue *q)
{
    return q->front == -1;
}

void enqueue(Queue *q, Posicao value)
{
    if (q->rear == q->size - 1)
        return;
    if (q->front == -1)
        q->front = 0;
    q->rear++;
    q->items[q->rear] = value;
}

Posicao dequeue(Queue *q)
{
    Posicao item = q->items[q->front];
    q->front++;
    if (q->front > q->rear)
        q->front = q->rear = -1;
    return item;
}

// Função modificada para encontrar o menor caminho
int encontrarMenorCaminho(Labirinto *labirinto, Posicao posicaoInicial, Pilha *caminho)
{
    int altura = labirinto->altura;
    int largura = labirinto->largura;

    // Matriz para armazenar os pais de cada posição
    Posicao **pais = (Posicao **)malloc(altura * sizeof(Posicao *));
    for (int i = 0; i < altura; i++)
    {
        pais[i] = (Posicao *)malloc(largura * sizeof(Posicao));
        for (int j = 0; j < largura; j++)
        {
            pais[i][j].x = -1;
            pais[i][j].y = -1;
        }
    }

    // Matriz para armazenar os movimentos
    char **movimentos = (char **)malloc(altura * sizeof(char *));
    for (int i = 0; i < altura; i++)
    {
        movimentos[i] = (char *)malloc(largura * sizeof(char));
        memset(movimentos[i], 0, largura * sizeof(char));
    }

    Queue q;
    initializeQueue(&q, altura * largura);

    enqueue(&q, posicaoInicial);
    pais[posicaoInicial.x][posicaoInicial.y] = posicaoInicial;

    int dx[] = {-1, 1, 0, 0};
    int dy[] = {0, 0, -1, 1};
    char direcoes[] = {'U', 'D', 'L', 'R'};

    while (!isQueueEmpty(&q))
    {
        Posicao atual = dequeue(&q);

        // Se chegou à borda, encontrou a saída
        if (atual.x == 0 || atual.x == altura - 1 || atual.y == 0 || atual.y == largura - 1)
        {
            // Reconstrói o caminho
            while (atual.x != posicaoInicial.x || atual.y != posicaoInicial.y)
            {
                empilhar(caminho, atual, movimentos[atual.x][atual.y]);
                atual = pais[atual.x][atual.y];
            }
            empilhar(caminho, posicaoInicial, '\0');

            // Libera a memória alocada
            for (int i = 0; i < altura; i++)
            {
                free(pais[i]);
                free(movimentos[i]);
            }
            free(pais);
            free(movimentos);
            free(q.items);

            return 1;
        }

        for (int i = 0; i < 4; i++)
        {
            int newX = atual.x + dx[i];
            int newY = atual.y + dy[i];

            if (newX >= 0 && newX < altura && newY >= 0 && newY < largura &&
                labirinto->mapa[newX][newY] == '.' && // Modificado para permitir apenas '.'
                pais[newX][newY].x == -1)
            {
                Posicao novaPosicao = {newX, newY};
                enqueue(&q, novaPosicao);
                pais[newX][newY] = atual;
                movimentos[newX][newY] = direcoes[i];
            }
        }
    }

    // Libera a memória se não encontrou caminho
    for (int i = 0; i < altura; i++)
    {
        free(pais[i]);
        free(movimentos[i]);
    }
    free(pais);
    free(movimentos);
    free(q.items);

    return 0;
}

// Função modificada para usar o novo algoritmo de busca
void resolverLabirinto(Labirinto *labirinto)
{
    Pilha caminho;
    inicializarPilha(&caminho, labirinto->altura * labirinto->largura);

    if (encontrarMenorCaminho(labirinto, labirinto->posicaoInicial, &caminho))
    {
        printf("YES\n");
        imprimirPilha(&caminho);
    }
    else
    {
        printf("NO.\n");
    }

    desalocarPilha(&caminho);
}