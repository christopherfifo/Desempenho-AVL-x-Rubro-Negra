typedef struct NO *arvoreLLRB;

arvoreLLRB *cria_arvoreLLRB();

int vazia_arvoreLLRB(arvoreLLRB *raiz);

int altura_arvoreLLRB(arvoreLLRB *raiz);

int insere_arvoreLLRB(arvoreLLRB *raiz, int valor);

int totalNO_arvoreLLRB(arvoreLLRB *raiz);

void preOrdem_arvoreLLRB(arvoreLLRB *raiz);

void emOrdem_arvoreLLRB(arvoreLLRB *raiz);

void posOderm_arvoreLLRB(arvoreLLRB *raiz);

int remove_arvoreLLRB(arvoreLLRB *raiz, int valor);

int consulta_arvoreLLRB(arvoreLLRB *raiz, int valor);

void liberar_arvoreLLRB(arvoreLLRB *raiz);

struct NO *insereNO(struct NO *H, int valor, int *resp);

struct NO *removeNO(struct NO *H, int valor);

struct NO *procuraMenor(struct NO *H);

struct NO *removeMenor(struct NO *H);