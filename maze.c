#include "maze.h"

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
    labirinto->numMonstros = 0;
    for (i = 0; i < labirinto->altura; i++)
    {
        for (j = 0; j < labirinto->largura; j++)
        {
            if (labirinto->mapa[i][j] == 'M')
            {
                labirinto->numMonstros++;
            }
        }
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
    pilha->pilha = (Posicao *)malloc(tamanho_maximo * sizeof(Posicao));
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
    printf("\n");
    for (int i = pilha->topo; i >= 0; i--)
    {
        printf("%c", pilha->movimentos[i]);
    }
    printf("\n");
    printf("%d\n", pilha->topo);
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

void inicializarMonstros(Labirinto *labirinto)
{
    labirinto->numMonstros = 0;
    for (int i = 0; i < labirinto->altura; i++)
    {
        for (int j = 0; j < labirinto->largura; j++)
        {
            if (labirinto->mapa[i][j] == 'M')
            {
                labirinto->monstros[labirinto->numMonstros].posicao.x = i;
                labirinto->monstros[labirinto->numMonstros].posicao.y = j;
                labirinto->numMonstros++;
            }
        }
    }
}

int resolverLabirintoComMonstros(Labirinto *labirinto)
{
    Queue qA, qM;
    initializeQueue(&qA, labirinto->altura * labirinto->largura);
    initializeQueue(&qM, labirinto->altura * labirinto->largura);

    bool visitadoA[TAMANHO_MAX][TAMANHO_MAX] = {false};
    bool visitadoM[TAMANHO_MAX][TAMANHO_MAX] = {false};

    enqueue(&qA, labirinto->posicaoInicial);
    visitadoA[labirinto->posicaoInicial.x][labirinto->posicaoInicial.y] = true;

    for (int i = 0; i < labirinto->numMonstros; i++)
    {
        enqueue(&qM, labirinto->monstros[i].posicao);
        visitadoM[labirinto->monstros[i].posicao.x][labirinto->monstros[i].posicao.y] = true;
    }

    int dx[] = {-1, 1, 0, 0};
    int dy[] = {0, 0, -1, 1};

    while (!isQueueEmpty(&qA))
    {
        // Movimento de 'A'
        int sizeA = qA.rear - qA.front + 1;
        for (int a = 0; a < sizeA; a++)
        {
            Posicao currentA = dequeue(&qA);

            // Verifica se 'A' chegou à saída
            if (currentA.x == 0 || currentA.x == labirinto->altura - 1 ||
                currentA.y == 0 || currentA.y == labirinto->largura - 1)
            {

                return 1; // 'A' escapou
            }

            // Explora vizinhos de 'A'
            for (int i = 0; i < 4; i++)
            {
                int newX = currentA.x + dx[i];
                int newY = currentA.y + dy[i];

                if (newX >= 0 && newX < labirinto->altura && newY >= 0 && newY < labirinto->largura &&
                    !visitadoA[newX][newY] && labirinto->mapa[newX][newY] != '#')
                {
                    Posicao newA = {newX, newY};
                    enqueue(&qA, newA);
                    visitadoA[newX][newY] = true;
                }
            }
        }

        // Movimento dos monstros
        int sizeM = qM.rear - qM.front + 1;
        for (int m = 0; m < sizeM; m++)
        {
            Posicao currentM = dequeue(&qM);

            for (int i = 0; i < 4; i++)
            {
                int newX = currentM.x + dx[i];
                int newY = currentM.y + dy[i];

                if (newX >= 0 && newX < labirinto->altura && newY >= 0 && newY < labirinto->largura &&
                    !visitadoM[newX][newY] && labirinto->mapa[newX][newY] != '#')
                {
                    Posicao newM = {newX, newY};
                    enqueue(&qM, newM);
                    visitadoM[newX][newY] = true;

                    // Verifica se o monstro pegou 'A'
                    if (visitadoA[newX][newY])
                    {
                        return 0; // Monstro pegou 'A'
                    }
                }
            }
        }
    }

    return 0; // 'A' não conseguiu escapar
}

void resolverLabirinto(Labirinto *labirinto)
{
    inicializarMonstros(labirinto);
    if (resolverLabirintoComMonstros(labirinto))
    {
        printf("YES\n");
    }
    else
    {
        printf("NO\n");
    }
}