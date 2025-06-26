#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "auxiliar.h"

void limpar_buffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

void exibir_menu() {
    printf("\n\n====== ANALISE DE DESEMPENHO DE ARVORES ======\n");
    printf("1. Inserir em Arvore AVL (Dados Desordenados)\n");
    printf("2. Inserir em Arvore AVL (Dados Ordenados)\n");
    printf("3. Inserir em Arvore Rubro-Negra (Dados Desordenados)\n");
    printf("4. Inserir em Arvore Rubro-Negra (Dados Ordenados)\n");
    printf("5. Exibir Relatorio de Tempos de todos os testes executados\n");
    printf("0. Sair do Programa\n");
    printf("========================================================\n");
    printf("Escolha uma opcao: ");
}

int main() {
    FILE *arquivo_massa = fopen("massaDados.csv", "r");
    if (arquivo_massa == NULL) {
        printf("\nERRO FATAL: O arquivo 'massaDados.csv' nao foi encontrado!\n");
        printf("Por favor, certifique-se de que ele esta na mesma pasta do executavel.\n\n");
        exit(1);
    }
    fclose(arquivo_massa);

    FILE *arquivo_ordenado = fopen("funcionarios_ordenados.csv", "r");
    if (arquivo_ordenado == NULL) {
        printf("\nArquivo 'funcionarios_ordenados.csv' nao encontrado.\n");
        printf("Iniciando a criacao do arquivo com dados ordenados a partir de 'massaDados.csv'...\n");
        alimenta_arvore(CRIANDO_ARVORE, "massaDados.csv");
        printf("\nArquivo ordenado criado com sucesso!\n");
    } else {
        printf("Arquivo 'funcionarios_ordenados.csv' ja existe. Carregamento rapido!\n");
        fclose(arquivo_ordenado);
    }

    int opcao = -1;
    do {
        exibir_menu();
        if (scanf("%d", &opcao) != 1) {
            printf("Entrada invalida. Por favor, digite um numero.\n");
            limpar_buffer();
            opcao = -1;
            continue;
        }

        switch (opcao) {
            case 1:
                printf("\n--- Executando: Insercao em Arvore AVL (Dados Desordenados) ---\n");
                alimenta_arvore(ARVORE_AVL, "massaDados.csv");
                break;
            case 2:
                printf("\n--- Executando: Insercao em Arvore AVL (Dados Ordenados) ---\n");
                alimenta_arvore(ARVORE_AVL, "funcionarios_ordenados.csv");
                break;
            case 3:
                printf("\n--- Executando: Insercao em Arvore Rubro-Negra (Dados Desordenados) ---\n");
                alimenta_arvore(ARVORE_RUBRO_NEGRA, "massaDados.csv");
                break;
            case 4:
                printf("\n--- Executando: Insercao em Arvore Rubro-Negra (Dados Ordenados) ---\n");
                alimenta_arvore(ARVORE_RUBRO_NEGRA, "funcionarios_ordenados.csv");
                break;
            case 5:
                exibeTempos();
                break;
            case 0:
                printf("\nSaindo...!\n");
                break;
            default:
                printf("\nOpcao invalida! Escolha uma opcao entre 0 e 5.\n");
                break;
        }

    } while (opcao != 0);

    return 0;
}