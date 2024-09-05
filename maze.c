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

    carregaLabirintoAleatorio(labirinto);

    int i, j;
    for (i = 0; i < labirinto->altura; i++)
    {
        for (j = 0; j < labirinto->largura; j++)
        {
            if (labirinto->mapa[i][j] != '.' && labirinto->mapa[i][j] != '#' && labirinto->mapa[i][j] != 'A' && labirinto->mapa[i][j] != 'M')
            {
                printf("Erro: Caractere inválido '%c' encontrado no labirinto.\n", labirinto->mapa[i][j]);
                return;
            }
        }
    }
}

void imprimeLabirinto(Labirinto *labirinto)
{
    int i, j;
    for (i = 0; i < labirinto->altura; i++)
    {
        for (j = 0; j < labirinto->largura; j++)
        {
            printf("%c", labirinto->mapa[i][j]);
        }
        printf("\n"); // Adiciona uma nova linha após cada linha do labirinto
    }
}



void inicializarPilha(Pilha *pilha, int tamanho_maximo)
{
    pilha->pilha = (Posicao *)malloc(tamanho_maximo * sizeof(Posicao));
    if (pilha->pilha == NULL)
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

void empilhar(Pilha *pilha, Posicao pos)
{
    if (pilha->topo < pilha->tamanho_maximo - 1)
    {
        pilha->pilha[++(pilha->topo)] = pos;
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
        exit(1); // Opcionalmente, pode-se usar um valor de retorno especial ou definir um comportamento alternativo
    }
    return pilha->pilha[(pilha->topo)--];
}

void imprimirPilha(Pilha *pilha) {
    for (int i = 0; i <= pilha->topo; i++) {
        printf("(%d, %d)", pilha->pilha[i].x, pilha->pilha[i].y);
        if (i < pilha->topo) {
            printf(" <- ");
        }
    }
    printf("\n");
    printf("Tamanho da pilha: %d\n", pilha->topo + 1);
}

void desalocarPilha(Pilha *pilha)
{
    free(pilha->pilha);
}

// Direções para cima, baixo, esquerda, direita
int dx[4] = {-1, 1, 0, 0};
int dy[4] = {0, 0, -1, 1};


// int existeSaida(Labirinto *labirinto, char direcao){
//     printf("\nx = %d \ny = %d\n\n", labirinto->posicaoInicial.x, labirinto->posicaoInicial.y);

    
// }

int encontrarCaminho(Labirinto *labirinto, Posicao posicaoAtual, Pilha *caminho) {
    // Se a posição atual estiver na borda do labirinto, encontramos a saída
    if (posicaoAtual.x == 0 || posicaoAtual.x == labirinto->altura - 1 ||
        posicaoAtual.y == 0 || posicaoAtual.y == labirinto->largura - 1) {
        empilhar(caminho, posicaoAtual);
        return 1;
    }

    // Marca a posição atual como visitada
    labirinto->mapa[posicaoAtual.x][posicaoAtual.y] = '#';

    // Testa todas as quatro direções (cima, baixo, esquerda, direita)
    for (int i = 0; i < 4; i++) {
        Posicao novaPosicao = {posicaoAtual.x + dx[i], posicaoAtual.y + dy[i]};

        // Verifica se a nova posição está dentro dos limites e é um caminho válido
        if (novaPosicao.x >= 0 && novaPosicao.x < labirinto->altura &&
            novaPosicao.y >= 0 && novaPosicao.y < labirinto->largura &&
            labirinto->mapa[novaPosicao.x][novaPosicao.y] == '.') {
            
            if (encontrarCaminho(labirinto, novaPosicao, caminho)) {
                empilhar(caminho, posicaoAtual);
                return 1;
            }
        }
    }

    // Se não encontrou um caminho, desmarca a posição atual como visitada
    labirinto->mapa[posicaoAtual.x][posicaoAtual.y] = '.';
    return 0;
}