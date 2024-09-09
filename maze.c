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
    printf("\n");
    for (i = 0; i < labirinto->altura; i++)
    {
        for (j = 0; j < labirinto->largura; j++)
        {
            printf("%c", labirinto->mapa[i][j]);
        }
        printf("\n"); // Adiciona uma nova linha após cada linha do labirinto
    }
    printf("\n");
}

void inicializarPilha(Pilha *pilha, int tamanho_maximo)
{
    pilha->pilha = (Posicao *)malloc(tamanho_maximo * sizeof(Posicao));
    pilha->movimentos = (char *)malloc(tamanho_maximo * sizeof(char)); // Aloca espaço para os movimentos
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
        pilha->movimentos[pilha->topo] = movimento; // Armazena o movimento
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
    printf("Posição inicial: (Linha: %d, Coluna: %d)\n", pilha->pilha[0].x + 1, pilha->pilha[0].y + 1);
    for (int i = pilha->topo; i >= 0; i--)
    {
        printf("(%d,%d) -> ", pilha->pilha[i].x + 1, pilha->pilha[i].y + 1);
    }
    printf("\n");
    for (int i = pilha->topo; i >= 0; i--)
    {
        printf("%c", pilha->movimentos[i]);
    }
    printf("\nSaiu\n");
    printf("Tamanho da pilha: %d\n", pilha->topo);
}

void desalocarPilha(Pilha *pilha)
{
    free(pilha->pilha);
    free(pilha->movimentos); // Libera a memória dos movimentos
}

// Direções para cima, baixo, esquerda, direita
int dx[4] = {-1, 1, 0, 0};
int dy[4] = {0, 0, -1, 1};
char movimentos[4] = {'U', 'D', 'L', 'R'}; // Cima, Baixo, Esquerda, Direita


void inicializarMonstro(Labirinto *labirinto, Monstro *monstro) {
    do {
        monstro->posicao.x = rand() % labirinto->altura;
        monstro->posicao.y = rand() % labirinto->largura;
    } while (labirinto->mapa[monstro->posicao.x][monstro->posicao.y] != '.');
    
    labirinto->mapa[monstro->posicao.x][monstro->posicao.y] = 'M';
}

void moverMonstro(Labirinto *labirinto, Monstro *monstro) {
    int direcao = rand() % 4;
    Posicao novaPosicao = {
        monstro->posicao.x + dx[direcao],
        monstro->posicao.y + dy[direcao]
    };

    if (novaPosicao.x >= 0 && novaPosicao.x < labirinto->altura &&
        novaPosicao.y >= 0 && novaPosicao.y < labirinto->largura &&
        labirinto->mapa[novaPosicao.x][novaPosicao.y] == '.') {
        
        labirinto->mapa[monstro->posicao.x][monstro->posicao.y] = '.';
        monstro->posicao = novaPosicao;
        labirinto->mapa[monstro->posicao.x][monstro->posicao.y] = 'M';
    }
}



int encontrarCaminho(Labirinto *labirinto, Posicao posicaoAtual, Pilha *caminho, Monstro *monstro) {
    // Verifica se chegou à borda (condição de saída)
    if (posicaoAtual.x == 0 || posicaoAtual.x == labirinto->altura - 1 ||
        posicaoAtual.y == 0 || posicaoAtual.y == labirinto->largura - 1) {
        empilhar(caminho, posicaoAtual, '\0');
        return 1;
    }

    // Marca a posição atual como visitada
    labirinto->mapa[posicaoAtual.x][posicaoAtual.y] = '#';

    // Move o monstro
    moverMonstro(labirinto, monstro);

    // Verifica se o monstro pegou o jogador
    if (posicaoAtual.x == monstro->posicao.x && posicaoAtual.y == monstro->posicao.y) {
        printf("O monstro pegou o jogador!\n");
        return 0;
    }

    // Testa todas as quatro direções
    for (int i = 0; i < 4; i++) {
        Posicao novaPosicao = {posicaoAtual.x + dx[i], posicaoAtual.y + dy[i]};

        if (novaPosicao.x >= 0 && novaPosicao.x < labirinto->altura &&
            novaPosicao.y >= 0 && novaPosicao.y < labirinto->largura &&
            labirinto->mapa[novaPosicao.x][novaPosicao.y] == '.') {

            if (encontrarCaminho(labirinto, novaPosicao, caminho, monstro)) {
                empilhar(caminho, posicaoAtual, movimentos[i]);
                return 1;
            }
        }
    }

    // Se não encontrou um caminho, desmarca a posição atual
    labirinto->mapa[posicaoAtual.x][posicaoAtual.y] = '.';
    return 0;
}