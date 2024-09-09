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

typedef struct
{
    char mapa[TAMANHO_MAX][TAMANHO_MAX];
    int altura, largura;
    Posicao posicaoInicial;
} Labirinto;

typedef struct
{
    Posicao *pilha;
    int topo;
    int tamanho_maximo;
    char *movimentos;
} Pilha;

typedef struct {
    Posicao posicao;
} Monstro;


void carregarLabirinto(Labirinto *labirinto, int linhas, int colunas);
void carregaLabirintoAleatorio(Labirinto *labirinto);
void imprimeLabirinto(Labirinto *labirinto);

void inicializarPilha(Pilha *pilha, int tamanho_maximo);
int pilhaVazia(Pilha *pilha);
void empilhar(Pilha *pilha, Posicao pos, char movimento);
void imprimirPilha(Pilha *pilha);
void desalocarPilha(Pilha *pilha);
Posicao desempilhar(Pilha *pilha);
// int existeSaida(Labirinto *labirinto, char direcao);
int encontrarCaminho(Labirinto *labirinto, Posicao posicaoAtual, Pilha *caminho, Monstro *monstro);


void inicializarMonstro(Labirinto *labirinto, Monstro *monstro);
void moverMonstro(Labirinto *labirinto, Monstro *monstro);

#endif