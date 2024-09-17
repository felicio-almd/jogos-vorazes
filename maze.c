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

// função para adicionar nós com as posições na fila
// a fila é usada para gerir as posições durante a busca
Fila *enfileira(Fila *posicaoNova, int posicao[2])
{
    Fila *novo = (Fila *)calloc(1, sizeof(Fila));
    if (novo == NULL)
    {
        printf("Erro de alocacao de memoria\n");
        exit(1);
    }

    // guarda a nova posição fornecida no novo nó da fila
    novo->posicaoNoLabirinto[0] = posicao[0];
    novo->posicaoNoLabirinto[1] = posicao[1];


    // percore a fila e coloca o nó na ultima posição
    Fila *aux = posicaoNova;
    if (posicaoNova == NULL)
        return novo;
    while (aux->prox != NULL)
        aux = aux->prox;
    aux->prox = novo;
    return posicaoNova;
}

// função para remover o nó da fila quando a posição não é mais
// necessaria para ser explorada
Fila *removeFila(Fila *F)
{
    Fila *aux = F;
    F = aux->prox;
    free(aux);
    return F;
}

// usa a fila para armazenar posições iniciais no labirinto que precisam ser
// verificadas para possíveis movimentos ou para a identificação de pontos de interesse.
Fila *acharPosicaoAtual(int tipoEntidade, int altura, int largura, int **labirinto)
{
    // o tipo de entidade pode ser tributo ou bestante
    int posicaoNoLabirinto[2];



    // percore a fila e coloca o nó na ultima posição
    Fila *aux = posicaoNova;
    if (posicaoNova == NULL)
        return novo;
    while (aux->prox != NULL)
        aux = aux->prox;
    aux->prox = novo;
    return posicaoNova;
}

// função para remover o nó da fila quando a posição não é mais
// necessaria para ser explorada
Fila *removeFila(Fila *F)
{
    Fila *aux = F;
    F = aux->prox;
    free(aux);
    return F;
}

// usa a fila para armazenar posições iniciais no labirinto que precisam ser
// verificadas para possíveis movimentos ou para a identificação de pontos de interesse.
Fila *acharPosicaoAtual(int tipoEntidade, int altura, int largura, int **labirinto)
{
    // o tipo de entidade pode ser tributo ou bestante
    int posicaoNoLabirinto[2];


    // Ponteiro para a fila que armazenará as posições encontradas
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
                    // coloca a posição à fila de posições encontradas
                    posicaoNova = enfileira(posicaoNova, posicaoNoLabirinto);
                }
            }
        }
        return posicaoNova;
    }
    else
    // para os bestantes
    {
        for (int i = 0; i < altura; i++)
        {
            for (int j = 0; j < largura; j++)
            {
                if (labirinto[i][j] == tipoEntidade)
                {
                    // verifica se ele nao esta na borda
                    if (i != 0 && i != altura - 1 && j != 0 && j != largura - 1)
                    {
                        // aqui verifica se o bestante ele pode se movimentar
                        // o 0 equivale como o chão
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
        // Retorna a fila com todas as posições encontradas
        return posicaoNova;
    }
}

// Função para mover bestantes (ou seja, posições a serem exploradas) em todas as direções possíveis
int moverBestantes(int **labirinto, int altura, int largura, Fila *bestantes, Fila **novaFila)
{
    if (bestantes == NULL)
    {
        return 0;
    }

    Fila *aux = NULL;

    // enquanto houver posições na fila de bestantes
    while (bestantes != NULL)
    {
        int x = bestantes->posicaoNoLabirinto[0];
        int y = bestantes->posicaoNoLabirinto[1];

        // movimento para cima
        if (x > 0 && labirinto[x - 1][y] == 0)
        {
            labirinto[x - 1][y] = 3;                 // marca a célula acima como visitada (3)
            aux = enfileira(aux, (int[]){x - 1, y}); // adiciona a nova posição (x - 1, y) à fila auxiliar
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

        // tira o bestante atual da fila após processá-lo
        bestantes = removeFila(bestantes);
    }

    *novaFila = aux;
    // retorna que o movimento foi feito
    return 1;
}

int encontrarSaida(int **labirinto, int altura, int largura, int x, int y, NoPilha *caminho, Fila *bestantes, Fila **novaFila)
{
    // se a posição atual é uma borda do labirinto
    if (x == 0 || y == 0 || x == altura - 1 || y == largura - 1)
    {
        empilha(caminho, (int[]){x, y}, '\0'); // marca a saida o "\0" significa caractere NULO
        return 1;
    }

    labirinto[x][y] = 1;                   // marca a posição atual como visitada (1)
    empilha(caminho, (int[]){x, y}, '\0'); // guarda a posição que ja foi visitada na pilha que tem o caminho

    moverBestantes(labirinto, altura, largura, bestantes, novaFila);


    int dx[] = {1, 0, -1, 0}; // ordem de verificação das direções, começa de baixo e faz
    int dy[] = {0, 1, 0, -1};
    char direcoes[] = {'D', 'R', 'U', 'L'};

    // loop para tentar nas 4 direções
    for (int i = 0; i < 4; i++)
    {
        int novoX = x + dx[i];
        int novoY = y + dy[i];

        if (novoX >= 0 && novoX < altura && novoY >= 0 && novoY < largura && labirinto[novoX][novoY] == 0)
        {
            // chama a função recursiva novamente para tentar novas posições
            if (encontrarSaida(labirinto, altura, largura, novoX, novoY, caminho, *novaFila, novaFila))
            {
                empilha(caminho, (int[]){novoX, novoY}, direcoes[i]);
                caminho->tamanho++; // acrescenta 1 na pilha do caminho
                // retorna 1 e indica que a saída foi encontrada a partir da posição atual
                return 1;
            }
        }
    }



    int dx[] = {1, 0, -1, 0}; // ordem de verificação das direções, começa de baixo e faz
    int dy[] = {0, 1, 0, -1};
    char direcoes[] = {'D', 'R', 'U', 'L'};

    // loop para tentar nas 4 direções
    for (int i = 0; i < 4; i++)
    {
        int novoX = x + dx[i];
        int novoY = y + dy[i];

        if (novoX >= 0 && novoX < altura && novoY >= 0 && novoY < largura && labirinto[novoX][novoY] == 0)
        {
            // chama a função recursiva novamente para tentar novas posições
            if (encontrarSaida(labirinto, altura, largura, novoX, novoY, caminho, *novaFila, novaFila))
            {
                empilha(caminho, (int[]){novoX, novoY}, direcoes[i]);
                caminho->tamanho++; // acrescenta 1 na pilha do caminho
                // retorna 1 e indica que a saída foi encontrada a partir da posição atual
                return 1;
            }
        }
    }


    // se nenhuma direção for válida, desempilha e retrocede a posição
    if (caminho->tamanho > 0)
        desempilha(caminho);
    //  retorna 0 e indica que a saída não foi encontrada a partir da posição atual
    return 0;

}

}

