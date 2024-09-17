#ifndef MAZE_H
#define MAZE_H

#include <stdio.h>
#include <stdlib.h>

// Estruturas

/*
    Estrutura: NoPilha
    Atributos:
        coordenadasCaminho: (Array de inteiros que armazena as coordenadas [x, y] da posição no labirinto)
        tamanho: (Inteiro que irá representar o tamanho da pilha)
        direcao: (Caractere que representa a direção tomada pelo tributo no caminho do labirinto)
        prox: (Ponteiro para o próximo nó da pilha)
        ant: (Ponteiro para o nó anterior da pilha)
    Objetivo: Armazenar as posições e direções tomadas no caminho percorrido no labirinto.
*/
typedef struct no
{
    int coordenadasCaminho[2], tamanho;
    char direcao;
    struct no *prox;
    struct no *ant;
} NoPilha;

/*
    Estrutura: Fila
    Atributos:
        posicaoNoLabirinto: (Array de inteiros que armazena as coordenadas [x, y] da posição de uma entidade no labirinto)
        prox: (Ponteiro para o próximo elemento da fila)
    Objetivo: Armazenar as posições de entidades (tributo ou bestantes) no labirinto em uma fila.
*/
typedef struct fila
{
    int posicaoNoLabirinto[2];
    struct fila *prox;
} Fila;

/*
    Função: empilha
    Parâmetros:
        Caminho: (Ponteiro para a pilha onde o novo nó será adicionado)
        posicao: (Array de inteiros representando as coordenadas [x, y] a serem armazenadas no nó)
        comando: (Caractere que representa a direção tomada para chegar à nova posição)
    Objetivo: Adiciona um novo nó na pilha com as coordenadas e a direção fornecidas.
*/
void empilha(NoPilha *Caminho, int posicao[2], char comando);

/*
    Função: desempilha
    Parâmetros:
        caminho: (Ponteiro para a pilha de onde o nó será removido)
    Objetivo: Remove o nó do topo da pilha, que significa que o caminho não será usado.
*/
void desempilha(NoPilha *caminho);

/*
    Função: imprimeCaminho
    Parâmetros:
        caminho: (Ponteiro para a pilha contendo o caminho percorrido)
    Objetivo: Imprime o caminho percorrido no labirinto, mostrando as direções tomadas.
*/
void imprimeCaminho(NoPilha *caminho);

// Funções para manipulação de filas

/*
    Função: enfileira
    Parâmetros:
        fila: (Ponteiro para a fila onde o novo elemento será adicionado)
        posicao: (Array de inteiros representando as coordenadas [x, y] a serem adicionadas)
    Objetivo: Adiciona um novo elemento à fila com as coordenadas fornecidas.
    Retorna um ponteiro para a fila atualizada.
*/
Fila *enfileira(Fila *fila, int posicao[2]);

/*
    Função: removeFila
    Parâmetros:
        fila: (Ponteiro para a fila de onde o primeiro elemento será removido)
    Objetivo: Remove o primeiro elemento da fila e retorna o ponteiro para o próximo elemento.
*/
Fila *removeFila(Fila *fila);

// Funções principais do labirinto

/*
    Função: acharPosicaoAtual
    Parâmetros:
        tipoEntidade: (Inteiro que representa o tipo da entidade no labirinto, como tributo ou bestante)
        altura: (Altura do labirinto)
        largura: (Largura do labirinto)
        labirinto: (Matriz de inteiros representando o layout do labirinto)
    Objetivo: Encontra a(s) posição(ões) da entidade no labirinto e as armazena em uma fila.
    Retorna um ponteiro para a fila de posições encontradas.
*/
Fila *acharPosicaoAtual(int tipoEntidade, int altura, int largura, int **labirinto);

/*
    Função: moverBestantesRecursivo
    Parâmetros:
        labirinto: (Matriz de inteiros representando o layout do labirinto)
        altura: (Altura do labirinto)
        largura: (Largura do labirinto)
        bestantes: (Ponteiro para a fila contendo as posições dos bestantes)
        novaFila: (Ponteiro para a fila que armazenará as novas posições dos bestantes após o movimento)
    Objetivo: Movimenta os bestantes de forma recursiva pelo labirinto.
    Retorna um valor inteiro indicando o status do movimento.
*/
int moverBestantes(int **labirinto, int altura, int largura, Fila *bestantes, Fila **novaFila);

/*
    Função: encontrarSaidaRecursiva
    Parâmetros:
        labirinto: (Matriz de inteiros representando o layout do labirinto)
        altura: (Altura do labirinto)
        largura: (Largura do labirinto)
        x: (Coordenada x atual do tributo)
        y: (Coordenada y atual do tributo)
        caminho: (Ponteiro para a pilha que armazenará o caminho percorrido)
        bestantes: (Ponteiro para a fila contendo as posições dos bestantes)
        novaFila: (Ponteiro para a fila que armazenará as novas posições dos bestantes)
    Objetivo: Realiza a busca recursiva pela saída do labirinto para o tributo, enquanto os bestantes se movimentam.
    Retorna um valor inteiro indicando o status da busca.
*/
int encontrarSaida(int **labirinto, int altura, int largura, int x, int y, NoPilha *caminho, Fila *bestantes, Fila **novaFila);

#endif // MAZE_H