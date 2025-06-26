#include <stdio.h>
#include <stdlib.h>
#include "auxiliar.h"
#include "menu.h"

int main()
{
    FILE *arquivo = fopen("massaDados.csv", "r");
    if (arquivo == NULL)
    {
        printf("\nErro ao abrir o arquivo\n\n");
        exit(1);
    }
    fclose(arquivo);

    FILE *criando = fopen("funcionarios_ordenados.csv", "r");
    if (criando == NULL)
    {
        printf("Aquivo nao existe\n");
        printf("\nEstamos criando o vetor ordenado!\n\n");
        alimenta_arvore(CRIANDO_ARVORE, "massaDados.csv");
        getchar();
    }
    else
    {
        fclose(criando);
    }

    iniciar_menu();

    return 0;
}