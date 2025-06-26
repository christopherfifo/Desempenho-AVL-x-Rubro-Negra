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

void criar_csv_ordenado( const char *nome_arquivo_saida, Funcionario* vetor, int tamanho){
    FILE *arquivo = fopen(nome_arquivo_saida, "w");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo\n");
        exit(1);
    }

    fprintf(arquivo, "Id;Nome;Idade;Empresa;Departamento;Salario\n");

    for (int i = 0; i < tamanho; i++) {
        fprintf(arquivo, "%d;%s;%d;%s;%s;%.2f\n", vetor[i].id, vetor[i].nome, vetor[i].idade, vetor[i].empresa, vetor[i].dpto, vetor[i].sal);
    }

    fclose(arquivo);
    printf("Arquivo '%s' criado com sucesso!\n", nome_arquivo_saida);
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
            troca(&arr[i], &arr[j]);
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

int alimenta_arvore(int arvore, char *nome_arquivo) {

    FILE *arquivo = fopen(nome_arquivo, "r");

    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo\n");
        return 1;
    }

    Funcionario func;

    char linha[256];
    fgets(linha, sizeof(linha), arquivo);

    Funcionario *vetor = NULL;

    int tamanho = 0;
    int capacidade = 1000;


         switch (arvore)
         {
         case ARVORE_AVL: {               

                arvAVL *raiz = cria_arvAVL();

                gettimeofday(&inicio, NULL);
                while (fgets(linha, sizeof(linha), arquivo) != NULL) {

                    func.id = atoi(strtok(linha, ";"));
                    strcpy(func.nome, strtok(NULL, ";"));
                    func.idade = atoi(strtok(NULL, ";"));
                    strcpy(func.empresa, strtok(NULL, ";"));
                    strcpy(func.dpto, strtok(NULL, ";"));
                    func.sal = atof(strtok(NULL, "\n"));

                    if (insere_arvAVL(raiz, func) == 0) {
                        printf("Erro ao inserir funcionario %s na arvore AVL.\n", func.nome);
                    }

                }

                    gettimeofday(&fim, NULL);
                    double tempo = calculaTempo(inicio, fim);
                    printf("Tempo gasto para inserir na arvore AVL: %.6f segundos\n", tempo);

                    if(strcmp(nome_arquivo, "funcionarios_ordenados.csv") == 0) {
                        TempoAVL[1] = tempo;
                        contadorAVL = 2;
                    } else {
                        TempoAVL[0] = tempo;
                        contadorAVL = (contadorAVL < 1) ? 1 : contadorAVL;
                    }
                    
                    liberar_arvAVL(raiz);
         }

            break;

            case ARVORE_RUBRO_NEGRA: {

                arvoreLLRB *raiz = cria_arvoreLLRB();

                gettimeofday(&inicio, NULL);
                while (fgets(linha, sizeof(linha), arquivo) != NULL) {

                    func.id = atoi(strtok(linha, ";"));
                    strcpy(func.nome, strtok(NULL, ";"));
                    func.idade = atoi(strtok(NULL, ";"));
                    strcpy(func.empresa, strtok(NULL, ";"));
                    strcpy(func.dpto, strtok(NULL, ";"));
                    func.sal = atof(strtok(NULL, "\n"));

                    if (insere_arvoreLLRB(raiz, func) == 0) {
                        printf("Erro ao inserir funcionario %s na arvore Rubro-Negra.\n", func.nome);
                    }

                }

                    gettimeofday(&fim, NULL);
                    double tempo = calculaTempo(inicio, fim);
                    printf("Tempo gasto para inserir na arvore Rubro Negra: %.6f segundos\n", tempo);

                    if(strcmp(nome_arquivo, "funcionarios_ordenados.csv") == 0) {
                        TempoRubroNegra[1] = tempo;
                        contadorRubroNegra = 2;
                    } else {
                        TempoRubroNegra[0] = tempo;
                        contadorRubroNegra = (contadorRubroNegra < 1) ? 1 : contadorRubroNegra;
                    }
                
                    liberar_arvoreLLRB(raiz);
            }
            break;

            case CRIANDO_ARVORE:

                vetor = malloc(capacidade * sizeof(Funcionario));
                if (vetor == NULL) {
                    printf("Erro ao alocar memória inicial para o vetor.\n");
                    fclose(arquivo);
                    return 1;
                }

                while (fgets(linha, sizeof(linha), arquivo) != NULL) {

                    func.id = atoi(strtok(linha, ";"));
                    strcpy(func.nome, strtok(NULL, ";"));
                    func.idade = atoi(strtok(NULL, ";"));
                    strcpy(func.empresa, strtok(NULL, ";"));
                    strcpy(func.dpto, strtok(NULL, ";"));
                    func.sal = atof(strtok(NULL, "\n"));

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
                }

                quickSort(vetor, 0, tamanho - 1);
                criar_csv_ordenado("funcionarios_ordenados.csv", vetor, tamanho);
                free(vetor);

            break;

         default:
            break;
         }

    fclose(arquivo);

    return 0;
}

void exibeTempos() {

    printf("\n\n======= RESULTADOS DOS TEMPOS =======\n\n");
    
    if (contadorAVL > 0) {
        printf("Tempos para Arvore AVL:\n");
        for (int i = 0; i < contadorAVL; i++) {
            (i == 0) ? printf("Tempo %d (arquivo desordenado): %.6f segundos\n", i + 1, TempoAVL[i]) : printf("Tempo %d (arquivo ordenado): %.6f segundos\n", i + 1, TempoAVL[i]);
        }
    } else {
        printf("Nenhum tempo foi registrado para a Arvore AVL.\n");
    }

    if (contadorRubroNegra > 0) {
        printf("\nTempos para Arvore Rubro-Negra:\n");
        for (int i = 0; i < contadorRubroNegra; i++) {
            (i == 0) ? printf("Tempo %d (arquivo desordenado): %.6f segundos\n", i + 1, TempoRubroNegra[i]) : printf("Tempo %d (arquivo ordenado): %.6f segundos\n", i + 1, TempoRubroNegra[i]);
        }
    } else {
        printf("Nenhum tempo foi registrado para a Arvore Rubro-Negra.\n");
    }
    
    printf("\n=====================================\n");
}
