#include "maze.h"
#include <stdbool.h>

no *criaNo()
{
    no *novo;
    novo = (no *)calloc(1, sizeof(no));
    if (novo == NULL)
    {
        printf("ERRO: problemas com a alocacao de memoria . \n");
        exit(1);
    }
    return novo;
}

void empilha(no *Caminho, int posicao[2], char comando)
{
    no *novo = criaNo();
    novo->direcao = comando;
    novo->v[0] = posicao[0];
    novo->v[1] = posicao[1];
    no *aux = Caminho;
    while (aux->prox != NULL)
    {
        aux = aux->prox;
    }
    aux->prox = novo;
    novo->ant = aux;
    Caminho->tam++;
}
void desempilha(no *caminho)
{
    no *aux = caminho;
    while (aux->prox != NULL)
    {
        aux = aux->prox;
    }
    aux->ant->prox = NULL;
    caminho->tam--;
    free(aux);
}

void imprimeVoltaCaminho(no *Caminho)
{
    no *aux = Caminho->prox;
    if (aux == NULL)
        return;
    while (aux->prox != NULL)
    {
        aux = aux->prox;
    }
    while (aux != Caminho)
    {
        printf("%c", aux->direcao);
        aux = aux->ant;
    }
}

fila *criaFila()
{
    fila *novo = (fila *)calloc(1, sizeof(fila));
    if (novo == NULL)
    {
        printf("Erro de alocacao\n");
        exit(1);
    }
    return novo;
}

fila *addFila(fila *F, int posicao[2])
{
    fila *novo = criaFila();
    novo->posi[0] = posicao[0];
    novo->posi[1] = posicao[1];
    fila *aux = F;
    if (F == NULL)
        return novo;
    while (aux->prox != NULL)
        aux = aux->prox;
    aux->prox = novo;
    return F;
}

fila *removeFila(fila *F)
{
    fila *aux = F;
    F = aux->prox;
    free(aux);
    return F;
}

fila *achaposicao(int altura, int largura, int **labirinto, int M_A)
{
    int posicao[2];
    fila *posi = NULL;
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
                    posi = addFila(posi, posicao);
                }
            }
        }
        return posi;
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
                            posi = addFila(posi, posicao);
                        }
                    }
                    else
                    {
                        posicao[0] = i;
                        posicao[1] = j;
                        posi = addFila(posi, posicao);
                    }
                }
            }
        }
        return posi;
    }
}

void voltaCaminho(int altura, int largura, int **labirinto, int inicial[2], int final[2])
{
    no *caminho = criaNo();
    while ((final[0] != inicial[0]) || (final[1] != inicial[1]))
    {
        if (final[0] != 0 && labirinto[final[0] - 1][final[1]] == 1)
        {
            labirinto[final[0]][final[1]] = 4;
            final[0] = final[0] - 1;
            empilha(caminho, final, 'D');
        }
        else if (final[1] != largura - 1 && labirinto[final[0]][final[1] + 1] == 1)
        {
            labirinto[final[0]][final[1]] = 4;
            final[1] = final[1] + 1;
            empilha(caminho, final, 'L');
        }
        else if (final[0] != altura - 1 && labirinto[final[0] + 1][final[1]] == 1)
        {
            labirinto[final[0]][final[1]] = 4;
            final[0] = final[0] + 1;
            empilha(caminho, final, 'U');
        }
        else if (final[1] != 0 && labirinto[final[0]][final[1] - 1] == 1)
        {
            labirinto[final[0]][final[1]] = 4;
            final[1] = final[1] - 1;
            empilha(caminho, final, 'R');
        }
        else if (labirinto[final[0] - 1][final[1]] == 4)
        {
            labirinto[final[0]][final[1]] = 3;
            final[0] = final[0] - 1;
            desempilha(caminho);
        }
        else if (labirinto[final[0]][final[1] + 1] == 4)
        {
            labirinto[final[0]][final[1]] = 3;
            final[1] = final[1] + 1;
            desempilha(caminho);
        }
        else if (labirinto[final[0] + 1][final[1]] == 4)
        {
            labirinto[final[0]][final[1]] = 3;
            final[0] = final[0] + 1;
            desempilha(caminho);
        }
        else if (labirinto[final[0]][final[1] - 1] == 4)
        {
            labirinto[final[0]][final[1]] = 3;
            final[1] = final[1] - 1;
            desempilha(caminho);
        }
    }
    printf("YES\n");
    printf("%d\n", caminho->tam);
    imprimeVoltaCaminho(caminho);
}

int distancia(int x1, int y1, int x2, int y2)
{
    return abs(x1 - x2) + abs(y1 - y2);
}

bool moveBestante(int altura, int largura, int **labirinto, int *bestante, int *tributo)
{
    int melhor_x = bestante[0], melhor_y = bestante[1];
    int menor_dist = distancia(bestante[0], bestante[1], tributo[0], tributo[1]);

    int dx[] = {-1, 0, 1, 0};
    int dy[] = {0, 1, 0, -1};

    for (int i = 0; i < 4; i++)
    {
        int novo_x = bestante[0] + dx[i];
        int novo_y = bestante[1] + dy[i];

        if (novo_x >= 0 && novo_x < altura && novo_y >= 0 && novo_y < largura &&
            labirinto[novo_x][novo_y] != 3)
        { // Não é parede
            int nova_dist = distancia(novo_x, novo_y, tributo[0], tributo[1]);
            if (nova_dist < menor_dist)
            {
                menor_dist = nova_dist;
                melhor_x = novo_x;
                melhor_y = novo_y;
            }
        }
    }

    if (melhor_x == tributo[0] && melhor_y == tributo[1])
    {
        return true; // Bestante alcançou o tributo
    }

    labirinto[bestante[0]][bestante[1]] = 0; // Libera a posição atual
    bestante[0] = melhor_x;
    bestante[1] = melhor_y;
    labirinto[melhor_x][melhor_y] = 2; // Marca a nova posição do bestante
    return false;
}

bool moveTributo(int altura, int largura, int **labirinto, int *tributo, no *caminho)
{
    int dx[] = {-1, 0, 1, 0};
    int dy[] = {0, 1, 0, -1};
    char direcoes[] = {'U', 'R', 'D', 'L'};

    for (int i = 0; i < 4; i++)
    {
        int novo_x = tributo[0] + dx[i];
        int novo_y = tributo[1] + dy[i];

        if (novo_x >= 0 && novo_x < altura && novo_y >= 0 && novo_y < largura &&
            labirinto[novo_x][novo_y] == 0)
        {
            labirinto[tributo[0]][tributo[1]] = 0; // Libera a posição atual
            tributo[0] = novo_x;
            tributo[1] = novo_y;
            labirinto[novo_x][novo_y] = 1; // Marca a nova posição do tributo
            empilha(caminho, tributo, direcoes[i]);
            return true;
        }
    }
    return false; // Tributo não conseguiu se mover
}

void sairLab(int altura, int largura, int **labirinto, fila *posiTributo, fila *posiMonstros)
{
    int tributo[2] = {posiTributo->posi[0], posiTributo->posi[1]};
    no *caminho = criaNo();

    while (true)
    {
        // Verifica se o tributo chegou à borda
        if (tributo[0] == 0 || tributo[1] == largura - 1 || tributo[0] == altura - 1 || tributo[1] == 0)
        {
            printf("YES\n");
            printf("%d\n", caminho->tam);
            imprimeVoltaCaminho(caminho);
            return;
        }

        bool tributoMoveu = moveTributo(altura, largura, labirinto, tributo, caminho);
        bool bestanteAlcancou = false;

        // Move todos os bestantes
        fila *monstro_atual = posiMonstros;
        while (monstro_atual != NULL)
        {
            if (moveBestante(altura, largura, labirinto, monstro_atual->posi, tributo))
            {
                bestanteAlcancou = true;
                break;
            }
            monstro_atual = monstro_atual->prox;
        }

        // Verifica se algum bestante alcançou o tributo
        if (bestanteAlcancou)
        {
            printf("You Died\n");
            return;
        }

        // Se o tributo não conseguiu se mover e nenhum bestante o alcançou, não há solução
        if (!tributoMoveu)
        {
            printf("NO\n");
            return;
        }
    }
}