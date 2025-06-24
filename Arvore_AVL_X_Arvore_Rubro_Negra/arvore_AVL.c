#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "auxiliar.h"
#include "arvore_AVL.h"

typedef struct NO{
    int info;
    int alt; // FB - altura da sub-arvore
    struct NO *esq;
    struct NO *dir;
};

arvAVL *cria_arvAVL(){
    arvAVL *raiz = (arvAVL*) malloc(sizeof(arvAVL));
    if (raiz != NULL){
        *raiz = NULL;
    }
    return raiz;
}

int vazia_arvAVL(arvAVL *raiz){
    if(raiz == NULL){
        return 1;
    }
    if(*raiz == NULL){
        return 1;
    }
    return 0;
}

int altura_arvAVL(arvAVL *raiz){
    if(raiz == NULL){
        return 0;
    }
    if(*raiz == NULL){
        return 0;
    }
    int alt_esq = altura_arvAVL(&((*raiz)->esq));
    int alt_dir = altura_arvAVL(&((*raiz)->dir));
    if(alt_esq > alt_dir){
        return(alt_esq + 1);
    }else{
        return(alt_dir + 1);
    }
}

int insere_arvAVL(arvAVL *raiz, int valor){
    int res;

    if(*raiz == NULL){
        struct NO *novo = (struct NO*) malloc(sizeof(struct NO));
        if(novo == NULL){
            return 0;
        }
        novo->info = valor;
        novo->alt = 0;
        novo->esq = NULL;
        novo->dir = NULL;
        *raiz = novo;
        return 1;
    }

    struct NO *atual = *raiz;
    if(valor < atual->info){
        if((res = insere_arvAVL(&(atual->esq), valor)) == 1){
            if(fatorBalanceamento_NO(atual) >= 2){
                if(valor < (*raiz)->esq->info){
                    rotacaoLL(raiz);
                }else{
                rotacaoLR(raiz);
                }
            }
        }
    } else{
        if(valor > atual->info){
            if((res = insere_arvAVL(&(atual->dir), valor)) == 1){
                if(fatorBalanceamento_NO(atual) >= 2){
                    if((*raiz)->dir->info < valor){
                        rotacaoRR(raiz);
                    }else{
                        rotacaoRL(raiz);
                    }
                }
            }
        }else{
            printf("Elemento %d já existe na arvore. Insercao duplicada!\n", valor);
            return 0;
        }
    }
    atual->alt = maior(alt_no(atual->esq), alt_no(atual->dir)) + 1;
    return res;
}

int totalNO_arvAVL(arvAVL *raiz){
    if(raiz == NULL){
        return 0;
    }
    if(*raiz == NULL){
        return 0;
    }
    int alt_esq = totalNO_arvAVL(&((*raiz)->esq));
    int alt_dir = totalNO_arvAVL(&((*raiz)->dir));
    return(alt_esq + alt_dir + 1);
}


void preOrdem_arvAVL(arvAVL *raiz){
    if(raiz == NULL){
        return;
    }
    if(*raiz != NULL){
        printf("\t%d\n", (*raiz)->info);
        preOrdem_arvAVL(&((*raiz)->esq));
        preOrdem_arvAVL(&((*raiz)->dir));
    }
}


void emOrdem_arvAVL(arvAVL *raiz){
    if(raiz == NULL){
        return;
    }
    if(*raiz != NULL){
        emOrdem_arvAVL(&((*raiz)->esq));
        printf("\t%d\n", (*raiz)->info);
        emOrdem_arvAVL(&((*raiz)->dir));
    }
}

void posOderm_arvAVL(arvAVL *raiz){
    if(raiz == NULL){
        return;
    }
    if(*raiz != NULL){
        posOderm_arvAVL(&((*raiz)->esq));
        posOderm_arvAVL(&((*raiz)->dir));
        printf("\t%d\n", (*raiz)->info);
    }
}


int remove_arvAVL(arvAVL *raiz, int valor){
    if(raiz == NULL){
        return 0;
    }

    int res;
    if(valor < (*raiz)->info){
        if((res = remove_arvAVL(&(*raiz)->esq, valor)) == 1){
            if(fatorBalanceamento_NO(*raiz) >= 2){
                if(alt_no((*raiz)->dir->esq) <= alt_no((*raiz)->dir->dir)){
                    rotacaoRR(raiz);
                }else{
                    rotacaoRL(raiz);
                }
            }
        }
    }

    if((*raiz)->info < valor){
        if((res = remove_arvAVL(&(*raiz)->dir, valor)) == 1){
            if(fatorBalanceamento_NO(*raiz) >= 2){
                if(alt_no((*raiz)->esq->dir) <= alt_no((*raiz)->esq->esq)){
                    rotacaoLL(raiz);
                }else{
                    rotacaoLR(raiz);
                }
            }
        }
    }

    if((*raiz)->info == valor){
        if(((*raiz)->esq == NULL) || (*raiz)->dir == NULL){
            struct NO *no_velho = *raiz;
            if((*raiz)->esq != NULL){
                *raiz = (*raiz)->esq;
            }else{
                *raiz = (*raiz)->dir;
            }
            free(no_velho);
        }else{
            struct NO *temp = procuramenor((*raiz)->dir);
            (*raiz)->info = temp->info;
            remove_arvAVL((*raiz)->dir, (*raiz)->info);
            if(fatorBalanceamento_NO(*raiz) >= 2){
                if(alt_no((*raiz)->esq->dir) <= alt_no((*raiz)->esq->esq)){
                    rotacaoLL(raiz);
                }else{
                    rotacaoLR(raiz);
                }
            }
        }

        if(*raiz != NULL){
            (*raiz)->alt = maior(alt_no((*raiz)->esq), alt_no((*raiz)->dir)) + 1;
        }
        return 1;
    }
    if(*raiz != NULL){
        (*raiz)->alt = maior(alt_no((*raiz)->esq), alt_no((*raiz)->dir)) + 1;
    }
    return res;
}


int consulta_arvAVL(arvAVL *raiz, int valor){
    if(raiz == NULL){
        return 0;
    }
    struct NO *atual = *raiz;
    while(atual != NULL){
        if(valor == atual->info){
            return 1;
        }
        if(valor > atual->info){
            atual = atual->dir;
        }else{
            atual = atual->esq;
        }
    }
    return 0;
}

void libera_NO(struct NO *no){
    if(no == NULL){
        return;
    }
    libera_NO(no->esq);
    libera_NO(no->dir);
    free(no);
    no = NULL;
}


void liberar_arvAVL(arvAVL *raiz){
    if(raiz == NULL){
        return;
    }
    libera_NO(*raiz);
    free(raiz);
}

//calcula a altura de um nó
int alt_no(struct NO *no){
    if(no == NULL){
        return -1;
    }
    return no->alt;
}

//devolve o maior entre dois números
int maior(int x, int y){
    if(x > y){
        return x;
    }
    return y;
}

//calcula o fator de balanceamento de um nó
int fatorBalanceamento_NO(struct NO *no){
    if(no == NULL){
        return 0;
    }
    return abs(alt_no(no->esq) - alt_no(no->dir));
}

//rotacao simples a direita
void rotacaoLL(arvAVL *A){
    struct NO *B = (*A)->esq;
    (*A)->esq = B->dir;
    B->dir = *A;
    (*A)->alt = maior(alt_no((*A)->esq), alt_no((*A)->dir)) + 1;
    B->alt = maior(alt_no(B->esq), (*A)->alt) + 1;
     *A = B;
}

//rotacao simples a esquerda
void rotacaoRR(arvAVL *A){
    struct NO *B = (*A)->dir;
    (*A)->dir = B->esq;
    B->esq = (*A);
    (*A)->alt = maior(alt_no((*A)->esq), alt_no((*A)->dir)) + 1;
    B->alt = maior(alt_no(B->dir), (*A)->alt) + 1;
     (*A) = B;
}

//rotacao dupla a esquerda
void rotacaoLR(arvAVL *A){
    rotacaoRR(&(*A)->esq);
    rotacaoLL(A);
}

//rotacao dupla a direita
void rotacaoRL(arvAVL *A){
    rotacaoLL(&(*A)->dir);
    rotacaoRR(A);
}

struct NO *procuramenor(struct NO *atual){
    struct NO *no1 = atual;
    struct NO *no2 = atual->esq;
    while(no2 != NULL){
        no1 = no2;
        no2 = no2->esq;
    }
    return no1;
}

