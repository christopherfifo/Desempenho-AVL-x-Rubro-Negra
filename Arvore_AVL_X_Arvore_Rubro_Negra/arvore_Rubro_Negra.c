
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "auxiliar.h"
#include "arvore_Rubro_Negra.h"

#define RED 1
#define BLACK 0

typedef struct NO{
    Funcionario dados_func;   
    struct NO *esq;
    struct NO *dir;
    int cor;
} NO;

arvoreLLRB *cria_arvoreLLRB(){
    arvoreLLRB *raiz = (arvoreLLRB*) malloc(sizeof(arvoreLLRB));
    if (raiz != NULL){
        *raiz = NULL;
    }
    return raiz;
}

int vazia_arvoreLLRB(arvoreLLRB *raiz){
    if(raiz == NULL){
        return 1;
    }
    if(*raiz == NULL){
        return 1;
    }
    return 0;
}

int altura_arvoreLLRB(arvoreLLRB *raiz){
    if(raiz == NULL){
        return 0;
    }
    if(*raiz == NULL){
        return 0;
    }
    int alt_esq = altura_arvoreLLRB(&((*raiz)->esq));
    int alt_dir = altura_arvoreLLRB(&((*raiz)->dir));
    if(alt_esq > alt_dir){
        return(alt_esq + 1);
    }else{
        return(alt_dir + 1);
    }
}

int insere_arvoreLLRB(arvoreLLRB *raiz, Funcionario valor){
    int resp;

    *raiz =  insereNO(*raiz, valor, &resp);
    if(*raiz != NULL){
        (*raiz)->cor = BLACK;
    }
    return resp;
}

int totalNO_arvoreLLRB(arvoreLLRB *raiz){
    if(raiz == NULL){
        return 0;
    }
    if(*raiz == NULL){
        return 0;
    }
    int alt_esq = totalNO_arvoreLLRB(&((*raiz)->esq));
    int alt_dir = totalNO_arvoreLLRB(&((*raiz)->dir));
    return(alt_esq + alt_dir + 1);
}


void preOrdem_arvoreLLRB(arvoreLLRB *raiz){
    if(raiz == NULL){
        return;
    }
    if(*raiz != NULL){
        printf("\t%d\n", (*raiz)->dados_func.id);
        preOrdem_arvoreLLRB(&((*raiz)->esq));
        preOrdem_arvoreLLRB(&((*raiz)->dir));
    }
}


void emOrdem_arvoreLLRB(arvoreLLRB *raiz){
    if(raiz == NULL){
        return;
    }
    if(*raiz != NULL){
        emOrdem_arvoreLLRB(&((*raiz)->esq));
        printf("\t%d\n", (*raiz)->dados_func.id);
        emOrdem_arvoreLLRB(&((*raiz)->dir));
    }
}



void posOderm_arvoreLLRB(arvoreLLRB *raiz){
    if(raiz == NULL){
        return;
    }
    if(*raiz != NULL){
        posOderm_arvoreLLRB(&((*raiz)->esq));
        posOderm_arvoreLLRB(&((*raiz)->dir));
        printf("\t%d\n", (*raiz)->dados_func.id);
    }
}


int remove_arvoreLLRB(arvoreLLRB *raiz, Funcionario valor){
    if(consulta_arvoreLLRB(raiz, valor.id)){
        struct NO *H = *raiz;

        *raiz = removeNO(H, valor.id);
        if(*raiz != NULL){
            (*raiz)->cor = BLACK;
        }

        return 1;
    } else {
        return 0;
    }
}


int consulta_arvoreLLRB(arvoreLLRB *raiz, int valor){
    if(raiz == NULL){
        return 0;
    }
    struct NO *atual = *raiz;
    while(atual != NULL){
        if(valor == atual->dados_func.id){
            return 1;
        }
        if(valor > atual->dados_func.id){
            atual = atual->dir;
        }else{
            atual = atual->esq;
        }
    }
    return 0;
}

void libera_NORU(struct NO *no){
    if(no == NULL){
        return;
    }
    libera_NORU(no->esq);
    libera_NORU(no->dir);
    free(no);
    no = NULL;
}


void liberar_arvoreLLRB(arvoreLLRB *raiz){
    if(raiz == NULL){
        return;
    }
    libera_NORU(*raiz);
    free(raiz);
}


int cor(struct NO *H){
    if(H == NULL){
        return BLACK;
    }
    return H->cor;
}

void trocaCor(struct NO *H){
    H->cor = !H->cor;
    if(H->esq != NULL){
        H->esq->cor = !H->esq->cor;
    }
    if(H->dir != NULL){
        H->dir->cor = !H->dir->cor;
    }
}

struct NO *rotacionaEsquerda(struct NO *A){
    struct NO *B = A->dir;
    A->dir = B->esq;
    B->esq = A;
    B->cor = A->cor;
    A->cor = RED;
    return B;
}

struct NO *rotacionaDireita(struct NO *A){
    struct NO *B = A->esq;
    A->esq = B->dir;
    B->dir = A;
    B->cor = A->cor;
    A->cor = RED;
    return B;
}

struct NO *move2EsqRed(struct NO *H){
    trocaCor(H);
    if(cor(H->dir->esq) == RED){
        H->dir = rotacionaDireita(H->dir);
        H = rotacionaEsquerda(H);
        trocaCor(H);
    }
    return H;
}

struct NO *move2DirRed(struct NO *H){
    trocaCor(H);
    if(cor(H->esq->esq) == RED){
        H = rotacionaDireita(H);
        trocaCor(H);
    }
    return H;
}

struct NO *balancear(struct NO *H){
    if(cor(H->dir) == RED){
        H = rotacionaEsquerda(H);
    }
    if(H->esq != NULL && cor(H->dir) == RED && cor(H->esq->esq) == RED){
        H = rotacionaDireita(H);
    }
    if(cor(H->esq) == RED && cor(H->dir) == RED){
        trocaCor(H);
    }
    return H;
}

struct NO *insereNO(struct NO *H, Funcionario valor, int *resp){
    if(H == NULL){
        struct NO *novo = (struct NO*) malloc(sizeof(struct NO));
        if(novo == NULL){
            *resp = 0; 
            return NULL;
        }
        novo->dados_func = valor;
        novo->cor = RED;
        novo->dir = NULL;
        novo->esq = NULL;
        *resp = 1;
        return novo;
    }

    if(valor.id == H->dados_func.id){
        *resp = 0;
    } else {
        if(valor.id < H->dados_func.id){
            H->esq = insereNO(H->esq, valor, resp);
        } else {
            H->dir = insereNO(H->dir, valor, resp);
        }
    }

    if(cor(H->dir) == RED && cor(H->esq) == BLACK){
        H = rotacionaEsquerda(H);
    }

    if(cor(H->esq) == RED && cor(H->esq->esq) == RED){
        H = rotacionaDireita(H);
    }

    if(cor(H->esq) == RED && cor(H->dir) == RED){
        trocaCor(H);
    }

    return H;
}

struct NO *removeNO(struct NO *H, int valor){
    if(valor < H->dados_func.id){
        if(cor(H->esq) == BLACK && cor(H->esq->esq) == BLACK){
            H = move2EsqRed(H);
        }
        H->esq = removeNO(H->esq, valor);
    } else {
        if(cor(H->esq) == RED){
            H = rotacionaDireita(H);
        }
        if(valor == H->dados_func.id && (H->dir == NULL)){
            free(H);
            return NULL;
        }
        if(cor(H->dir) == BLACK && cor(H->dir->esq) == BLACK){
            H = move2DirRed(H);
        }
        if(valor == H->dados_func.id){ 
            if (H->dir == NULL) {
                free(H);
                return NULL;
            }
            NO *x = procuraMenor(H->dir);
            H->dados_func = x->dados_func; 
            H->dir = removeMenor(H->dir);
        } else {
            H->dir = removeNO(H->dir, valor);
        }
    }
    return balancear(H);
}

struct NO *removeMenor(struct NO *H){
    if(H->esq == NULL){
        free(H);
        return NULL;
    }

    if(cor(H->esq) == BLACK && cor(H->esq->esq) == BLACK){
        H = move2EsqRed(H);
    }

    H->esq = removeMenor(H->esq);

    return balancear(H);
}

struct NO *procuraMenor(struct NO *atual){
    struct NO *no1 = atual;

    struct NO *no2 = atual->esq;
    while(no2 != NULL){
        no1 = no2;
        no2 = no2->esq;
    }

    return no1;
}
