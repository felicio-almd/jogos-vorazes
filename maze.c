#include "maze.h"

No *criaNo()
{
    No *novo;
    novo = (No *)calloc(1, sizeof(No));
    if (novo == NULL)
    {
        printf("ERRO: problemas com a alocacao de memoria . \n");
        exit(1);
    }
    return novo;
}

void empilha(No *Caminho, int posicao[2], char comando)
{
    No *novo = criaNo();
    novo->direcao = comando;
    novo->coordenadasCaminho[0] = posicao[0];
    novo->coordenadasCaminho[1] = posicao[1];
    No *aux = Caminho;
    while (aux->prox != NULL)
    {
        aux = aux->prox;
    }
    aux->prox = novo;
    novo->ant = aux;
    Caminho->tamanho++;
}
void desempilha(No *caminho)
{
    No *aux = caminho;
    while (aux->prox != NULL)
    {
        aux = aux->prox;
    }
    aux->ant->prox = NULL;
    caminho->tamanho--;
    free(aux);
}

void imprimeCaminho(No *Caminho)
{
    No *aux = Caminho->prox;
    if (aux == NULL)
        return;
    while (aux != NULL)
    {
        printf("%c", aux->direcao);
        aux = aux->prox;
    }
    printf("\n");
}

Fila *enfileira(Fila *F, int posicao[2])
{
    Fila *novo = (Fila *)calloc(1, sizeof(Fila));
    if (novo == NULL)
    {
        printf("Erro de alocacao\n");
        exit(1);
    }
    novo->posicaoNoLabirinto[0] = posicao[0];
    novo->posicaoNoLabirinto[1] = posicao[1];
    Fila *aux = F;
    if (F == NULL)
        return novo;
    while (aux->prox != NULL)
        aux = aux->prox;
    aux->prox = novo;
    return F;
}

Fila *removeFila(Fila *F)
{
    Fila *aux = F;
    F = aux->prox;
    free(aux);
    return F;
}

Fila *acharPosicaoAtual(int altura, int largura, int **labirinto, int M_A)
{
    int posicao[2];
    Fila *posi = NULL;
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
                    posi = enfileira(posi, posicao);
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
                            posi = enfileira(posi, posicao);
                        }
                    }
                    else
                    {
                        posicao[0] = i;
                        posicao[1] = j;
                        posi = enfileira(posi, posicao);
                    }
                }
            }
        }
        return posi;
    }
}

void voltaCaminho(int altura, int largura, int **labirinto, int inicial[2], int final[2])
{
    No *caminho = criaNo();
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
    printf("%d\n", caminho->tamanho);
    imprimeCaminho(caminho);
}

void encontrarSaidaLabirinto(int altura, int largura, int **labirinto, Fila *posiTributo, Fila *posiMonstros)
{
    int inicio[2];
    inicio[0] = posiTributo->posicaoNoLabirinto[0];
    inicio[1] = posiTributo->posicaoNoLabirinto[1];
    Fila *espera;
    int posicao_aux[2];
    while (posiTributo != NULL && (posiTributo->posicaoNoLabirinto[0] != 0 && posiTributo->posicaoNoLabirinto[1] != largura - 1 && posiTributo->posicaoNoLabirinto[0] != altura - 1 && posiTributo->posicaoNoLabirinto[1] != 0))
    {
        espera = NULL;
        while (posiMonstros != NULL)
        {
            if (posiMonstros->posicaoNoLabirinto[0] != 0 && labirinto[posiMonstros->posicaoNoLabirinto[0] - 1][posiMonstros->posicaoNoLabirinto[1]] == 0)
            {
                labirinto[posiMonstros->posicaoNoLabirinto[0] - 1][posiMonstros->posicaoNoLabirinto[1]] = 2;
                posicao_aux[0] = posiMonstros->posicaoNoLabirinto[0] - 1;
                posicao_aux[1] = posiMonstros->posicaoNoLabirinto[1];
                espera = enfileira(espera, posicao_aux);
            }
            if (posiMonstros->posicaoNoLabirinto[1] != largura - 1 && labirinto[posiMonstros->posicaoNoLabirinto[0]][posiMonstros->posicaoNoLabirinto[1] + 1] == 0)
            {
                labirinto[posiMonstros->posicaoNoLabirinto[0]][posiMonstros->posicaoNoLabirinto[1] + 1] = 2;
                posicao_aux[0] = posiMonstros->posicaoNoLabirinto[0];
                posicao_aux[1] = posiMonstros->posicaoNoLabirinto[1] + 1;
                espera = enfileira(espera, posicao_aux);
            }
            if (posiMonstros->posicaoNoLabirinto[0] != altura - 1 && labirinto[posiMonstros->posicaoNoLabirinto[0] + 1][posiMonstros->posicaoNoLabirinto[1]] == 0)
            {
                labirinto[posiMonstros->posicaoNoLabirinto[0] + 1][posiMonstros->posicaoNoLabirinto[1]] = 2;
                posicao_aux[0] = posiMonstros->posicaoNoLabirinto[0] + 1;
                posicao_aux[1] = posiMonstros->posicaoNoLabirinto[1];
                espera = enfileira(espera, posicao_aux);
            }
            if (posiMonstros->posicaoNoLabirinto[1] != 0 && labirinto[posiMonstros->posicaoNoLabirinto[0]][posiMonstros->posicaoNoLabirinto[1] - 1] == 0)
            {
                labirinto[posiMonstros->posicaoNoLabirinto[0]][posiMonstros->posicaoNoLabirinto[1] - 1] = 2;
                posicao_aux[0] = posiMonstros->posicaoNoLabirinto[0];
                posicao_aux[1] = posiMonstros->posicaoNoLabirinto[1] - 1;
                espera = enfileira(espera, posicao_aux);
            }
            posiMonstros = removeFila(posiMonstros);
        }
        posiMonstros = espera;
        espera = NULL;
        while (posiTributo != NULL && (posiTributo->posicaoNoLabirinto[0] != 0 && posiTributo->posicaoNoLabirinto[1] != largura - 1 && posiTributo->posicaoNoLabirinto[0] != altura - 1 && posiTributo->posicaoNoLabirinto[1] != 0))
        {
            if (labirinto[posiTributo->posicaoNoLabirinto[0] - 1][posiTributo->posicaoNoLabirinto[1]] == 0)
            {
                labirinto[posiTributo->posicaoNoLabirinto[0] - 1][posiTributo->posicaoNoLabirinto[1]] = 1;
                posicao_aux[0] = posiTributo->posicaoNoLabirinto[0] - 1;
                posicao_aux[1] = posiTributo->posicaoNoLabirinto[1];
                espera = enfileira(espera, posicao_aux);
            }
            if (labirinto[posiTributo->posicaoNoLabirinto[0]][posiTributo->posicaoNoLabirinto[1] + 1] == 0)
            {
                labirinto[posiTributo->posicaoNoLabirinto[0]][posiTributo->posicaoNoLabirinto[1] + 1] = 1;
                posicao_aux[0] = posiTributo->posicaoNoLabirinto[0];
                posicao_aux[1] = posiTributo->posicaoNoLabirinto[1] + 1;
                espera = enfileira(espera, posicao_aux);
            }
            if (labirinto[posiTributo->posicaoNoLabirinto[0] + 1][posiTributo->posicaoNoLabirinto[1]] == 0)
            {
                labirinto[posiTributo->posicaoNoLabirinto[0] + 1][posiTributo->posicaoNoLabirinto[1]] = 1;
                posicao_aux[0] = posiTributo->posicaoNoLabirinto[0] + 1;
                posicao_aux[1] = posiTributo->posicaoNoLabirinto[1];
                espera = enfileira(espera, posicao_aux);
            }
            if (labirinto[posiTributo->posicaoNoLabirinto[0]][posiTributo->posicaoNoLabirinto[1] - 1] == 0)
            {
                labirinto[posiTributo->posicaoNoLabirinto[0]][posiTributo->posicaoNoLabirinto[1] - 1] = 1;
                posicao_aux[0] = posiTributo->posicaoNoLabirinto[0];
                posicao_aux[1] = posiTributo->posicaoNoLabirinto[1] - 1;
                espera = enfileira(espera, posicao_aux);
            }
            posiTributo = removeFila(posiTributo);
        }
        posiTributo = espera;
    }

    if (posiTributo != NULL)
    {
        voltaCaminho(altura, largura, labirinto, inicio, posiTributo->posicaoNoLabirinto);
    }
    else
    {
        printf("NO\n");
        exit(1);
    }
}