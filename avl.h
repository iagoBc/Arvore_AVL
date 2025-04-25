#ifndef AVL_H_
#define AVL_H_

#include <stdio.h>
#include <stdlib.h>


struct No{
    int chave, altura; 
    struct No *esq, *dir, *pai, *raiz;
};

struct arvore{
    struct No *raiz;
};

int maior(int a, int b);
int altura(struct No *no);
int fator(struct No *no);

struct No* criaNo (int chave);
struct No* incluir(struct No *no, int chave);
struct No* excluir(struct No *no, int chave);
struct No* balancear(struct No *raiz);

struct No* rotEsquerda(struct No *raiz, struct No* x);
struct No* rotDireita(struct No *raiz, struct No* x);
struct No* rotEsquerdaDireita(struct No *raiz, struct No *r);
struct No* rotDireitaEsquerda(struct No *raiz, struct No *r);

void printree(struct No *n, int nivel);

#endif  // AVL_H_