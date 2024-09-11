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
                (labirinto->mapa[newX][newY] == '.' || labirinto->mapa[newX][newY] == 'A') &&
                pais[newX][newY].x == -1)
            {
                Posicao novaPosicao = {newX, newY};
                enqueue(&q, novaPosicao);
                pais[newX][newY] = atual;
                movimentos[newX][newY] = direcoes[i];
            }
        }

        // Verifica se o jogador foi capturado por um monstro
        if (labirinto->mapa[atual.x][atual.y] == 'M')
        {
            printf("Jogador capturado por um monstro!\n");

            // Libera a memória alocada
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

int distanciaEntrePosicoes(Posicao p1, Posicao p2)
{
    return abs(p1.x - p2.x) + abs(p1.y - p2.y);
}

void moverMonstros(Labirinto *labirinto)
{
    int dx[] = {-1, 1, 0, 0};
    int dy[] = {0, 0, -1, 1};

    for (int i = 0; i < labirinto->numMonstros; i++)
    {
        int melhorDirecao = -1;
        int menorDistancia = TAMANHO_MAX * TAMANHO_MAX;

        for (int j = 0; j < 4; j++)
        {
            int newX = labirinto->monstros[i].posicao.x + dx[j];
            int newY = labirinto->monstros[i].posicao.y + dy[j];

            if (newX >= 0 && newX < labirinto->altura && newY >= 0 && newY < labirinto->largura &&
                labirinto->mapa[newX][newY] != '#' && labirinto->mapa[newX][newY] != 'M')
            {
                Posicao novaPosicao = {newX, newY};
                int distancia = distanciaEntrePosicoes(novaPosicao, labirinto->posicaoInicial);

                if (distancia < menorDistancia)
                {
                    melhorDirecao = j;
                    menorDistancia = distancia;
                }
            }
        }

        if (melhorDirecao != -1)
        {
            int newX = labirinto->monstros[i].posicao.x + dx[melhorDirecao];
            int newY = labirinto->monstros[i].posicao.y + dy[melhorDirecao];

            labirinto->mapa[labirinto->monstros[i].posicao.x][labirinto->monstros[i].posicao.y] = '.';
            labirinto->mapa[newX][newY] = 'M';
            labirinto->monstros[i].posicao.x = newX;
            labirinto->monstros[i].posicao.y = newY;
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
        // Aqui você pode adicionar lógica para reconstruir e imprimir o caminho, se necessário
    }
    else
    {
        printf("NO\n");
    }

    // Adicione esta linha para imprimir o labirinto após a resolução
    imprimeLabirinto(labirinto);
}