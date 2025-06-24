#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>
#include "auxiliar.h"
#include "arvore_AVL.h"
#include "arvore_Rubro_Negra.h"



double TempoAVL[2];
double TempoRubroNegra[2];
struct timeval inicio, fim;
int contadorAVL = 0;
int contadorRubroNegra = 0;

void criar_csv_ordenado( char nome_arquivo_saida, Funcionario* vetor, int tamanho){
    FILE *arquivo = fopen(nome_arquivo_saida, "w");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo\n");
        exit(1);
    }

    fprintf(arquivo, "p;Nome;Idade;Empresa;Departamento;Salario\n");

    for (int i = 0; i < tamanho; i++) {
        fprintf(arquivo, "%d;%s;%d;%s;%.2f\n", vetor[i].id, vetor[i].nome, vetor[i].idade, vetor[i].dpto, vetor[i].sal);
    }

    fclose(arquivo);
    printf("Arquivo '%s' criado com sucesso!\n", nome_arquivo_saida);
}


void swap(int *a, int *b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}

void troca(Funcionario *a, Funcionario *b)
{
    Funcionario temp = *a;
    *a = *b;
    *b = temp;
}

int divisao(Funcionario arr[], int low, int high)
{
    Funcionario pivot = arr[high];
    int i = (low - 1);
    for (int j = low; j < high; j++) {
        if (arr[j].id <= pivot.id) {
            i++;
            swap(&arr[i], &arr[j]);
        }
    }
    troca(&arr[i + 1], &arr[high]);
    return (i + 1);
}

void quickSort(Funcionario arr[], int low, int high)
{
    if (low < high)
    {
        int pi = divisao(arr, low, high);

        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}

double calculaTempo(struct timeval tempoInicial, struct timeval tempoFinal)
{
    double inicio = tempoInicial.tv_sec + tempoInicial.tv_usec / 1000000.0;
    double fim = tempoFinal.tv_sec + tempoFinal.tv_usec / 1000000.0;
    return fim - inicio;
}

/* aqui ele vai ler o arquivo, mandar para a função token que vai mandar para a struct
 que ela vai mandar essa struct para a arvore e depois para um vetor,
 depois dessa arvore ele vai mandar o vetor para o algoritimo de ordenação que vai ordenar o vetor
  e depois vamos mandar para a função de criar arquivo csv.
*/
int alimenta_arvore(int arvore, char *nome_arquivo, int arquivo_ordenado) {

    FILE *arquivo = fopen(nome_arquivo, "r");

    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo\n");
        fclose(arquivo);
        return 1;
    }

    int arquivo_ordenado_existe = (arvore == CRIANDO_ARVORE) ? 0 : 1;

    if (contadorAVL > 2) {
        contadorAVL = 0;
    }
    if (contadorRubroNegra > 2) {
        contadorRubroNegra = 0;
    }

    Funcionario func;

    char linha[256];
    fgets(linha, sizeof(linha), arquivo);

    Funcionario *vetor = NULL;

    int tamanho = 0;
    int capacidade = 1000;

    vetor = malloc(capacidade * sizeof(Funcionario));
    if (vetor == NULL) {
        printf("Erro ao alocar memória inicial para o vetor.\n");
        fclose(arquivo);
        return 1;
    }

    gettimeofday(&inicio, NULL);
    while (fgets(linha, sizeof(linha), arquivo) != NULL) {

		 func.id = atoi(strtok(linha, ";"));
		 strcpy(func.nome, strtok(NULL, ";"));
         strcpy(func.empresa, strtok(NULL, ";"));
		 func.idade = atoi(strtok(NULL, ";"));
		 strcpy(func.dpto, strtok(NULL, ";"));
		 func.sal = atof(strtok(NULL, "\n"));;

         switch (arvore)
         {
         case ARVORE_AVL:
                if (insere_arvore_AVL(func) == 0) {
                    printf("Funcionario %s inserido na arvore AVL.\n", func.nome);
                } else {
                    printf("Erro ao inserir funcionario %s na arvore AVL.\n", func.nome);
                }

            break;

            case ARVORE_RUBRO_NEGRA:

                if (insere_arvore_Rubro_Negra(func) == 0) {
                    printf("Funcionario %s inserido na arvore Rubro-Negra.\n", func.nome);
                } else {
                    printf("Erro ao inserir funcionario %s na arvore Rubro-Negra.\n", func.nome);
                }
            break;

            case CRIANDO_ARVORE:

                if (tamanho == capacidade) {
                    int nova_capacidade = capacidade * 2;
                    Funcionario *temp = realloc(vetor, nova_capacidade * sizeof(Funcionario));
                    if (temp == NULL) {
                        printf("Erro ao realocar memória para o vetor.\n");
                        free(vetor);
                        fclose(arquivo);
                        return 1;
                    }
                    vetor = temp;
                    capacidade = nova_capacidade;
                }

                vetor[tamanho] = func;
                tamanho++;

         default:
            break;
         }

    }

    gettimeofday(&fim, NULL);
    double tempo = calculaTempo(inicio, fim);
    printf("Tempo gasto para inserir na arvore: %.6f segundos\n", tempo);

    if (arvore == ARVORE_AVL) {
        TempoAVL[contadorAVL] = tempo;
        contadorAVL++;
    } else if (arvore == ARVORE_RUBRO_NEGRA) {
        TempoRubroNegra[contadorRubroNegra] = tempo;
        contadorRubroNegra++;
    }

    fclose(arquivo);

    if (!arquivo_ordenado_existe) {
        quickSort(vetor, 0, tamanho - 1);
        criar_csv_ordenado("funcionarios_ordenados.csv", vetor, tamanho);
        return 0;
    }

    free(vetor);

    if(arquivo_ordenado == 1){
    alimenta_arvore(arvore, "FuncionariosOrdenados.csv", 0);
    }

    return 0;
}

void exibeTempos() {
    
    printf("Tempos para Arvore AVL:\n");
    for (int i = 0; i < contadorAVL; i++) {
        (i == 0) ? printf("Tempo %d (arquivo desordenado): %.6f segundos\n", i + 1, TempoAVL[i]) : printf("Tempo %d (arquivo ordenado): %.6f segundos\n", i + 1, TempoAVL[i]);
    }

    printf("\nTempos para Arvore Rubro-Negra:\n");
    for (int i = 0; i < contadorRubroNegra; i++) {
        (i == 0) ? printf("Tempo %d (arquivo desordenado): %.6f segundos\n", i + 1, TempoRubroNegra[i]) : printf("Tempo %d (arquivo ordenado): %.6f segundos\n", i + 1, TempoRubroNegra[i]);
    }
}