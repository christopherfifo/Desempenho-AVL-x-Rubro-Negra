#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>
#include "auxiliar.h"


int main()
{
    FILE *arquivo = fopen("massaDados.csv", "r");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo\n");
        exit(1);
    }
    fclose(arquivo);

    FILE *criando = fopen("funcionarios_ordenados.csv", "r");
    if (criando == NULL) {
        printf("Aquivo não existe\n");
        printf("\n Estamos criando o vetor ordenado!\n");
        alimenta_arvore(CRIANDO_ARVORE, "massaDados.csv", 0);
    } else {
        printf("Arquivo já existe!\n");
        fclose(criando);
    }


    printf("Iniciando o programa...\n");
    alimenta_arvore(ARVORE_AVL, "massaDados.csv", 1);
    alimenta_arvore(ARVORE_RUBRO_NEGRA, "massaDados.csv", 1);

    exibeTempos();

    printf("Hello world!\n");
    return 0;
}
