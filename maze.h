#ifndef MAZE_H
#define MAZE_H

#include <stdio.h>
#include <stdlib.h>

// Estruturas
typedef struct no
{
    char direcao;
    int coordenadasCaminho[2];
    struct no *prox;
    struct no *ant;
    int tamanho;
} No;

typedef struct fila
{
    int posicaoNoLabirinto[2];
    struct fila *prox;
} Fila;

// Funções para manipulação de nós
No *criaNo();
void empilha(No *Caminho, int posicao[2], char comando);
void desempilha(No *caminho);
void imprimeCaminho(No *caminho);

// Funções para manipulação de filas
Fila *removeFila(Fila *fila);
Fila *enfileira(Fila *fila, int posicao[2]);

// Funções principais do labirinto
Fila *acharPosicaoAtual(int altura, int largura, int **labirinto, int M_A);
void voltaCaminho(int altura, int largura, int **labirinto, int inicial[2], int final[2]);
void encontrarSaidaLabirinto(int altura, int largura, int **labirinto, Fila *posiTributo, Fila *posiMonstros);

#endif // MAZE_H