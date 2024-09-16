#include "maze.h"

void empilha(NoPilha *caminho, int posicaoNoMapa[2], char comando)
{
    NoPilha *novo = (NoPilha *)calloc(1, sizeof(NoPilha));
    NoPilha *aux = caminho;

    if (novo == NULL)
    {
        printf("Erro de alocacao de memoria.\n");
        exit(1);
    }

    novo->direcao = comando;
    novo->coordenadasCaminho[0] = posicaoNoMapa[0];
    novo->coordenadasCaminho[1] = posicaoNoMapa[1];

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
    NoPilha *aux = caminho->prox; // Start from the first actual node, not the dummy head
    if (aux == NULL)
        return;
    while (aux->prox != NULL)
    {
        aux = aux->prox;
    }
    while (aux != caminho)
    {
        printf("%c", aux->direcao);
        aux = aux->ant;
    }
    printf("\n");
}

Fila *enfileira(Fila *posicaoNova, int posicao[2])
{
    Fila *novo = (Fila *)calloc(1, sizeof(Fila));
    if (novo == NULL)
    {
        printf("Erro de alocacao\n");
        exit(1);
    }

    novo->posicaoNoLabirinto[0] = posicao[0];
    novo->posicaoNoLabirinto[1] = posicao[1];

    Fila *aux = posicaoNova;
    if (posicaoNova == NULL)
        return novo;
    while (aux->prox != NULL)
        aux = aux->prox;
    aux->prox = novo;
    return posicaoNova;
}

Fila *removeFila(Fila *F)
{
    Fila *aux = F;
    F = aux->prox;
    free(aux);
    return F;
}

Fila *acharPosicaoAtual(int tipoEntidade, int altura, int largura, int **labirinto)
{
    int posicaoNoLabirinto[2];
    Fila *posicaoNova = NULL;
    if (tipoEntidade == 1)
    {
        for (int i = 0; i < altura; i++)
        {
            for (int j = 0; j < largura; j++)
            {
                if (labirinto[i][j] == tipoEntidade)
                {
                    posicaoNoLabirinto[0] = i;
                    posicaoNoLabirinto[1] = j;
                    posicaoNova = enfileira(posicaoNova, posicaoNoLabirinto);
                }
            }
        }
        return posicaoNova;
    }
    else
    {
        for (int i = 0; i < altura; i++)
        {
            for (int j = 0; j < largura; j++)
            {
                if (labirinto[i][j] == tipoEntidade)
                {
                    if (i != 0 && i != altura - 1 && j != 0 && j != largura - 1)
                    {
                        if (labirinto[i + 1][j] == 0 || labirinto[i - 1][j] == 0 || labirinto[i][j + 1] == 0 || labirinto[i][j - 1] == 0)
                        {
                            posicaoNoLabirinto[0] = i;
                            posicaoNoLabirinto[1] = j;
                            posicaoNova = enfileira(posicaoNova, posicaoNoLabirinto);
                        }
                    }
                    else
                    {
                        posicaoNoLabirinto[0] = i;
                        posicaoNoLabirinto[1] = j;
                        posicaoNova = enfileira(posicaoNova, posicaoNoLabirinto);
                    }
                }
            }
        }
        return posicaoNova;
    }
}

// void voltaCaminho(int altura, int largura, int **labirinto, int posicaoInicial[2], int posicaoFinal[2], NoPilha *caminho)
// {
//     // Vetor de possíveis direções (cima, direita, baixo, esquerda)
//     int direcoes[4][2] = {{-1, 0}, {0, 1}, {1, 0}, {0, -1}};
//     char direcaoCorrespondente[4] = {'D', 'L', 'U', 'R'}; // Direções opostas (cima->baixo, direita->esquerda)

//     if (posicaoFinal[0] == posicaoInicial[0] && posicaoFinal[1] == posicaoInicial[1])
//     {
//         printf("YES\n");
//         printf("%d\n", caminho->tamanho);
//         imprimeCaminho(caminho);
//         return;
//     }

//     // Iterar pelas possíveis direções
//     for (int i = 0; i < 4; i++)
//     {
//         int novaLinha = posicaoFinal[0] + direcoes[i][0];
//         int novaColuna = posicaoFinal[1] + direcoes[i][1];

//         // Verificar se a nova posição está dentro dos limites e se é válida (labirinto == 1)
//         if (novaLinha >= 0 && novaLinha < altura && novaColuna >= 0 && novaColuna < largura && labirinto[novaLinha][novaColuna] == 1)
//         {
//             labirinto[posicaoFinal[0]][posicaoFinal[1]] = 4; // Marcar como visitado
//             posicaoFinal[0] = novaLinha;
//             posicaoFinal[1] = novaColuna;
//             empilha(caminho, posicaoFinal, direcaoCorrespondente[i]); // Adicionar direção à pilha
//             voltaCaminho(altura, largura, labirinto, posicaoInicial, posicaoFinal, caminho);
//             return;
//         }
//     }

//     // Se não encontrar nenhuma direção válida, voltar (desempilhar)
//     for (int i = 0; i < 4; i++)
//     {
//         int novaLinha = posicaoFinal[0] + direcoes[i][0];
//         int novaColuna = posicaoFinal[1] + direcoes[i][1];

//         // Verificar se a nova posição é um caminho visitado (labirinto == 4)
//         if (novaLinha >= 0 && novaLinha < altura && novaColuna >= 0 && novaColuna < largura && labirinto[novaLinha][novaColuna] == 4)
//         {
//             labirinto[posicaoFinal[0]][posicaoFinal[1]] = 3;
//             posicaoFinal[0] = novaLinha;
//             posicaoFinal[1] = novaColuna;
//             desempilha(caminho);
//             voltaCaminho(altura, largura, labirinto, posicaoInicial, posicaoFinal, caminho);
//             return;
//         }
//     }
// }

int moverBestantesRecursivo(int **labirinto, int altura, int largura, Fila *bestantes, Fila **novaFila)
{
    if (bestantes == NULL)
    {
        return 0;
    }

    Fila *aux = NULL;

    while (bestantes != NULL)
    {
        int x = bestantes->posicaoNoLabirinto[0];
        int y = bestantes->posicaoNoLabirinto[1];

        // Movimenta para cima
        if (x > 0 && labirinto[x - 1][y] == 0)
        {
            labirinto[x - 1][y] = 3;
            aux = enfileira(aux, (int[]){x - 1, y});
        }

        // Movimenta para direita
        if (y < largura - 1 && labirinto[x][y + 1] == 0)
        {
            labirinto[x][y + 1] = 3;
            aux = enfileira(aux, (int[]){x, y + 1});
        }

        // Movimenta para baixo
        if (x < altura - 1 && labirinto[x + 1][y] == 0)
        {
            labirinto[x + 1][y] = 3;
            aux = enfileira(aux, (int[]){x + 1, y});
        }

        // Movimenta para esquerda
        if (y > 0 && labirinto[x][y - 1] == 0)
        {
            labirinto[x][y - 1] = 3;
            aux = enfileira(aux, (int[]){x, y - 1});
        }

        bestantes = removeFila(bestantes);
    }

    *novaFila = aux;
    return 1;
}

int encontrarSaidaRecursiva(int **labirinto, int altura, int largura, int x, int y, NoPilha *caminho, Fila *bestantes, Fila **novaFila)
{
    // Verifica se a posição atual é uma borda do labirinto (saída)
    if (x == 0 || y == 0 || x == altura - 1 || y == largura - 1)
    {
        empilha(caminho, (int[]){x, y}, 'S'); // Marca saída
        return 1;                             // Encontrou saída
    }

    // Marca a posição atual como visitada (1)
    labirinto[x][y] = 1;
    empilha(caminho, (int[]){x, y}, 'V'); // Marca visita

    // Atualiza posições dos bestantes
    moverBestantesRecursivo(labirinto, altura, largura, bestantes, novaFila);

    int dx[] = {1, 0, -1, 0}; // Mudança na ordem: primeiro para baixo
    int dy[] = {0, 1, 0, -1};
    char direcoes[] = {'D', 'R', 'U', 'L'}; // Adaptado para a nova ordem

    for (int i = 0; i < 4; i++)
    {
        int novoX = x + dx[i];
        int novoY = y + dy[i];

        if (novoX >= 0 && novoX < altura && novoY >= 0 && novoY < largura && labirinto[novoX][novoY] == 0)
        {
            if (encontrarSaidaRecursiva(labirinto, altura, largura, novoX, novoY, caminho, *novaFila, novaFila))
            {
                empilha(caminho, (int[]){novoX, novoY}, direcoes[i]);
                return 1;
            }
        }
    }

    // Se nenhuma direção for válida, desempilha e retrocede (backtracking)
    desempilha(caminho);
    return 0;
}
