#include <sys/time.h>

typedef struct funcionario
{
	int id;
	char nome[100];
	char empresa[100];
	int idade;
	char dpto[100];
	float sal;
} Funcionario;

void quickSort(Funcionario arr[], int low, int high);

void criar_csv_ordenado(const char *nome_arquivo_saida, Funcionario *vetor, int tamanho);

double calculaTempo(struct timeval tempoInicial, struct timeval tempoFinal);

int alimenta_arvore(int arvore, char *nome_arquivo);

void exibeTempos();

typedef enum
{
	ARVORE_AVL,
	ARVORE_RUBRO_NEGRA,
	CRIANDO_ARVORE
} SELECAO;