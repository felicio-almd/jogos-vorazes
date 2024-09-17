#ifndef MAZE_H
#define MAZE_H

#include <stdio.h>
#include <stdlib.h>

// Estruturas
typedef struct no
{
    int coordenadasCaminho[2], tamanho;
    char direcao;
    struct no *prox;
    struct no *ant;
} NoPilha;

typedef struct fila
{
    int posicaoNoLabirinto[2];
    struct fila *prox;
} Fila;

// Funções para manipulação de nós
NoPilha *criaNo();
void empilha(NoPilha *Caminho, int posicao[2], char comando);
void desempilha(NoPilha *caminho);
void imprimeCaminho(NoPilha *caminho);

// Funções para manipulação de filas
Fila *removeFila(Fila *fila);
Fila *enfileira(Fila *fila, int posicao[2]);

// Funções principais do labirinto
Fila *acharPosicaoAtual(int tipoEntidade, int altura, int largura, int **labirinto);
void voltaCaminho(int altura, int largura, int **labirinto, int posicaoInicial[2], int posicaoFinal[2], NoPilha *caminho);
int moverBestantes(int **labirinto, int altura, int largura, Fila *bestantes, Fila **novaFila);
int encontrarSaida(int **labirinto, int altura, int largura, int x, int y, NoPilha *caminho, Fila *bestantes, Fila **novaFila);

#endif // MAZE_H