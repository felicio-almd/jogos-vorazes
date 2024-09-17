#include "maze.h"

// FUNCAO MAIN PRONTA
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

    Fila *posicaoTributo = acharPosicaoAtual(1, altura, largura, labirintoComNumeros);
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

    Fila *posicaoBestantes = acharPosicaoAtual(2, altura, largura, labirintoComNumeros);

    Fila *novaFilaBestantes = NULL;
    NoPilha *caminho = (NoPilha *)calloc(1, sizeof(NoPilha));
    if (caminho == NULL)
    {
        printf("Erro de alocacao de memoria.\n");
        exit(1);
    }
    if (encontrarSaida(labirintoComNumeros, altura, largura, posicaoTributo->posicaoNoLabirinto[0], posicaoTributo->posicaoNoLabirinto[1], caminho, posicaoBestantes, &novaFilaBestantes))
    {
        printf("YES\n");
        imprimeCaminho(caminho);
    }
    else
    {
        printf("NO\n");
    }

    for (int i = 0; i < altura; i++)
    {
        free(labirintoComNumeros[i]);
    }
    free(labirintoComNumeros);
    free(labirinto);

    return 0;
}