#include "avl.h"

// Retorna o maior número
int maior(int a, int b){
    if(a > b) return a;
    else return b;
}

// Retorna a altura de um nó ou -1 caso ele seja null
int altura(struct No *no){
    if(no == NULL) return -1;
    else return no->altura;
}

// Calcula e retorna o fator de balanceamento de um nó
int fator(struct No *no){
    if(no) return (altura(no->esq) - altura(no->dir));
    else return 0;
}

// Cria e retorna o ponteiro de nó
struct No* criaNo (int chave){
    struct No *n = (struct No*)malloc (sizeof (struct No)); // Uso correto de struct no
    if (n != NULL) { // Verifica se a alocação de memória foi bem-sucedida
        n->chave = chave;
        n->altura = 0;
        n->esq = NULL;
        n->dir = NULL;
        n->pai = NULL;
    }
    else printf("\nErro na alocação de memória para o nó\n");
    return n; // Retorna o ponteiro criado
}

// Rotaciona à esquerda 
struct No* rotEsquerda(struct No *raiz, struct No* x) {
    struct No *y;    
    y = x->dir; // y será o filho à direita de x 

    x->dir = y->esq; // A subárvore esquerda de y se torna a subárvore direita de x   
    if(y->esq != NULL)  y->esq->pai = x; // Se y tinha uma subárvore à esquerda, define x como o novo pai dessa subárvore

    y->pai = x->pai;

    if(x->pai == NULL) raiz = y; // Se x era a raiz, atualiza a raiz para y
    
    else if(x == x->pai->esq) x->pai->esq = y; // Se x era filho à esquerda de seu pai, atualiza o ponteiro do pai para y
    
    else x->pai->dir = y; // Caso contrário, atualiza o ponteiro do pai para y como filho à direita

    
    y->esq = x; // Define x como o filho à esquerda de y
    
    x->pai = y; // Atualiza o pai de x para y

    // Recalcula a altura de x após a rotação
    x->altura = maior(altura(x->esq), altura(x->dir)) + 1;

    // Recalcula a altura de y, já que sua subárvore mudou
    y->altura = maior(altura(y->esq), altura(y->dir)) + 1;

    // Retorna o novo nó raiz após a rotação (nó 'y')
    return y;
}

// Rotaciona à direita 
struct No* rotDireita(struct No *raiz, struct No* x) {
    struct No *y = x->esq; // y será o filho à esquerda de x
    
    x->esq = y->dir; // A subárvore direita de y se torna a subárvore esquerda de x
    if (y->dir != NULL) y->dir->pai = x; // Se y tinha uma subárvore à direita, define x como o novo pai dessa subárvore
    
    y->pai = x->pai;

    if (x->pai == NULL) raiz = y; // Se x era a raiz, atualiza a raiz para y
    
    else if (x == x->pai->dir) x->pai->dir = y; // Se x era filho à direita de seu pai, atualiza o ponteiro do pai para y
    
    else  x->pai->esq = y; // Caso contrário, atualiza o ponteiro do pai para y como filho à esquerda

    y->dir = x; // Define x como o filho à direita de y
    
    x->pai = y; // Atualiza o pai de x para y

    x->altura = maior(altura(x->esq), altura(x->dir)) + 1; // Recalcula a altura de x após a rotação

    y->altura = maior(altura(y->esq), altura(y->dir)) + 1; // Recalcula a altura de y, já que sua subárvore mudou

    return y; 
}

// Corrige casos de desbalanceamento quando a subárvore esquerda do nó está mais pesada à direita
struct No* rotEsquerdaDireita(struct No *raiz, struct No *r) {
    r->esq = rotEsquerda(raiz, r->esq); // Primeiramente, realiza uma rotação à esquerda no filho à esquerda de r
    return rotDireita(raiz, r); // Em seguida, realiza uma rotação à direita no nó r
}

// Corrige casos de desbalanceamento quando a subárvore direita do nó está mais pesada à esquerda
struct No* rotDireitaEsquerda(struct No *raiz, struct No *r) {
    r->dir = rotDireita(raiz, r->dir); // Primeiramente, realiza uma rotação à direita no filho à direita de r
    return rotEsquerda(raiz, r); // Em seguida, realiza uma rotação à esquerda no nó r
}

// Balanceia a árvore se preciso
struct No* balancear(struct No *raiz) {
    
    int fb = fator(raiz); // Calcula o fator de balanceamento do nó atual

    // Caso 1: Rotação simples à esquerda (quando a subárvore direita está desbalanceada)
    // fb < -1 indica que a subárvore direita é mais pesada (altura direita > altura esquerda)
    // Se o fator de balanceamento da subárvore direita é <= 0, significa que o desbalanceamento
    // está na direção certa para uma rotação simples (esquerda).
    if(fb < -1 && fator(raiz->dir) <= 0)
        return rotEsquerda(raiz, raiz);

    // Caso 2: Rotação simples à direita (quando a subárvore esquerda está desbalanceada)
    // fb > 1 indica que a subárvore esquerda é mais pesada (altura esquerda > altura direita)
    // Se o fator de balanceamento da subárvore esquerda é >= 0, significa que a desbalanceamento
    // está na direção certa para uma rotação simples (direita).
    if(fb > 1 && fator(raiz->esq) >= 0)
        return rotDireita(raiz, raiz);

    // Caso 3: Rotação dupla à esquerda (quando a subárvore esquerda está desbalanceada para a direita)
    // fb > 1 indica que a subárvore esquerda é mais pesada, mas o fator da subárvore esquerda é < 0,
    // indicando que a subárvore esquerda está desbalanceada para a direita, o que requer uma rotação dupla.
    if(fb > 1 && fator(raiz->esq) < 0)
        return rotEsquerdaDireita(raiz, raiz);

    // Caso 4: Rotação dupla à direita (quando a subárvore direita está desbalanceada para a esquerda)
    // fb < -1 indica que a subárvore direita é mais pesada, mas o fator da subárvore direita é > 0,
    // indicando que a subárvore direita está desbalanceada para a esquerda, o que requer uma rotação dupla.
    if(fb < -1 && fator(raiz->dir) > 0)
        return rotDireitaEsquerda(raiz, raiz);

    return raiz;  
}

// Encontra o antecessor (maior valor da subárvore esquerda)
struct No *antecessor(struct No *no){
    if (no->dir == NULL) return no;
    else return antecessor(no->dir);
}

// Excluí o nó que possuí a chave que desejamos excluir
struct No* excluir(struct No *no, int chave) {
    if(no == NULL){ // Retorna NULL se a chave não foi encontrada
        return NULL;
    } 
    
    else { // Procura o nó a ser excluído
        if(no->chave == chave) {
            if(no->esq == NULL && no->dir == NULL) { // Caso 1: O nó é uma folha
                free(no);
                return NULL; // Retorna NULL para que o pai deste nó o desconecte
            }

            else {         
                // Caso 3: O nó tem dois filhos
                if(no->esq != NULL && no->dir != NULL) {       
                    struct No *aux = antecessor(no->esq); // Encontra o antecessor (maior valor da subárvore esquerda)
                    no->chave = aux->chave; // Substitui a chave do nó atual pela chave do antecessor
                    aux->chave = chave; // Atualiza a chave do antecessor para a chave a ser excluída
                    no->esq = excluir(no->esq, chave); // Excluí o antecessor da subárvore esquerda
                    return no;
                }

                else {
                    // Caso 2: O nó tem apenas um filho (esquerda ou direita)
                    struct No *aux;
                    if(no->esq != NULL) aux = no->esq; // Se o filho está à esquerda
                    else aux = no->dir; // Se o filho está à direita
                    free(no);
                    return aux; // Retorna o filho do nó para conectar com o pai
                }
            }
        } 
        
        else { // Busca binária para encontrar o nó que possuí a chave a ser excluída
            if(chave < no->chave) no->esq = excluir(no->esq, chave); // Se a chave a ser removida é menor, continua a busca na subárvore esquerda
            
            else no->dir = excluir(no->dir, chave); // Se a chave a ser removida é maior, continua a busca na subárvore direita
        }

        // Recalcula a altura do nó após a remoção
        no->altura = maior(altura(no->esq), altura(no->dir)) + 1;

        // Verifica se o nó precisa ser balanceado após a remoção
        no = balancear(no);

        return no; // Retorna o nó (possivelmente balanceado) para manter a árvore correta
    }
}

// Incluí um nó com a chave desejada
struct No* incluir(struct No *no, int chave){
    if (no == NULL) return criaNo(chave); // Se o nó não existe, cria um

    if (chave < no->chave){ // Se a chave é menor, incluí no filho da esquerda
        no->esq = incluir(no->esq, chave);
        no->esq->pai = no;
    }

    else {
        no->dir = incluir(no->dir, chave); // Se a chave é maior, incluí no filho da direita
        no->dir->pai = no;
    }

    // Recalcula a altura de todos os nós entre a raiz e o novo nó inserido
    no->altura = maior(altura(no->esq), altura(no->dir)) + 1;

    no = balancear(no);

    return no; 
}

// Imprime a árvore em ordem
void printree(struct No *n, int nivel){
    if(n == NULL) return;
    printree(n->esq, nivel + 1);
    printf("%d,%d\n", n->chave, nivel);
    printree(n->dir, nivel + 1);
}