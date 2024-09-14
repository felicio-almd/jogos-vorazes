#include "maze.h"

int main()
{
    int altura, largura;
    scanf("%d %d", &altura, &largura);
    char *labirinto = (char *)malloc((largura + 1) * sizeof(char));
    int **lab = (int **)malloc(altura * sizeof(int *));

    for (int i = 0; i < altura; i++)
    { // Aloca memoria para armazenar o labirinto como uma matriz de caracteres (int **)
        lab[i] = (int *)malloc((largura) * sizeof(int));
    }

    for (int i = 0; i < altura; i++)
    {
        scanf("%s", labirinto);
        for (int j = 0; j < largura; j++)
        {
            if (labirinto[j] == '#')
            {
                lab[i][j] = 3;
            }
            else if (labirinto[j] == 'M')
            {
                lab[i][j] = 2;
            }
            else if (labirinto[j] == 'A')
            {
                lab[i][j] = 1;
            }
            else
            {
                lab[i][j] = 0;
            }
        }
    }
    fila *posicaoTributo = achaposicao(altura, largura, lab, 1);
    if (posicaoTributo->posi[0] == 0 || posicaoTributo->posi[1] == largura - 1 || posicaoTributo->posi[0] == altura - 1 || posicaoTributo->posi[1] == 0)
    {
        printf("YES\n");
        printf("%d", 0);
        return 0;
    }
    fila *posicaoMonstros = achaposicao(altura, largura, lab, 2);
    sairLab(altura, largura, lab, posicaoTributo, posicaoMonstros);
    printf("\n");
    return 0;
}