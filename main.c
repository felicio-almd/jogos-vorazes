#include "maze.h"

int main()
{
    Labirinto labirinto;
    int altura, largura;

    scanf("%d %d", &altura, &largura);

    carregarLabirinto(&labirinto, altura, largura);
    // printf("Labirinto gerado:\n");
    imprimeLabirinto(&labirinto);

    // printf("Buscando o menor caminho...\n");
    resolverLabirinto(&labirinto);

    return 0;
}