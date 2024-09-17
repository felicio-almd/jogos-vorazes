#include "maze.h"

// guardar a ultima posicao caminhada
void empilha(NoPilha *caminho, int posicaoNoMapa[2], char comando)
{
    NoPilha *novo = (NoPilha *)calloc(1, sizeof(NoPilha));
    NoPilha *aux = caminho;

    if (novo == NULL)
    {
        printf("Erro de alocacao de memoria.\n");
        exit(1);
    }

    // definir a direção e coordenadas do novo nó
    novo->direcao = comando;
    novo->coordenadasCaminho[0] = posicaoNoMapa[0];
    novo->coordenadasCaminho[1] = posicaoNoMapa[1];

    while (aux->prox != NULL)
    {
        aux = aux->prox;
    }

    aux->prox = novo;
    novo->ant = aux;
}

// retirar a ultima posicao caminhada
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

// funcao para imprimir o caminho feito pelo tributo
// Ao empilhar direções em uma pilha durante um labirinto, a última direção empilhada é a mais recente na sequência de movimentos.
// Para imprimir o caminho completo da navegação em ordem correta (da primeira direção tomada até a última),
// é necessário percorrer a pilha do topo (último elemento empilhado) até o fundo (primeiro elemento empilhado).
// por isso a pilha percorre até o ultimo nó e imprime o contrário
void imprimeCaminho(NoPilha *caminho)
{
    NoPilha *aux = caminho->prox;
    if (aux == NULL)
        return;
    while (aux->prox != NULL)
    {
        aux = aux->prox;
    }
    printf("%d\n", caminho->tamanho);
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
        printf("Erro de alocacao de memoria\n");
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

int moverBestantes(int **labirinto, int altura, int largura, Fila *bestantes, Fila **novaFila)
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

        // movimento para cima
        if (x > 0 && labirinto[x - 1][y] == 0)
        {
            labirinto[x - 1][y] = 3;
            aux = enfileira(aux, (int[]){x - 1, y});
        }

        // movimento para direita
        if (y < largura - 1 && labirinto[x][y + 1] == 0)
        {
            labirinto[x][y + 1] = 3;
            aux = enfileira(aux, (int[]){x, y + 1});
        }

        // movimento para baixo
        if (x < altura - 1 && labirinto[x + 1][y] == 0)
        {
            labirinto[x + 1][y] = 3;
            aux = enfileira(aux, (int[]){x + 1, y});
        }

        // movimento para esquerda
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

int encontrarSaida(int **labirinto, int altura, int largura, int x, int y, NoPilha *caminho, Fila *bestantes, Fila **novaFila)
{
    // Verifica se a posição atual é uma borda do labirinto (saída)
    if (x == 0 || y == 0 || x == altura - 1 || y == largura - 1)
    {
        empilha(caminho, (int[]){x, y}, '\0'); // marcou a saida o "\0" significa caractere NULO
        return 1;
    }

    // Marca a posição atual como visitada (1)
    labirinto[x][y] = 1;
    empilha(caminho, (int[]){x, y}, '\0'); // Marca visita

    moverBestantes(labirinto, altura, largura, bestantes, novaFila);

    int dx[] = {1, 0, -1, 0}; // ordem de verificação começa de baixo e faz
    int dy[] = {0, 1, 0, -1};
    char direcoes[] = {'D', 'R', 'U', 'L'};

    for (int i = 0; i < 4; i++)
    {
        int novoX = x + dx[i];
        int novoY = y + dy[i];

        if (novoX >= 0 && novoX < altura && novoY >= 0 && novoY < largura && labirinto[novoX][novoY] == 0)
        {
            if (encontrarSaida(labirinto, altura, largura, novoX, novoY, caminho, *novaFila, novaFila))
            {
                empilha(caminho, (int[]){novoX, novoY}, direcoes[i]);
                caminho->tamanho++;
                return 1;
            }
        }
    }

    // se nenhuma direção for válida, desempilha e retrocede a posição
    if (caminho->tamanho > 0)
        desempilha(caminho);
    return 0;
}
