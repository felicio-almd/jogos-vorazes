#include "maze.h"

// Iniciando o labirinto
// FALTA FAZER
// verificar sem tem A no labirinto
// verificar sem tem 2 A no labirinto
// verificar se o tamanho eh ideal  1 ≤ n, m ≤ 1000.
// verificar se nao tem caraceteres errado
/*void carregarLabirinto(Labirinto *labirinto, int linhas, int colunas)
{
    if (linhas < 1 || linhas > TAMANHO_MAX || colunas < 1 || colunas > TAMANHO_MAX)
    {
        printf("Erro: Dimensões do labirinto são inválidas.\n");
        return;
    }
    // armazena a altura e largura como quantidade de linhas e colunas
    labirinto->altura = linhas;
    labirinto->largura = colunas;
    int i, j;
    int contadorA = 0;

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
                contadorA++;

                if (labirinto->mapa[i][j] != 'A' && labirinto->mapa[i][j] != '.' && labirinto->mapa[i][j] != '#' && labirinto->mapa[i][j] != 'M')
                {
                    printf("Erro: Caractere inválido '%c' encontrado no labirinto.\n", labirinto->mapa[i][j]);
                    return;
                }
            }
        }
        if (contadorA == 0)
        {
            printf("Erro: Nenhum ponto inicial 'A' encontrado no labirinto.\n");
        }
        else if (contadorA > 1)
        {
            printf("Erro: Mais de um ponto inicial 'A' encontrado no labirinto.\n");
        }
    }
}
*/

// Função para preencher o labirinto com caracteres aleatórios
void carregaLabirintoAleatorio(Labirinto *labirinto)
{
    int i, j;

    // Inicializa o gerador de números aleatórios
    srand(time(NULL));

    // Preenche o labirinto com caracteres aleatórios, exceto 'A'
    for (i = 0; i < labirinto->altura; i++)
    {
        for (j = 0; j < labirinto->largura; j++)
        {
            int randChar = rand() % 3; // Gera um número aleatório entre 0 e 2

            switch (randChar)
            {
            case 0:
                labirinto->mapa[i][j] = '.';
                break;
            case 1:
                labirinto->mapa[i][j] = '#';
                break;
            case 2:
                labirinto->mapa[i][j] = 'M';
                break;
            }
        }
    }

    // Garante que há exatamente um 'A' no labirinto
    int posX = rand() % labirinto->altura;
    int posY = rand() % labirinto->largura;
    labirinto->mapa[posX][posY] = 'A';
    labirinto->posicaoInicial.x = posX;
    labirinto->posicaoInicial.y = posY;
}

void carregarLabirinto(Labirinto *labirinto, int linhas, int colunas)
{
    if (linhas < 1 || linhas > TAMANHO_MAX || colunas < 1 || colunas > TAMANHO_MAX)
    {
        printf("Erro: Dimensões do labirinto são inválidas.\n");
        return;
    }

    // Armazena a altura e largura
    labirinto->altura = linhas;
    labirinto->largura = colunas;

    // Preenche o labirinto com caracteres aleatórios
    carregaLabirintoAleatorio(labirinto);

    // Valida os caracteres no labirinto
    int i, j;
    for (i = 0; i < labirinto->altura; i++)
    {
        for (j = 0; j < labirinto->largura; j++)
        {
            if (labirinto->mapa[i][j] != '.' && labirinto->mapa[i][j] != '#' && labirinto->mapa[i][j] != 'A' && labirinto->mapa[i][j] != 'M')
            {
                printf("Erro: Caractere inválido '%c' encontrado no labirinto.\n", labirinto->mapa[i][j]);
                return;
            }
        }
    }
}

void imprimeLabirinto(Labirinto *labirinto)
{
    int i, j;
    for (i = 0; i < labirinto->altura; i++)
    {
        for (j = 0; j < labirinto->largura; j++)
        {
            printf("%c", labirinto->mapa[i][j]);
        }
        printf("\n"); // Adiciona uma nova linha após cada linha do labirinto
    }
}

// Inicializa a pilha
void inicializaPilha(Pilha *p)
{
    p->topo = -1;
}

// Verifica se a pilha está vazia
int pilhaVazia(Pilha *p)
{
    return p->topo == -1;
}

// Adiciona um item à pilha
void empilha(Pilha *p, Posicao pos)
{
    if (p->topo < TAMANHO_MAX * TAMANHO_MAX - 1)
    {
        p->pilha[++p->topo] = pos;
    }
}

// Remove e retorna o item do topo da pilha
Posicao desempilha(Pilha *p)
{
    if (!pilhaVazia(p))
    {
        return p->pilha[p->topo--];
    }
    // Retorna uma posição inválida se a pilha estiver vazia
    Posicao pos = {-1, -1};
    return pos;
}

int movimento(Labirinto *labirinto)
{
}

// Função da busca do caminho (busca em profundidade)
// ou tem caminho
// void existeCaminho(Labirinto *labirinto, char *caminho, int *tamanhoCaminho)
// {
//     // Implemente a lógica para verificar se o caminho é possível
// }

// int dentroDoLabirinto(Labirinto *labirinto, int x, int y)
// {
//     return (x >= 0 && x < labirinto->altura && y >= 0 && y < labirinto->largura);
// }

// // Função DFS recursiva
// int buscaEmProfundidade(Labirinto *labirinto, int x, int y)
// {
//     if (!dentroDoLabirinto(labirinto, x, y) || labirinto->visitado[x][y] || labirinto->mapa[x][y] == '#')
//     {
//         return 0;
//     }

//     labirinto->visitado[x][y] = 1;

//     // Se encontramos uma saída (ponto final), retorna verdadeiro
//     if (labirinto->mapa[x][y] == 'A')
//     {
//         return 1;
//     }

//     // Explora as 4 direções (cima, baixo, esquerda, direita)
//     int dx[] = {-1, 1, 0, 0};
//     int dy[] = {0, 0, -1, 1};

//     for (int i = 0; i < 4; i++)
//     {
//         int novoX = x + dx[i];
//         int novoY = y + dy[i];

//         if (buscaEmProfundidade(labirinto, novoX, novoY))
//         {
//             return 1;
//         }
//     }

//     // Retorna falso se não encontrou a saída
//     return 0;
// }

// // Função para iniciar a busca e verificar se há uma saída
// int existeSaida(Labirinto *labirinto)
// {
//     // Inicializa a matriz de visitado
//     for (int i = 0; i < labirinto->altura; i++)
//     {
//         for (int j = 0; j < labirinto->largura; j++)
//         {
//             labirinto->visitado[i][j] = 0;
//         }
//     }

//     // Inicia a busca a partir da posição inicial 'A'
//     return buscaEmProfundidade(labirinto, labirinto->posicaoInicial.x, labirinto->posicaoInicial.y);
// }

// Função que imprime a saída desejada
// void imprimirSolucao(int tamanhoCaminho, char *caminho)
// {
//     if (tamanhoCaminho > 0)
//     {
//         printf("YES\n%d\n%s\n", tamanhoCaminho, caminho);
//     }
//     else
//     {
//         printf("NO\n");
//     }
// }