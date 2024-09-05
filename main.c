#include "maze.h"

int main()
{
    Labirinto labirinto;
    Pilha caminho;
    inicializarPilha(&caminho, 1000); // Ajuste o tamanho máximo conforme necessário

    carregarLabirinto(&labirinto, 5, 5); // Ajuste as dimensões conforme necessário
    imprimeLabirinto(&labirinto);

    printf("Buscando caminho...\n");
    if (encontrarCaminho(&labirinto, labirinto.posicaoInicial, &caminho))
    {
        printf("Caminho encontrado:\n");
        imprimirPilha(&caminho);
    }
    else
    {
        printf("Nenhum caminho encontrado.\n");
    }

    desalocarPilha(&caminho);
    return 0;
}