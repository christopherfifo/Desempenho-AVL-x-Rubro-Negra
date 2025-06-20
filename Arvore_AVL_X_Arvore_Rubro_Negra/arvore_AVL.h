typedef struct NO *arvAVL;

arvAVL *cria_arvAVL();

struct NO *procuramenor(struct NO *atual);

int vazia_arvAVL(arvAVL *raiz);

int altura_arvAVL(arvAVL *raiz);

int insere_arvAVL(arvAVL *raiz, int valor);

int totalNO_arvAVL(arvAVL *raiz);

void preOrdem_arvAVL(arvAVL *raiz);

void emOrdem_arvAVL(arvAVL *raiz);

void posOderm_arvAVL(arvAVL *raiz);

int remove_arvAVL(arvAVL *raiz, int valor);

int consulta_arvAVL(arvAVL *raiz, int valor);

void liberar_arvAVL(arvAVL *raiz);

int alt_no(struct NO *no); 

int maior(int x, int y);

int fatorBalanceamento_NO(struct NO *no);

void rotacaoLL(arvAVL *A);

void rotacaoRR(arvAVL *A);

void rotacaoLR(arvAVL *A);

void rotacaoRL(arvAVL *A);

