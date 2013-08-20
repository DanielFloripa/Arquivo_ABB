#include "abb_publico.h"
#include "abb_privado.h"


FILE *fp;
char *arq = "abb.dat",
        *escr = "wb",
        *leit = "rb";

ppABB loadTDA_ABB( ppABB *pp ){
    int qtd, i, val;
    fp = fopen(arq, leit);
    if(fp == NULL){
        contaDados(); //para criar um novo arquivo
        return 0;
    }
    //else{
    qtd = contaDados();
    if(qtd == 0){
        printf("Arquivo vazio!!!\n");
        return 0;
    }
    printf("inserindo\n");
    (*pp) = (ppABB) malloc(sizeof (ABB) * qtd);
    fread((*pp), sizeof (ppABB), qtd, fp);
    fclose(fp);
    printf("feito no load\n");
    return (*pp);
    free(pp);
    // }
}

void saveTDA_ABB( pABB arvore, int qtd ){
    int *x;
    pNoABB temp;
    printf("Gravando em %s.\n QTD: %i\n", arq, qtd);
    fp = fopen(arq, escr);
    if(fp == NULL){
        printf("Problemas no %s", arq);
        exit(0);
    }
    fwrite(x, sizeof (int), qtd, fp);
    printf("Gravando..");
    printf(".......\n");
    fclose(fp);
    printf("Gravado %i contatos em %s com SUCESSO!!\n", qtd, arq);
}

int contaDados( ){
    int qtd, cap, total = 0;
    pABB temp;

    printf("\n\nContando dados.......\n");
    fp = fopen(arq, leit); // abre para leitura
    if(fp == NULL){ // se arquivo vazio:
        printf("Sem arquivo!\nCriando um vazio!\n");
        fp = fopen(arq, escr); //cria um arquivo vazio
        fclose(fp);
        return FRACASSO;
    }
    else{ // se tiver conteudo*/
        cap = 10;
        pABB temp = (pABB) malloc(sizeof (pABB) * cap);
        while(!feof(fp)){
            if(cap == qtd){
                cap = qtd * 2;
                temp = (pABB) realloc(temp, sizeof (pABB) * cap);
            }
            qtd = fread(temp, sizeof (pABB), cap, fp); // leia os 'n' contatos e copie para a struct
            if(ferror(fp)){
                perror("Erro de leitura");
                break;
            }
            total += qtd;
        }
        printf("Dados no %s = %i \n\n", arq, total);
        fclose(fp);
        free(temp);
        return total;
    }
}