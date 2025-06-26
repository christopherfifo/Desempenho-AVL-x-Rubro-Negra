#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>
#include "auxiliar.h"


int main()
{
    FILE *arquivo = fopen("massaDados.csv", "r");
    if (arquivo == NULL) {
        printf("\nErro ao abrir o arquivo\n\n");
        exit(1);
    }
    fclose(arquivo);

    FILE *criando = fopen("funcionarios_ordenados.csv", "r");
    if (criando == NULL) {
        printf("Aquivo nao existe\n");
        printf("\nEstamos criando o vetor ordenado!\n\n");
        alimenta_arvore(CRIANDO_ARVORE, "massaDados.csv", 0);
    } else {
        printf("Arquivo funcionarios_ordenados.csv ja existe!\n");
        fclose(criando);
    }


    printf("\nIniciando o programa...\n\n");
    alimenta_arvore(ARVORE_AVL, "massaDados.csv", 1);
    alimenta_arvore(ARVORE_RUBRO_NEGRA, "massaDados.csv", 1);

    exibeTempos();

    return 0;
}
