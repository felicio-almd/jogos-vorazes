#ifndef __MAZE_H__
#define __MAZE_H__

#include <stdlib.h>
#include <stdio.h>

#define TAMANHO_MAX 1000

/*
    Nome da Estrutura: Labirinto
    Objetivo: Representa o labirinto em 2 dimensões
    Campos:
        mapa: uma matriz bidimensional de caracteres que representa o mapa
            do labirinto. Cada celula pode conter:
            "." para chão
            "#" para parede
            "A" para posição inicial do tributo
            "M" para um bestante (monstro)
        altura: um inteiro que armazena a altura do labirinto
        largura: um inteiro que armazena a largura do labirinto
    obs: a constante TAMANHO_MAX (definida como 1000 no arquivo) determina o tamanho maximo do labirinto
*/
typedef struct labirinto
{
    char mapa[TAMANHO_MAX][TAMANHO_MAX];
    int altura;
    int largura;
    Posicao posicaoInicial;
} Labirinto;

/*
    Nome da Estrutura: Posicao
    Objetivo: Representa uma posição no labirinto
    Campos:
        x: um inteiro que a coordenada x (linha) da posição
        y: um inteiro que a coordenada y (coluna) da posição
*/
typedef struct
{
    int x;
    int y;
} Posicao;

/*
    Nome da função: carregarLabirinto
    Parametro:
        labirinto:(Ponteiro para uma estrutura labirinto da entrada)
        linhas:(inteiro com o tamanho da altura do labirinto)
        colunas:(inteiro com o tamanho da largura do labirinto)

    Objetivo: Armazenar a altura e Largura do labirinto nos campos da estrutura
              em seguida, ler o mapa do labirinto linha por linha e coloca-lo no campo mapa
*/
void carregarLabirinto(Labirinto *labirinto, int linhas, int colunas);

/*
    Nome da função: existeCaminho
    Parametro:
        labirinto:(Ponteiro para uma estrutura labirinto da entrada)
    Retorno: 1 se for possivel escapar(tem caminho), 0 se não tem caminho para escapar
    Objetivo: A partir de um algoritmo de busca, verificar se tem o caminho para o tributo
              sair do labirinto. Considera movimentos simultaneos do tributo e dos bestantes
*/
int existeCaminho(Labirinto *labirinto);

/*
    Nome da função: imprimirCaminho
    Parametro:
        labirinto:(Ponteiro para uma estrutura labirinto da entrada)
    Objetivo: Essa função deve encontrar o caminho de fuga e imprimir esse caminho válido.
*/
void imprimirCaminho(Labirinto *labirinto);

// Estrutura para a arvore (busca)
typedef struct no
{
    int chave;
    struct no *esq, *dir, *cima, *baixo;
} Tree;

#endif