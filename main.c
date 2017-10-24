#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#define Tam 7

//=========================================Variaveis Globais===========================================//
int cont;
int numeroVertices = Tam;
int estimativa[Tam];
int fechado[Tam];
int precedente[Tam];
int peso = 0;
int menor = INT_MAX;
int atual = 0;
int destino = 0;

//======================================== Assinatura das Funçoes =====================================//
int **lerArquivo();
void relaxamento(int atual, int destino, int peso);
int menorPeso(int estimativa[]);
void recebeRotas(int *rotas);
void djikstra();
void imprime(int *rotas);

//======================================== Funçao Principal ===========================================//
int main()
{
    djikstra();
    return 0;
}

int **lerArquivo()
{
    int **matriz = (int**)malloc(Tam * sizeof(int*));
    for (int i = 0; i < Tam; i++)
    {
           matriz[i] = (int*) malloc(Tam * sizeof(int));
           for (int j = 0; j < Tam; j++)
           {
                matriz[i][j] = 0;
           }
    }

    char arquivo[]="Entrada.txt";
    FILE *arq;

    arq = fopen(arquivo, "r");
    if(arq == NULL)
    {
        printf("Erro, nao foi possivel abrir o arquivo\n");
   }
    else
    {
        while(!feof(arq))
        {
            for(int i = 0; i < Tam; i++)
                for(int j = 0; j < Tam; j++)
                    fscanf(arq, "%d", &matriz[i][j]);
        }
    }
/*
    for(int i = 0; i < Tam; i++)
    {
        for(int j = 0; j < Tam; j++)
            printf("%d\t",matriz[i][j]);
        printf("\n");
    }
    getchar();
*/

    fclose(arq);
    return matriz;
}
void relaxamento(int atual, int destino, int peso)
{
    if (estimativa[atual] + peso < estimativa[destino])
    {
        estimativa[destino] = estimativa[atual] + peso;
        precedente[destino] = atual;
    }
}

int menorPeso(int estimativa[])
{
    int i;
    menor = INT_MAX;
    int indice = 0;
    for (i = 0; i < numeroVertices; i++)
    {
        if ((menor > estimativa[i]) && (fechado[i] != 0))
        {
            menor = estimativa[i];
            indice = i;
        }
    }
    fechado[indice] = 0;
    return indice;
}

void recebeRotas(int *rotas)
{
    int linha = numeroVertices - 1;

    while (linha > 0)
    {
        linha = precedente[linha];
        rotas[cont] = linha;
        cont ++;
    }
}

void djikstra()
{
    int *rotas = (int *) malloc(Tam * sizeof (int));

//    int *recebendoRotas = (int *) malloc(Tam * sizeof (int));

    int **matriz = lerArquivo();

    for (int i = 0; i < numeroVertices; ++i)
    {
        estimativa[i] = INT_MAX;
        fechado[i] = -1;
        precedente[i] = -1;
    }

    estimativa[0] = 0;
    fechado[0] = 0;

    while (atual < numeroVertices)
    {
        for (destino = 0; destino <
             numeroVertices; destino++)
        {
            if ((matriz[atual][destino] != INT_MAX)
                    && (fechado[destino] != 0))
            {
                peso = matriz[atual][destino];
                relaxamento(atual, destino, peso);
            }
        }
        atual = menorPeso(estimativa);
        if (atual == numeroVertices - 1)
        {
            break;
        }
    }

    recebeRotas(rotas);
    imprime(rotas);
}

void imprime(int *rotas)
{
    for ( int i = 0; i < cont; i++ )
    {
        printf("A melhor rota e: %d\n", rotas[i]);
    }
}

