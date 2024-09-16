#include "maze.h"

void empilha(NoPilha *caminho, int posicaoNoMapa[2], char direcaoCorrespondente)
{
    NoPilha *novo = (NoPilha *)calloc(1, sizeof(NoPilha));
    NoPilha *aux = caminho;

    if (novo == NULL)
    {
        printf("Erro de alocacao de memoria.\n");
        exit(1);
    }

    novo->direcao = direcaoCorrespondente;
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

Fila *removeFila(Fila *posicaoNova)
{
    Fila *aux = posicaoNova;
    posicaoNova = aux->prox;
    free(aux);
    return posicaoNova;
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

void imprimeCaminho(NoPilha *caminho)
{
    NoPilha *aux = caminho->prox;
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

void voltaCaminho(int altura, int largura, int **labirinto, int posicaoInicial[2], int posicaoFinal[2], NoPilha *caminho)
{
    // Vetor de possíveis direções (cima, direita, baixo, esquerda)
    int direcoes[4][2] = {{-1, 0}, {0, 1}, {1, 0}, {0, -1}};
    char direcaoCorrespondente[4] = {'D', 'L', 'U', 'R'}; // Direções opostas (cima->baixo, direita->esquerda)

    if (posicaoFinal[0] == posicaoInicial[0] && posicaoFinal[1] == posicaoInicial[1])
    {
        printf("YES\n");
        printf("%d\n", caminho->tamanho);
        imprimeCaminho(caminho);
        return;
    }

    // Iterar pelas possíveis direções
    for (int i = 0; i < 4; i++)
    {
        int novaLinha = posicaoFinal[0] + direcoes[i][0];
        int novaColuna = posicaoFinal[1] + direcoes[i][1];

        // Verificar se a nova posição está dentro dos limites e se é válida (labirinto == 1)
        if (novaLinha >= 0 && novaLinha < altura && novaColuna >= 0 && novaColuna < largura && labirinto[novaLinha][novaColuna] == 1)
        {
            labirinto[posicaoFinal[0]][posicaoFinal[1]] = 4; // Marcar como visitado
            posicaoFinal[0] = novaLinha;
            posicaoFinal[1] = novaColuna;
            empilha(caminho, posicaoFinal, direcaoCorrespondente[i]); // Adicionar direção à pilha
            voltaCaminho(altura, largura, labirinto, posicaoInicial, posicaoFinal, caminho);
            return;
        }
    }

    // Se não encontrar nenhuma direção válida, voltar (desempilhar)
    for (int i = 0; i < 4; i++)
    {
        int novaLinha = posicaoFinal[0] + direcoes[i][0];
        int novaColuna = posicaoFinal[1] + direcoes[i][1];

        // Verificar se a nova posição é um caminho visitado (labirinto == 4)
        if (novaLinha >= 0 && novaLinha < altura && novaColuna >= 0 && novaColuna < largura && labirinto[novaLinha][novaColuna] == 4)
        {
            labirinto[posicaoFinal[0]][posicaoFinal[1]] = 3;
            posicaoFinal[0] = novaLinha;
            posicaoFinal[1] = novaColuna;
            desempilha(caminho);
            voltaCaminho(altura, largura, labirinto, posicaoInicial, posicaoFinal, caminho);
            return;
        }
    }
}

void processarMovimentosBestante(int **labirinto, int altura, int largura, Fila *posicaoBestante, Fila **aux)
{
    int posicao_aux[2];

    while (posicaoBestante != NULL)
    {
        // Cima
        if (posicaoBestante->posicaoNoLabirinto[0] != 0 && labirinto[posicaoBestante->posicaoNoLabirinto[0] - 1][posicaoBestante->posicaoNoLabirinto[1]] == 0)
        {
            labirinto[posicaoBestante->posicaoNoLabirinto[0] - 1][posicaoBestante->posicaoNoLabirinto[1]] = 2;
            posicao_aux[0] = posicaoBestante->posicaoNoLabirinto[0] - 1;
            posicao_aux[1] = posicaoBestante->posicaoNoLabirinto[1];
            *aux = enfileira(*aux, posicao_aux);
        }
        // Direita
        if (posicaoBestante->posicaoNoLabirinto[1] != largura - 1 && labirinto[posicaoBestante->posicaoNoLabirinto[0]][posicaoBestante->posicaoNoLabirinto[1] + 1] == 0)
        {
            labirinto[posicaoBestante->posicaoNoLabirinto[0]][posicaoBestante->posicaoNoLabirinto[1] + 1] = 2;
            posicao_aux[0] = posicaoBestante->posicaoNoLabirinto[0];
            posicao_aux[1] = posicaoBestante->posicaoNoLabirinto[1] + 1;
            *aux = enfileira(*aux, posicao_aux);
        }
        // Baixo
        if (posicaoBestante->posicaoNoLabirinto[0] != altura - 1 && labirinto[posicaoBestante->posicaoNoLabirinto[0] + 1][posicaoBestante->posicaoNoLabirinto[1]] == 0)
        {
            labirinto[posicaoBestante->posicaoNoLabirinto[0] + 1][posicaoBestante->posicaoNoLabirinto[1]] = 2;
            posicao_aux[0] = posicaoBestante->posicaoNoLabirinto[0] + 1;
            posicao_aux[1] = posicaoBestante->posicaoNoLabirinto[1];
            *aux = enfileira(*aux, posicao_aux);
        }
        // Esquerda
        if (posicaoBestante->posicaoNoLabirinto[1] != 0 && labirinto[posicaoBestante->posicaoNoLabirinto[0]][posicaoBestante->posicaoNoLabirinto[1] - 1] == 0)
        {
            labirinto[posicaoBestante->posicaoNoLabirinto[0]][posicaoBestante->posicaoNoLabirinto[1] - 1] = 2;
            posicao_aux[0] = posicaoBestante->posicaoNoLabirinto[0];
            posicao_aux[1] = posicaoBestante->posicaoNoLabirinto[1] - 1;
            *aux = enfileira(*aux, posicao_aux);
        }
        posicaoBestante = removeFila(posicaoBestante);
    }
}

void processarMovimentosTributo(int **labirinto, Fila *posicaoTributo, Fila **aux)
{
    int posicao_aux[2];

    while (posicaoTributo != NULL)
    {
        // Cima
        if (labirinto[posicaoTributo->posicaoNoLabirinto[0] - 1][posicaoTributo->posicaoNoLabirinto[1]] == 0)
        {
            labirinto[posicaoTributo->posicaoNoLabirinto[0] - 1][posicaoTributo->posicaoNoLabirinto[1]] = 1;
            posicao_aux[0] = posicaoTributo->posicaoNoLabirinto[0] - 1;
            posicao_aux[1] = posicaoTributo->posicaoNoLabirinto[1];
            *aux = enfileira(*aux, posicao_aux);
        }
        // Direita
        if (labirinto[posicaoTributo->posicaoNoLabirinto[0]][posicaoTributo->posicaoNoLabirinto[1] + 1] == 0)
        {
            labirinto[posicaoTributo->posicaoNoLabirinto[0]][posicaoTributo->posicaoNoLabirinto[1] + 1] = 1;
            posicao_aux[0] = posicaoTributo->posicaoNoLabirinto[0];
            posicao_aux[1] = posicaoTributo->posicaoNoLabirinto[1] + 1;
            *aux = enfileira(*aux, posicao_aux);
        }
        // Baixo
        if (labirinto[posicaoTributo->posicaoNoLabirinto[0] + 1][posicaoTributo->posicaoNoLabirinto[1]] == 0)
        {
            labirinto[posicaoTributo->posicaoNoLabirinto[0] + 1][posicaoTributo->posicaoNoLabirinto[1]] = 1;
            posicao_aux[0] = posicaoTributo->posicaoNoLabirinto[0] + 1;
            posicao_aux[1] = posicaoTributo->posicaoNoLabirinto[1];
            *aux = enfileira(*aux, posicao_aux);
        }
        // Esquerda
        if (labirinto[posicaoTributo->posicaoNoLabirinto[0]][posicaoTributo->posicaoNoLabirinto[1] - 1] == 0)
        {
            labirinto[posicaoTributo->posicaoNoLabirinto[0]][posicaoTributo->posicaoNoLabirinto[1] - 1] = 1;
            posicao_aux[0] = posicaoTributo->posicaoNoLabirinto[0];
            posicao_aux[1] = posicaoTributo->posicaoNoLabirinto[1] - 1;
            *aux = enfileira(*aux, posicao_aux);
        }
        posicaoTributo = removeFila(posicaoTributo);
    }
}

void encontrarSaidaLabirinto(int **labirinto, int altura, int largura, Fila *posicaoTributo, Fila *posicaoBestante)
{
    Fila *aux;
    int inicio[2] = {posicaoTributo->posicaoNoLabirinto[0], posicaoTributo->posicaoNoLabirinto[1]};

    while (posicaoTributo != NULL && (posicaoTributo->posicaoNoLabirinto[0] != 0 && posicaoTributo->posicaoNoLabirinto[1] != largura - 1 &&
                                      posicaoTributo->posicaoNoLabirinto[0] != altura - 1 && posicaoTributo->posicaoNoLabirinto[1] != 0))
    {

        aux = NULL;

        // Processa movimentação dos bestantes
        processarMovimentosBestante(labirinto, altura, largura, posicaoBestante, &aux);
        posicaoBestante = aux;

        // Processa movimentação do tributo
        aux = NULL;
        processarMovimentosTributo(labirinto, posicaoTributo, &aux);
        posicaoTributo = aux;
    }

    NoPilha *caminho = (NoPilha *)calloc(1, sizeof(NoPilha));

    if (caminho == NULL)
    {
        printf("ERRO: problemas com a alocacao de memoria.\n");
        exit(1);
    }

    if (posicaoTributo != NULL)
    {
        voltaCaminho(altura, largura, labirinto, inicio, posicaoTributo->posicaoNoLabirinto, caminho);
    }
    else
    {
        printf("NO\n");
        exit(1);
    }
}