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

    FILE *criando = fopen("FuncionariosOrdenados.csv", "r");
    if (criando == NULL) {
        printf("Aquivo não existe\n");
        printf("\n Estamos criando o vetor ordenado!\n");
        alimenta_arvore(CRIANDO_ARVORE, "massaDados.csv");
    }

    printf("Hello world!\n");
    return 0;
}
