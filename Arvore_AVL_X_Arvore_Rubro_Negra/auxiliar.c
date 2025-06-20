#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <auxiliar.h>
#include <arvore_AVL.h>
#include <arvore_Rubro_Negra.h>

struct funcionario{
	int id;
	char nome[100];
	int idade;
	char dpto[100];
	float sal;
};

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

/* aqui ele vai ler o arquivo, mandar para a função token que vai mandar para a struct
 que ela vai mandar essa struct para a arvore e depois para um vetor, 
 depois dessa arvore ele vai mandar o vetor para o algoritimo de ordenação que vai ordenar o vetor
  e depois vamos mandar para a função de criar arquivo csv.
*/
int alimenta_arvore(char arvore, int ordena) {

    FILE *arquivo = fopen("massaDados.csv", "r");

    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo\n");
        return 1;
    }
    Funcionario func;

    char linha[256]; 
    fgets(linha, sizeof(linha), arquivo);

    Funcionario *vetor = NULL;
    int tamanho = 0;
   
    while (fgets(linha, sizeof(linha), arquivo) != NULL) {

		 func.id = atoi(strtok(linha, ";"));
		 strcpy(func.nome, strtok(NULL, ";"));
		 func.idade = atoi(strtok(NULL, ";"));
		 strcpy(func.dpto, strtok(NULL, ";"));
		 func.sal = atof(strtok(NULL, "\n"));;

         switch (arvore)
         {
         case 'arvore_AVL':
            if (insere_arvore_AVL(func) == 0) {
                printf("Funcionario %s inserido na arvore AVL.\n", func.nome);
            } else {
                printf("Erro ao inserir funcionario %s na arvore AVL.\n", func.nome);
            }
            break;

            case 'arvore_Rubro_Negra':
            if (insere_arvore_Rubro_Negra(func) == 0) {
                printf("Funcionario %s inserido na arvore Rubro-Negra.\n", func.nome);
            } else {
                printf("Erro ao inserir funcionario %s na arvore Rubro-Negra.\n", func.nome);
            }
         
         default:
            break;
         }

                
        vetor = realloc(vetor, (tamanho + 1) * sizeof(Funcionario));
        if (vetor == NULL) {
            printf("Erro ao alocar memória para vetor auxiliar.\n");
            fclose(arquivo);
            return 1;
        }
        vetor[tamanho] = func; 
        tamanho++;
    }

    fclose(arquivo);
    printf("Total de funcionarios no vetor: %d\n", tamanho);

    

    return 0;
}