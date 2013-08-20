#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SUCESSO 1
#define FRACASSO 0
//---------------//
#define MAIOR 1
#define IGUAL 0
#define MENOR -1
//---------------//
#define DIREITA 1
#define ESQUERDA 0
#define AMBOS 2
//---------------//
#define ERRO -1
#define OK 0
#define VAZIA 1

typedef struct ABB *pABB, **ppABB;
typedef struct NoABB *pNoABB, **ppNoABB;

int criaABB(ppABB pp, int tinfo);
int destroiABB(ppABB pp);
int reiniciaABB(pABB p);

int insereABB(pABB p, void *elemento, int (*compara)(void *dado1, void *dado2));
int removeABB(pABB p, void *elemento, int (*compara)(void *dado1, void *dado2));
int buscaABB(pABB p, void *elemento, int (*compara)(void *dado1, void *dado2));

int percursoPreOrdem(pABB p, int (*exibe)(void *dado));
int percursoOrdem(pABB p, int (*exibe)(void *dado));
int percursoPosOrdem(pABB p, int (*exibe)(void *dado));

int vazia(pABB p);
