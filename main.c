#include "maze.h"

int main()
{
    int n, m;
    Labirinto labirinto;

    printf("Digite a largura do labirinto: ");
    scanf("%d", &m);
    printf("Digite a altura do labirinto: ");
    scanf("%d", &n);
    carregarLabirinto(&labirinto, n, m);
    printf("\n");
    imprimeLabirinto(&labirinto);

    // ver se nao tem que alocar melhor o tamanho

    // conferir a caminhada, como vai ser feita
    // if (existeSaida(&labirinto))
    // {
    //     printf("Tem uma saida no labirinto.\n");
    // }
    // else
    // {
    //     printf("Nao tem saida no labirinto.\n");
    // }

    return 0;
}