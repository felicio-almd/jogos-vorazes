#ifndef MAZE_H
#define MAZE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

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

typedef struct
{
    int x, y;
    int distance;
} QueueItem;

// Funções existentes
void carregarLabirinto(Labirinto *labirinto, int linhas, int colunas);
void imprimeLabirinto(Labirinto *labirinto);

void inicializarPilha(Pilha *pilha, int tamanho_maximo);
int pilhaVazia(Pilha *pilha);
void empilhar(Pilha *pilha, Posicao pos, char movimento);
Posicao desempilhar(Pilha *pilha);
void imprimirPilha(Pilha *pilha);
void desalocarPilha(Pilha *pilha);

// Novas funções para a fila
void initializeQueue(Queue *q, int maxSize);
int isQueueEmpty(Queue *q);
void enqueue(Queue *q, Posicao value);
Posicao dequeue(Queue *q);

void inicializarMonstros(Labirinto *labirinto);
int resolverLabirintoComMonstros(Labirinto *labirinto);

void resolverLabirinto(Labirinto *labirinto);

#endif