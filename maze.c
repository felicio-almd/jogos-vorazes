#include "maze.h"

NoPilha *criaNo()
{
    NoPilha *novo;
    novo = (NoPilha *)calloc(1, sizeof(NoPilha));
    if (novo == NULL)
    {
        printf("ERRO: problemas com a alocacao de memoria . \n");
        exit(1);
    }
    return novo;
}

void empilha(NoPilha *caminho, int posicao[2], char comando)
{
    NoPilha *novo = criaNo();
    novo->direcao = comando;
    novo->coordenadasCaminho[0] = posicao[0]; // trocar esse v que porra é essa
    novo->coordenadasCaminho[1] = posicao[1];
    NoPilha *aux = caminho;
    while (aux->prox != NULL)
    {
        aux = aux->prox;
    }
    aux->prox = novo;
    novo->ant = aux;
    caminho->tamanho++;
}

void desempilha(NoPilha *caminho)
{
    NoPilha *aux = caminho;
    while (aux->prox != NULL)
    {
        aux = aux->prox;
    }
    aux->ant->prox = NULL;
    caminho->tamanho--;
    free(aux);
}

void imprimeCaminho(NoPilha *caminho)
{
    NoPilha *aux = caminho;
    if (aux == NULL)
        return;
    while (aux->prox != NULL)
    {
        printf("%c", aux->direcao);
        aux = aux->prox;
    }
    printf("\n");
}

Fila *criarFilaVazia()
{
    Fila *novo = (Fila *)calloc(1, sizeof(Fila));
    if (novo == NULL)
    {
        printf("Erro de alocacao\n");
        exit(1);
    }
    return novo;
}

Fila *enfileirar(Fila *fila, int posicao[2])
{
    Fila *novo = criarFilaVazia();
    novo->posicaoNoLabirinto[0] = posicao[0];
    novo->posicaoNoLabirinto[1] = posicao[1];
    Fila *aux = fila;
    if (fila == NULL)
        return novo;
    while (aux->prox != NULL)
        aux = aux->prox;
    aux->prox = novo;
    return fila;
}

Fila *removeFila(Fila *fila)
{
    Fila *aux = fila;
    fila = aux->prox;
    free(aux);
    return fila;
}

Fila *acharPosicao(int altura, int largura, int **labirinto, int M_A) // dnv esse M_A sla
{
    int posicao[2];
    Fila *posicaoAtual = NULL;
    if (M_A == 1)
    {
        for (int i = 0; i < altura; i++)
        {
            for (int j = 0; j < largura; j++)
            {
                if (labirinto[i][j] == M_A)
                {
                    posicao[0] = i;
                    posicao[1] = j;
                    posicaoAtual = enfileirar(posicaoAtual, posicao);
                }
            }
        }
        return posicaoAtual;
    }
    else
    {
        for (int i = 0; i < altura; i++)
        {
            for (int j = 0; j < largura; j++)
            {
                if (labirinto[i][j] == M_A)
                {
                    if (i != 0 && i != altura - 1 && j != 0 && j != largura - 1)
                    {
                        if (labirinto[i + 1][j] == 0 || labirinto[i - 1][j] == 0 || labirinto[i][j + 1] == 0 || labirinto[i][j - 1] == 0)
                        {
                            posicao[0] = i;
                            posicao[1] = j;
                            posicaoAtual = enfileirar(posicaoAtual, posicao);
                        }
                    }
                    else
                    {
                        posicao[0] = i;
                        posicao[1] = j;
                        posicaoAtual = enfileirar(posicaoAtual, posicao);
                    }
                }
            }
        }
        return posicaoAtual;
    }
}

int distanciaEntreOsPersonagens(int x1, int y1, int x2, int y2)
{
    return abs(x1 - x2) + abs(y1 - y2);
}

bool moveBestante(int altura, int largura, int **labirinto, int *bestante, int *tributo)
{
    int melhorX = bestante[0], melhorY = bestante[1];
    int menorDistancia = distanciaEntreOsPersonagens(bestante[0], bestante[1], tributo[0], tributo[1]);
    int novoX, novoY, novaDistancia;

    int dx[] = {-1, 0, 1, 0};
    int dy[] = {0, 1, 0, -1};

    for (int i = 0; i < 4; i++)
    {
        novoX = bestante[0] + dx[i];
        novoY = bestante[1] + dy[i];

        if (novoX >= 0 && novoX < altura && novoY >= 0 && novoY < largura &&
            labirinto[novoX][novoY] != 3 && labirinto[novoX][novoY] != 5)
        { // Não é parede e não foi visitado
            novaDistancia = distanciaEntreOsPersonagens(novoX, novoY, tributo[0], tributo[1]);
            if (novaDistancia < menorDistancia)
            {
                menorDistancia = novaDistancia;
                melhorX = novoX;
                melhorY = novoY;
            }
        }
    }

    if (melhorX == tributo[0] && melhorY == tributo[1])
    {
        return true; // Bestante alcançou o tributo
    }

    labirinto[bestante[0]][bestante[1]] = 0; // Libera a posição atual
    bestante[0] = melhorX;
    bestante[1] = melhorY;
    labirinto[melhorX][melhorY] = 2; // Marca a nova posição do bestante
    return false;
}

bool moveTributo(int altura, int largura, int **labirinto, int *tributo, NoPilha *caminho)
{
    int dx[] = {-1, 0, 1, 0};
    int dy[] = {0, 1, 0, -1};
    char direcoes[] = {'U', 'R', 'D', 'L'};

    for (int i = 0; i < 4; i++)
    {
        int novoX = tributo[0] + dx[i];
        int novoY = tributo[1] + dy[i];

        if (novoX >= 0 && novoX < altura && novoY >= 0 && novoY < largura &&
            labirinto[novoX][novoY] == 0) // Mover apenas para posições livres
        {
            labirinto[tributo[0]][tributo[1]] = 5; // Marca a posição atual como visitada
            tributo[0] = novoX;
            tributo[1] = novoY;
            labirinto[novoX][novoY] = 1; // Marca a nova posição do tributo
            empilha(caminho, tributo, direcoes[i]);
            return true;
        }
    }
    return false; // Tributo não conseguiu se mover
}

void escaparLabirinto(int altura, int largura, int **labirinto, Fila *posicaoTributo, Fila *posicaoMonstros)
{
    int tributo[2] = {posicaoTributo->posicaoNoLabirinto[0], posicaoTributo->posicaoNoLabirinto[1]};
    NoPilha *caminho = criaNo();

    while (true)
    {
        bool tributoMoveu = moveTributo(altura, largura, labirinto, tributo, caminho);
        // Verifica se o tributo chegou à borda
        if (tributo[0] == 0 || tributo[1] == largura - 1 || tributo[0] == altura - 1 || tributo[1] == 0)
        {
            printf("YES\n");
            printf("%d\n", caminho->tamanho);
            imprimeCaminho(caminho);
            return;
        }

        // Se o tributo não conseguiu se mover e nenhum bestante o alcançou, não há solução
        if (!tributoMoveu)
        {
            printf("NO\n");
            return;
        }

        bool bestanteAlcancou = false;

        // Move todos os bestantes
        Fila *monstroAtual = posicaoMonstros;
        while (monstroAtual != NULL)
        {
            if (moveBestante(altura, largura, labirinto, monstroAtual->posicaoNoLabirinto, tributo))
            {
                bestanteAlcancou = true;
                break;
            }
            monstroAtual = monstroAtual->prox;
        }

        // Verifica se algum bestante alcançou o tributo
        if (bestanteAlcancou)
        {
            printf("You Died\n");
            return;
        }
    }
}