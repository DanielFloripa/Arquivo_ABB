#include "abb_publico.h"

typedef struct NoABB {
        void *dado;
        pNoABB pai, esq, dir;
} NoABB;

typedef struct ABB {
        int tinfo;
        pNoABB raiz;
} ABB;

int nfilhos(pNoABB p, int *pos); //retorna em num o numero de filhos que o elemento possui e em pos a posição dele(esq/dir)
pNoABB sucessor(pNoABB p); //retorna o endereço do elemento sucessor de p

void reiniciaRecursivo(pNoABB temp);
pNoABB removeRecursivo(pNoABB temp, void *elemento, int (*compara)(void *dado1, void *dado2));
void PreOrdemRecursivo(pNoABB temp, int (*exibe)(void *dado));
void OrdemRecursivo(pNoABB temp, int (*exibe)(void *dado));
void PosOrdemRecursivo(pNoABB temp, int (*exibe)(void *dado));
