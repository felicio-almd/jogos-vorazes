#ifndef MAZE_H
#define MAZE_H

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>

// Estruturas
typedef struct no
{
    char direcao;
    int coordenadasCaminho[2];
    struct no *prox;
    struct no *ant;
    int tamanho;
} NoPilha;

typedef struct fila
{
    int posicaoNoLabirinto[2];
    struct fila *prox;
} Fila;

// Funções para manipulação de nós
NoPilha *criaNo();
void empilha(NoPilha *caminho, int posicao[2], char comando);
void desempilha(NoPilha *caminho);
void imprimeCaminho(NoPilha *caminho);

// Funções para manipulação de filas
Fila *criarFilaVazia();
Fila *removerDaFila(Fila *fila);
Fila *enfileirar(Fila *fila, int posicao[2]);

// Funções principais do labirinto
Fila *acharPosicao(int altura, int largura, int **labirinto, int M_A); // mudar esse M_A
void escaparLabirinto(int altura, int largura, int **labirinto, Fila *posicaoTributo, Fila *posicaoBestante);
int distanciaEntreOsPersonagens(int x1, int y1, int x2, int y2);
bool moveBestante(int altura, int largura, int **labirinto, int *bestante, int *tributo);
bool moveTributo(int altura, int largura, int **labirinto, int *tributo, NoPilha *caminho);
#endif // MAZE_H