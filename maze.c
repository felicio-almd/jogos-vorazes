#include "maze.h"

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

void sairLab(int altura, int largura, int **labirinto, fila *posiTributo, fila *posiMonstros)
{
    int inicio[2];
    inicio[0] = posiTributo->posi[0];
    inicio[1] = posiTributo->posi[1];
    fila *espera;
    int posicao_aux[2];
    while (posiTributo != NULL && (posiTributo->posi[0] != 0 && posiTributo->posi[1] != largura - 1 && posiTributo->posi[0] != altura - 1 && posiTributo->posi[1] != 0))
    {
        espera = NULL;
        while (posiMonstros != NULL)
        {
            if (posiMonstros->posi[0] != 0 && labirinto[posiMonstros->posi[0] - 1][posiMonstros->posi[1]] == 0)
            {
                labirinto[posiMonstros->posi[0] - 1][posiMonstros->posi[1]] = 2;
                posicao_aux[0] = posiMonstros->posi[0] - 1;
                posicao_aux[1] = posiMonstros->posi[1];
                espera = addFila(espera, posicao_aux);
            }
            if (posiMonstros->posi[1] != largura - 1 && labirinto[posiMonstros->posi[0]][posiMonstros->posi[1] + 1] == 0)
            {
                labirinto[posiMonstros->posi[0]][posiMonstros->posi[1] + 1] = 2;
                posicao_aux[0] = posiMonstros->posi[0];
                posicao_aux[1] = posiMonstros->posi[1] + 1;
                espera = addFila(espera, posicao_aux);
            }
            if (posiMonstros->posi[0] != altura - 1 && labirinto[posiMonstros->posi[0] + 1][posiMonstros->posi[1]] == 0)
            {
                labirinto[posiMonstros->posi[0] + 1][posiMonstros->posi[1]] = 2;
                posicao_aux[0] = posiMonstros->posi[0] + 1;
                posicao_aux[1] = posiMonstros->posi[1];
                espera = addFila(espera, posicao_aux);
            }
            if (posiMonstros->posi[1] != 0 && labirinto[posiMonstros->posi[0]][posiMonstros->posi[1] - 1] == 0)
            {
                labirinto[posiMonstros->posi[0]][posiMonstros->posi[1] - 1] = 2;
                posicao_aux[0] = posiMonstros->posi[0];
                posicao_aux[1] = posiMonstros->posi[1] - 1;
                espera = addFila(espera, posicao_aux);
            }
            posiMonstros = removeFila(posiMonstros);
        }
        posiMonstros = espera;
        espera = NULL;
        while (posiTributo != NULL && (posiTributo->posi[0] != 0 && posiTributo->posi[1] != largura - 1 && posiTributo->posi[0] != altura - 1 && posiTributo->posi[1] != 0))
        {
            if (labirinto[posiTributo->posi[0] - 1][posiTributo->posi[1]] == 0)
            {
                labirinto[posiTributo->posi[0] - 1][posiTributo->posi[1]] = 1;
                posicao_aux[0] = posiTributo->posi[0] - 1;
                posicao_aux[1] = posiTributo->posi[1];
                espera = addFila(espera, posicao_aux);
            }
            if (labirinto[posiTributo->posi[0]][posiTributo->posi[1] + 1] == 0)
            {
                labirinto[posiTributo->posi[0]][posiTributo->posi[1] + 1] = 1;
                posicao_aux[0] = posiTributo->posi[0];
                posicao_aux[1] = posiTributo->posi[1] + 1;
                espera = addFila(espera, posicao_aux);
            }
            if (labirinto[posiTributo->posi[0] + 1][posiTributo->posi[1]] == 0)
            {
                labirinto[posiTributo->posi[0] + 1][posiTributo->posi[1]] = 1;
                posicao_aux[0] = posiTributo->posi[0] + 1;
                posicao_aux[1] = posiTributo->posi[1];
                espera = addFila(espera, posicao_aux);
            }
            if (labirinto[posiTributo->posi[0]][posiTributo->posi[1] - 1] == 0)
            {
                labirinto[posiTributo->posi[0]][posiTributo->posi[1] - 1] = 1;
                posicao_aux[0] = posiTributo->posi[0];
                posicao_aux[1] = posiTributo->posi[1] - 1;
                espera = addFila(espera, posicao_aux);
            }
            posiTributo = removeFila(posiTributo);
        }
        posiTributo = espera;
    }

    if (posiTributo != NULL)
    {
        voltaCaminho(altura, largura, labirinto, inicio, posiTributo->posi);
    }
    else
    {
        printf("NO\n");
        exit(1);
    }
}