#ifndef MAZE_H
#define MAZE_H

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>

// Estruturas
typedef struct No
{
    char direcao;
    int v[2];
    struct No *prox;
    struct No *ant;
    int tam;
} no;

typedef struct Fila
{
    int posi[2];
    struct Fila *prox;
} fila;

// Funções para manipulação de nós
no *criaNo();
void empilha(no *Caminho, int posicao[2], char comando);
void desempilha(no *caminho);
void imprimeCaminho(no *Caminho);
void imprimeVoltaCaminho(no *caminho);

// Funções para manipulação de filas
fila *criaFila();
fila *removeFila(fila *fila);
fila *addFila(fila *fila, int posicao[2]);

// Funções principais do labirinto
fila *achaposicao(int altura, int largura, int **labirinto, int M_A);
void voltaCaminho(int altura, int largura, int **labirinto, int inicial[2], int final[2]);
void sairLab(int altura, int largura, int **labirinto, fila *posiTributo, fila *posiMonstros);
int distancia(int x1, int y1, int x2, int y2);
bool moveBestante(int altura, int largura, int **labirinto, int *bestante, int *tributo);
bool moveTributo(int altura, int largura, int **labirinto, int *tributo, no *caminho);
#endif // MAZE_H