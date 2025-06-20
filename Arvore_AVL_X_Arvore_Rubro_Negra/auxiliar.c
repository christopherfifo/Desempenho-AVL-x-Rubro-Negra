#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <auxiliar.h>
#include <arvore_AVL.h>
#include <arvore_Rubro_Negra.h>

typedef struct funcionario{
	int id;
	char *nome;
	int idade;
	char *dpto;
	float sal;
};


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