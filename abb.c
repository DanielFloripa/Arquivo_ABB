#include "abb_privado.h"
//#include "arquivo.h"

int criaABB( ppABB pp, int tinfo ){
    if((*pp) != NULL){
        return FRACASSO;
    }
    if(contaDados()!= 0){
        (*pp) = (pABB) malloc(sizeof (ABB) * contaDados());
        pp = (pABB*) loadTDA_ABB();
        //(*pp) = (pABB) malloc(sizeof (ABB) * contaDados());
        //(*pp) = loadTDA_ABB();
        (*pp)->tinfo = tinfo;
        (*pp)->raiz = NULL;
        printf("Carregado!\n");
        return SUCESSO;
    }
    (*pp) = (pABB) malloc(sizeof (ABB));
    if((*pp) == NULL){
        return FRACASSO;
    }
    (*pp)->tinfo = tinfo;
    (*pp)->raiz = NULL;
    return SUCESSO;

}
//------------------------------------------------------------------------------------------------//

int insereABB( pABB p, void *elemento, int (*compara)(void *dado1, void *dado2) ){
    FILE *fp;
    fp = fopen("abb.dat","ab");
    if (fp == NULL){
        printf("Problema no arquivo!\n");
        exit(1);
    }
    if(p == NULL){
        return FRACASSO;
    }
    pNoABB novo = (pNoABB) malloc(sizeof (NoABB));
    novo->dado = malloc(p->tinfo);
    memcpy(novo->dado, elemento, p->tinfo);
    novo->pai = NULL;
    novo->esq = NULL;
    novo->dir = NULL; //formato de raiz;
    fwrite(elemento,p->tinfo,1,fp);
    fclose(fp);
    if(vazia(p)){
        p->raiz = novo;
        return SUCESSO;
    }
    else{ //se nao for raiz
        pNoABB temp = p->raiz;
        int comparacao;
        while(temp != NULL && temp->dado != NULL){ //temp->dado   para garantir que a compara  o ocorrer  normalmente
            comparacao = compara(novo->dado, temp->dado);
            if(comparacao == MENOR){ //novo->dado   menor que temp->dado
                if(temp->esq != NULL){
                    temp = temp->esq;
                }
                else{ //caso n o haja elemento no lado desejado, inserir
                    novo->pai = temp;
                    temp->esq = novo;
                    return SUCESSO;
                }
            }
            else if(comparacao == MAIOR){
                if(temp->dir != NULL){
                    temp = temp->dir;
                }
                else{ //caso n o haja elemento no lado desejado, inserir
                    novo->pai = temp;
                    temp->dir = novo;
                    return SUCESSO;
                }
            }
            else{ //se comparacao==IGUAL ent o dado j  foi inserido
                free(novo->dado);
                free(novo);
                novo = NULL;
                return FRACASSO;
            }
        } //se sair do while   porque ocorreu um erro, portanto deve retornar fracasso
    }
    return FRACASSO;
}
//------------------------------------------------------------------------------------------------//

int removeABB( pABB p, void *elemento, int (*compara)(void *dado1, void *dado2) ){
    pNoABB temp = NULL, sub = NULL; //temp: endere o do elemento a ser retirado; sub: endere o do substituto (caso tenha 2 filhos)
    int num, pos; //num=numero de filhos; pos=dir/esq/ambos (em abb_publico)
    if(vazia(p)){
        return FRACASSO;
    }
    temp = removeRecursivo(p->raiz, elemento, compara); //ao final, temp ter  o endere o do elemento a ser removido
    if(temp == NULL){
        return FRACASSO;
    }
    memcpy(elemento, temp->dado, p->tinfo); //recebe um dado que tem apenas o r tulo, retorna o dado completo
    num = nfilhos(temp, &pos); //para saber quantos filhos possui o elemento a ser removido e a localiza  o do(s) mesmo(s)
    if(num == 0){ //se n o tiver filhos
        if(temp == p->raiz){
            p->raiz = NULL;
        }
        else{
            if(temp->pai->dir == temp){
                temp->pai->dir = NULL;
            }
            if(temp->pai->esq == temp){
                temp->pai->esq = NULL;
            }
        }
    }
    else if(num == 1){
        if(temp == p->raiz){
            if(pos == DIREITA){
                p->raiz = temp->dir;
            }
            if(pos == ESQUERDA){
                p->raiz = temp->esq;
            }
        }
        else{
            if(temp->pai->dir == temp){
                if(pos == DIREITA){
                    temp->pai->dir = temp->dir;
                }
                else{
                    temp->pai->dir = temp->esq;
                } //mesmo que: if (pos==ESQUERDA){
            }
            if(temp->pai->esq == temp){
                if(pos == DIREITA){
                    temp->pai->esq = temp->dir;
                }
                else{
                    temp->pai->esq = temp->esq;
                } //mesmo que: if (pos==ESQUERDA){
            }
        }
    }
    else if(num == 2){
        sub = sucessor(temp); //sucessor do elemento a ser removido
        if(sub->pai != temp){
            sub->pai->esq = sub->dir;
        } //se substituto n o for o filho a direita do elemento a ser removido
        sub->esq = temp->esq;
        if(temp->dir != sub){
            sub->dir = temp->dir;
        }
        sub->pai = temp->pai; //Passar para o substituto os elementos de temp (esq, dir, pai, etc)
        if(temp != p->raiz){
            if(temp->pai->dir == temp){
                temp->pai->dir = sub;
            }
            else{
                temp->pai->esq = sub;
            }
        }
        else{
            p->raiz = sub;
            sub->pai = NULL;
        }
        if(temp->dir != NULL){
            if(temp->dir != sub){
                temp->dir->pai = sub;
            }
        }
        if(temp->esq != NULL){
            if(temp->esq != sub){
                temp->esq->pai = sub;
            }
        }
    }
    free(temp->dado);
    free(temp);
    temp = NULL; //Ao final, remove o elemento
    return SUCESSO;
}

pNoABB removeRecursivo( pNoABB temp, void *elemento, int (*compara)(void *dado1, void *dado2) ){
    int comp = compara(elemento, temp->dado);
    if(comp == MAIOR){
        return removeRecursivo(temp->dir, elemento, compara);
    }
    if(comp == MENOR){
        return removeRecursivo(temp->esq, elemento, compara);
    }
    if(comp == IGUAL){
        return temp;
    } //se comparacao==IGUAL ent o dado existe, portanto remover
    return temp; //VERIFICAR QDO TENTAR REMOVER ELEMENTO QUE NAO EST  NA ARVORE - NAO IMPLEMENTADO!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
}
//------------------------------------------------------------------------------------------------//

int buscaABB( pABB p, void *elemento, int (*compara)(void *dado1, void *dado2) ){
    if(p == NULL){
        return FRACASSO;
    }
    if(!vazia(p)){ //se raiz n o for NULL/se  rvore n o estiver vazia
        pNoABB temp = p->raiz;
        int comparacao;
        while(temp != NULL && temp->dado != NULL){ //temp->dado   para garantir que a compara  o ocorrer  normalmente
            comparacao = compara(elemento, temp->dado);
            if(comparacao == MENOR){ //novo->dado   menor que temp->dado
                if(temp->esq != NULL){
                    temp = temp->esq;
                }
                else{
                    return FRACASSO;
                } //caso n o haja elemento no lado desejado, ent o o elemento buscado n o existe na  rvore
            }
            else if(comparacao == MAIOR){
                if(temp->dir != NULL){
                    temp = temp->dir;
                }
                else{
                    return FRACASSO;
                } //caso n o haja elemento no lado desejado, ent o o elemento buscado n o existe na  rvore
            }
            else{ //se comparacao==IGUAL ent o dado j  foi inserido, portanto existe, portanto sucesso
                memcpy(elemento, temp->dado, p->tinfo); //recebe um dado que tem apenas o r tulo, retorna o dado completo
                return SUCESSO;
            }
        } //se sair do while   porque ocorreu um erro, portanto deve retornar fracasso
    }
    return FRACASSO;
}


//------------------------------------------------------------------------------------------------//

int destroiABB( ppABB pp ){
    if(*pp == NULL){
        return FRACASSO;
    }
    if(vazia(*pp)){
        free(*pp);
    }
    else{
        if(reiniciaABB(*pp)){
            free(*pp);
        }
    }
    (*pp) = NULL;
    return SUCESSO;
}
//------------------------------------------------------------------------------------------------//

int reiniciaABB( pABB p ){ //desde esquerda, desce direita, mostra
    if(p == NULL){
        return FRACASSO;
    }
    if(vazia(p)){
        return FRACASSO;
    }
    reiniciaRecursivo(p->raiz);
    p->raiz = NULL;
    return SUCESSO;
}

void reiniciaRecursivo( pNoABB temp ){
    if(temp->esq != NULL){
        reiniciaRecursivo(temp->esq);
    }
    if(temp->dir != NULL){
        reiniciaRecursivo(temp->dir);
    }
    //se n o tiver mais como descer, ent o remover elemento
    if(temp->pai != NULL){ //mesmo que: if (temp==p->raiz){
        if(temp->pai->esq == temp){
            temp->pai->esq = NULL;
        }
        if(temp->pai->dir == temp){
            temp->pai->dir = NULL;
        }
    }
    free(temp->dado);
    free(temp);
    temp = NULL;
}
//------------------------------------------------------------------------------------------------//

int percursoPreOrdem( pABB p, int (*exibe)(void *dado) ){ //mostra, desce esquerda, desce direita
    if(p == NULL){
        return FRACASSO;
    }
    if(vazia(p)){
        return FRACASSO;
    }
    PreOrdemRecursivo(p->raiz, exibe);
    return SUCESSO;
}

void PreOrdemRecursivo( pNoABB temp, int (*exibe)(void *dado) ){
    exibe(temp->dado);
    if(temp->esq != NULL){
        PreOrdemRecursivo(temp->esq, exibe);
    }
    if(temp->dir != NULL){
        PreOrdemRecursivo(temp->dir, exibe);
    }
}
//------------------------------------------------------------------------------------------------//

int percursoOrdem( pABB p, int (*exibe)(void *dado) ){ //desce esquerda, mostra, desce direita
    if(p == NULL){
        return FRACASSO;
    }
    if(vazia(p)){
        return FRACASSO;
    }
    OrdemRecursivo(p->raiz, exibe);
    return SUCESSO;
}

void OrdemRecursivo( pNoABB temp, int (*exibe)(void *dado) ){
    if(temp->esq != NULL){
        OrdemRecursivo(temp->esq, exibe);
    }
    exibe(temp->dado);
    if(temp->dir != NULL){
        OrdemRecursivo(temp->dir, exibe);
    }
}
//------------------------------------------------------------------------------------------------//

int percursoPosOrdem( pABB p, int (*exibe)(void *dado) ){ //desde esquerda, desce direita, mostra
    if(p == NULL){
        return FRACASSO;
    }
    if(vazia(p)){
        return FRACASSO;
    }
    PosOrdemRecursivo(p->raiz, exibe);
    return SUCESSO;
}

void PosOrdemRecursivo( pNoABB temp, int (*exibe)(void *dado) ){
    if(temp->esq != NULL){
        PosOrdemRecursivo(temp->esq, exibe);
    }
    if(temp->dir != NULL){
        PosOrdemRecursivo(temp->dir, exibe);
    }
    exibe(temp->dado);
}
//------------------------------------------------------------------------------------------------//

int nfilhos( pNoABB p, int *pos ){ //recebe o endere o do n  que deseja verificar o n mero de filhos que possui
    int num = 0;
    if(p->esq != NULL){
        num++;
        if(pos != NULL){
            *pos = ESQUERDA;
        } //pos vai ser NULL quando a fun  o for chamada por percursoOrdem
    } //pos=0 = filho   esquerda, pos=1 = filho   direita, pos=2 = 2 filhos (esq e dir)
    if(p->dir != NULL){
        num++; //num == numero de filhos
        if(*pos == ESQUERDA){
            *pos = AMBOS;
        }//se tiver filho   esquerda, ent o tem filho nos 2 lados
        else if(pos != NULL){
            *pos = DIREITA;
        } //se n o, tem apenas   direita
    } //n o tem problema pos retornar sem receber valor, pois s  ser  necess rio nos casos onde recebe valor
    return num;
}
//------------------------------------------------------------------------------------------------//

pNoABB sucessor( pNoABB p ){
    pNoABB temp = NULL;
    if(p->esq != NULL){
        temp = p->esq;
    } //ACHO QUE NAO   NECESSARIO, VERIFICAR!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
    if(p->dir != NULL){
        temp = p->dir;
    }
    while(temp->esq != NULL){
        temp = temp->esq;
    }
    return temp; //retorna elemento mais   esquerda do elemento   direita do que se deseja remover
}
//------------------------------------------------------------------------------------------------//

int vazia( pABB p ){
    if(p->raiz != NULL){
        return OK;
    }
    else{
        return VAZIA;
    }
}
