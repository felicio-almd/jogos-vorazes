#include "maze.h"

int main()
{
    int altura, largura;
    scanf("%d %d", &altura, &largura);

    if (altura < 1 || altura > 1000 || largura < 1 || largura > 1000)
    {
        printf("Dimensões Inválidas, digite um tamanho entre 1 e 1000.\n");
        return 1;
    }

    char *labirinto = (char *)malloc((largura + 1) * sizeof(char));
    if (labirinto == NULL)
    {
        printf("Erro de alocação de memoria.\n");
        return 1;
    }

    int **labirintoComNumeros = (int **)malloc(altura * sizeof(int *));
    if (labirintoComNumeros == NULL)
    {
        printf("Erro de alocação de memoria.\n");
        free(labirinto);
        return 1;
    }

    for (int i = 0; i < altura; i++)
    {
        labirintoComNumeros[i] = (int *)malloc(largura * sizeof(int));
        if (labirintoComNumeros[i] == NULL)
        {
            printf("Erro de alocação de memoria.\n");
            for (int j = 0; j < i; j++)
            {
                free(labirintoComNumeros[j]);
            }
            free(labirintoComNumeros);
            free(labirinto);
            return 1;
        }
    }

    // le o labirinto e transforma os caracteres em numeros para que fique mais facil
    // trabalhar pois números são mais fáceis e rápidos de comparar e manipular.
    for (int i = 0; i < altura; i++)
    {
        scanf("%s", labirinto);
        for (int j = 0; j < largura; j++)
        {
            if (labirinto[j] == '#')
            {
                labirintoComNumeros[i][j] = 3;
            }
            else if (labirinto[j] == 'M')
            {
                labirintoComNumeros[i][j] = 2;
            }
            else if (labirinto[j] == 'A')
            {
                labirintoComNumeros[i][j] = 1;
            }
            else
            {
                labirintoComNumeros[i][j] = 0;
            }
        }
    }

    // Encontra as posições dos tributos no labirinto
    Fila *posicaoTributo = acharPosicao(altura, largura, labirintoComNumeros, 1);
    if (posicaoTributo == NULL)
    {
        printf("NO\n");
        for (int i = 0; i < altura; i++)
        {
            free(labirintoComNumeros[i]);
        }
        free(labirintoComNumeros);
        free(labirinto);
        return 0;
    }

    // caso ja se inicie na borda, encerra o programa sem passos dados
    if (posicaoTributo->posicaoNoLabirinto[0] == 0 || posicaoTributo->posicaoNoLabirinto[1] == largura - 1 || posicaoTributo->posicaoNoLabirinto[0] == altura - 1 || posicaoTributo->posicaoNoLabirinto[1] == 0)
    {
        printf("YES\n");
        printf("0\n");
        for (int i = 0; i < altura; i++)
        {
            free(labirintoComNumeros[i]);
        }
        free(labirintoComNumeros);
        free(labirinto);
        free(posicaoTributo);
        return 0;
    }

    // Encontra as posições dos bestantes no labirinto
    Fila *posicaoBestantes = acharPosicao(altura, largura, labirintoComNumeros, 2);
    escaparLabirinto(altura, largura, labirintoComNumeros, posicaoTributo, posicaoBestantes);

    // libera a memoria
    for (int i = 0; i < altura; i++)
    {
        free(labirintoComNumeros[i]);
    }
    free(labirintoComNumeros);
    free(labirinto);

    return 0;
}