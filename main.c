#include "maze.h"

int main()
{
    Labirinto labirinto;
    Monstro monstro;
    Pilha caminho;
    inicializarPilha(&caminho, 1000); // Ajuste o tamanho máximo conforme necessário

    carregarLabirinto(&labirinto, 5, 5); // Ajuste as dimensões conforme necessário
    imprimeLabirinto(&labirinto);

    inicializarMonstro(&labirinto, &monstro);


    printf("Buscando caminho...\n");
    if (encontrarCaminho(&labirinto, labirinto.posicaoInicial, &caminho, &monstro)) {
        printf("Caminho encontrado!\n");
        imprimirPilha(&caminho);
    } else {
        printf("Não foi possível encontrar um caminho.\n");
    }

    desalocarPilha(&caminho);
    return 0;
}