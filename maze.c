#include <maze.h>

// Iniciando o labirinto
void carregarLabirinto(Labirinto *labirinto, int linhas, int colunas)
{
    // armazena a altura e largura como quantidade de linhas e colunas
    labirinto->altura = linhas;
    labirinto->largura = colunas;
    int i, j;

    // le cada caractere
    for (i = 0; i < labirinto->altura; i++)
    {
        for (j = 0; j < labirinto->largura; j++)
        {
            scanf(" %c", &labirinto->mapa[i][j]);
            if (labirinto->mapa[i][j] == 'A')
            {
                labirinto->posicaoInicial.x = i;
                labirinto->posicaoInicial.y = j;
            }
            // FALTA FAZER
            // verificar sem tem A no labirinto
            // verificar sem tem 2 A no labirinto
            // verificar se o tamanho eh ideal  1 ≤ n, m ≤ 1000.
            // verificar se nao tem caraceteres errado
            //
        }
    }
}

// Função da busca do caminho
// ou tem caminho
int caminhoPossivel(Labirinto *labirinto, char *caminho, int *tamanhoCaminho)
{
    // Implemente a lógica para verificar se o caminho é possível
    // Retorne 1 se o caminho for possível, 0 caso contrário
    return 1;
}

// Função que imprime a saída desejada
void imprimirSolucao(int tamanhoCaminho, char *caminho)
{
    if (tamanhoCaminho > 0)
    {
        printf("YES\n%d\n%s\n", tamanhoCaminho, caminho);
    }
    else
    {
        printf("NO\n");
    }
}