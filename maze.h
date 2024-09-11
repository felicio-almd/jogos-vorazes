#ifndef __MAZE_H__
#define __MAZE_H__

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#define TAMANHO_MAX 1000

typedef struct
{
    int x, y;
} Posicao;

typedef struct monstros
{
    Posicao posicao;
} Monstro;

typedef struct
{
    char mapa[TAMANHO_MAX][TAMANHO_MAX];
    int altura, largura;
    Posicao posicaoInicial;
    Monstro monstros[TAMANHO_MAX];
    int numMonstros;
} Labirinto;

typedef struct
{
    Posicao *pilha;
    int topo;
    int tamanho_maximo;
    char *movimentos;
} Pilha;

// Nova estrutura para a fila
typedef struct
{
    Posicao *items;
    int front;
    int rear;
    int size;
} Queue;

// Funções existentes
void carregarLabirinto(Labirinto *labirinto, int linhas, int colunas);
void carregaLabirintoAleatorio(Labirinto *labirinto);
void imprimeLabirinto(Labirinto *labirinto);

void inicializarPilha(Pilha *pilha, int tamanho_maximo);
int pilhaVazia(Pilha *pilha);
void empilhar(Pilha *pilha, Posicao pos, char movimento);
void imprimirPilha(Pilha *pilha);
void desalocarPilha(Pilha *pilha);
Posicao desempilhar(Pilha *pilha);

// Novas funções para a fila
void initializeQueue(Queue *q, int maxSize);
int isQueueEmpty(Queue *q);
void enqueue(Queue *q, Posicao value);
Posicao dequeue(Queue *q);

// Nova função para encontrar o menor caminho
int encontrarMenorCaminho(Labirinto *labirinto, Posicao posicaoInicial, Pilha *caminho);

// Função modificada para resolver o labirinto
void resolverLabirinto(Labirinto *labirinto);

#endif