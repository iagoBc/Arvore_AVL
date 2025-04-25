#include "avl.h"

int main(){ 
    struct arvore* T = (struct arvore*)malloc (sizeof (struct arvore));
    T->raiz = NULL;
    char operacao;
    int chave;

    // Lê as operações e as chaves do arquivo
    while (scanf("%c %d", &operacao, &chave) != EOF) {
        if (operacao == 'i') {
            T->raiz = incluir(T->raiz, chave);  // Incluir chave na árvore AVL
        } 
        
        else if (operacao == 'r') {
            T->raiz = excluir(T->raiz, chave);  // Excluir o nó da árvore AVL
        }
    }

    printree(T->raiz, 0); // Imprime em ordem as chaves e seus níveis  
    return 0;
}
