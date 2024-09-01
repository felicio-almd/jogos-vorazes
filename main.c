#include "maze.h"

int main()
{
    int n, m;
    Labirinto labirinto;

    scanf("%d %d", &n, &m);
    carregarLabirinto(&labirinto, n, m);

    // ver se nao tem que alocar melhor o tamanho
    char caminho[TAMANHO_MAX * TAMANHO_MAX];
    int tamanhoCaminho = 0;

    // conferir a caminhada, como vai ser feita
    if (caminhoPossivel(&labirinto, caminho, &tamanhoCaminho))
    {
        if (simularMovimento())
            imprimirSolucao(tamanhoCaminho, caminho);
        else
            imprimirSolucao(0, caminho);
    }
    else
        imprimirSolucao(0, caminho);

    return 0;
}