#include "maze.h"

int main()
{
    int altura, largura;
    scanf("%d %d", &altura, &largura);

    // Check input dimensions
    if (altura < 1 || altura > 1000 || largura < 1 || largura > 1000)
    {
        printf("Invalid dimensions. Must be between 1 and 1000.\n");
        return 1;
    }

    char *labirinto = (char *)malloc((largura + 1) * sizeof(char));
    if (labirinto == NULL)
    {
        printf("Memory allocation failed.\n");
        return 1;
    }

    int **lab = (int **)malloc(altura * sizeof(int *));
    if (lab == NULL)
    {
        printf("Memory allocation failed.\n");
        free(labirinto);
        return 1;
    }

    for (int i = 0; i < altura; i++)
    {
        lab[i] = (int *)malloc(largura * sizeof(int));
        if (lab[i] == NULL)
        {
            printf("Memory allocation failed.\n");
            for (int j = 0; j < i; j++)
            {
                free(lab[j]);
            }
            free(lab);
            free(labirinto);
            return 1;
        }
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
    if (posicaoTributo == NULL)
    {
        printf("NO\n");
        // Free allocated memory
        for (int i = 0; i < altura; i++)
        {
            free(lab[i]);
        }
        free(lab);
        free(labirinto);
        return 0;
    }

    if (posicaoTributo->posi[0] == 0 || posicaoTributo->posi[1] == largura - 1 || posicaoTributo->posi[0] == altura - 1 || posicaoTributo->posi[1] == 0)
    {
        printf("YES\n");
        printf("0\n");
        // Free allocated memory
        for (int i = 0; i < altura; i++)
        {
            free(lab[i]);
        }
        free(lab);
        free(labirinto);
        free(posicaoTributo);
        return 0;
    }

    fila *posicaoMonstros = achaposicao(altura, largura, lab, 2);
    sairLab(altura, largura, lab, posicaoTributo, posicaoMonstros);

    // Free allocated memory
    for (int i = 0; i < altura; i++)
    {
        free(lab[i]);
    }
    free(lab);
    free(labirinto);
    // Note: posicaoTributo and posicaoMonstros are freed in sairLab function

    return 0;
}