#include "aplicacao.h"
#include "abb_privado.h"

pABB arvore = NULL;

int main( int argc, char* argv ){
    int escolha, posicao, qtd = 0;

    do{
        do{
            //system("clear || cls");
            printf("\n1) Criar arvore e verifica arquivo\n"); //
            printf("2) Inserir inteiro na arvore\n");
            printf("3) Remover inteiro da arvore\n");
            printf("4) Buscar inteiro na arvore\n");
            printf("5) Reiniciar arvore\n");
            printf("6) Destruir arvore\n");
            printf("7) Exibir todos os inteiros na arvore\n");
            printf("8) Fechar programa\n"); //
            printf("Sua escolha: ");
            scanf("%d", &escolha);
            fflush(stdin);
            getchar();
        }while(escolha > 8 || escolha < 1);
        //system("clear || cls");
        switch(escolha){
            case 8: break; //Fechar
            case 1: cria();
                break;
            case 2: insere();
                break;
            case 3: remover();
                break;
            case 4: buscar();
                break;
            case 5: reiniciar();
                break;
            case 6: destruir();
                break;
            case 7: buscartodos();
                break;
        }
    }while(escolha != 8);
    if(arvore != NULL)
        free(arvore);
    return 0;
}

/******************************************************************/

void cria( ){
    if(arvore != NULL){
        printf("Voce ja criou a arvore!\n");
        getchar();
    }
    else{
        if(!criaABB(&arvore, sizeof (int))){
            printf("Erro ao criar arvore.\n");
            getchar();
        }
        printf("Arvore criada!\n");
        /*loadTDA_ABB();
        if(arvore == 0)
            printf("Erro ao carregar arquivo!");
        printf("carregado!!\n");*/
    }
}

void insere( ){
    int qtd, x;
    
    if(arvore == NULL){
        printf("Voce deve primeiro criar uma arvore!\n");
        getchar();
    }
    else{
        printf("Digite um inteiro: ");
        scanf("%i", &x);
        printf("Inserindo: %i\n\n", x);
        if(!insereABB(arvore, &x, compara)){
            printf("Erro ao inserir inteiro.\n");
            getchar();
        }
        printf("Salvando no arquivo\n");
        //loadTDA_ABB();
        printf("Salvo\n");
    }
}

void remover( ){
    if(arvore == NULL){
        printf("Voce deve primeiro criar uma arvore e inserir um inteiro!\n");
        getchar();
    }
    else{
        int inteiro;
        printf("Digite um inteiro: ");
        scanf("%d", &inteiro);
        if(!removeABB(arvore, &inteiro, compara)){
            printf("Erro ao remover elemento.\n");
            getchar();
        }
        else{
            printf("Inteiro %d removido.\n", inteiro);
            getchar();
        }
    }
}

void buscar( ){
    if(arvore == NULL){
        printf("Voce deve primeiro criar uma arvore e inserir um inteiro!\n");
        getchar();
    }
    else{
        int inteiro;
        printf("Digite um inteiro: ");
        scanf("%d", &inteiro);
        if(!buscaABB(arvore, &inteiro, compara)){
            printf("Erro ao buscar inteiro.\n");
            fflush(stdin);
            getchar();
            fflush(stdin);
        }
        else{
            printf("O inteiro buscado existe na arvore (%d)\n", inteiro);
            fflush(stdin);
            getchar();
            fflush(stdin);
        }
    }
}

void reiniciar( ){
    if(arvore == NULL){
        printf("Voce deve primeiro criar uma arvore!\n");
        getchar();
    }
    else{
        if(!reiniciaABB(arvore)){
            printf("Erro na reinicializacao da arvore.\n");
            getchar();
        }
        else{
            printf("Arvore reiniciada com sucesso.\n");
            getchar();
        }
    }
}

void destruir( ){
    if(arvore == NULL){
        printf("Voce deve primeiro criar uma arvore!\n");
        getchar();
    }
    else{
        if(!destroiABB(&arvore)){
            printf("Erro na destruicao da arvore.\n");
            getchar();
        }
        else{
            printf("Arvore destruida com sucesso.\n");
            getchar();
        }
    }
}

void buscartodos( ){
    if(arvore == NULL){
        printf("Voce deve primeiro criar uma arvore!\n");
        getchar();
    }
    else{
        printf("Percurso Pre-Ordem\n");
        percursoPreOrdem(arvore, exibe);
        printf("\n//------------------------------//\nPercurso Ordem\n");
        percursoOrdem(arvore, exibe);
        printf("\n//------------------------------//\nPercurso Pos-Ordem\n");
        percursoPosOrdem(arvore, exibe);
        printf("\nPressione ENTER para continuar.\n");
        getchar();
    }
}

int compara( void *dado1, void *dado2 ){
    int *num1, *num2;
    num1 = (int*) dado1;
    num2 = (int*) dado2;
    if(*num1<*num2){
        return MENOR;
    }
    if(*num1>*num2){
        return MAIOR;
    }
    else{
        return IGUAL;
    }
}

int exibe( void *dado ){
    int *num;
    num = (int*) dado;
    printf("dado = %d, \n", *num);
    return SUCESSO;
}
/*
void loadTDA_ABB( ){
    int qtd, i,val;
    fp = fopen(arq, leit);
    if(fp == NULL){
        printf("Sem arquivo ou vazio!\nCriando vazio!\n");
        fp = fopen(arq,escr);
        fclose(fp);
        exit(0);
    }
    else{
        qtd = contaDados();
        if(qtd == 0){
            printf("Arduivo vazio!!!\n");
            return;
        }
        printf("inserindo\n");
        pABB temp = (pABB) malloc(sizeof (pABB) * qtd);
        for(i = 0; i < qtd; i++){
            printf("no for = %i\n",i);
            fread(&val, sizeof (int), 1, fp);
            printf("insere val %i\n",val);
            insereABB(arvore, &val, compara);
        }
        fclose(fp);
        free(temp);
    }
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
    sleep(1);
    printf(".......\n");
    fclose(fp);
    printf("Gravado %i contatos em %s com SUCESSO!!\n", qtd, arq);
}

int contaDados( ){
    int qtd, cap, total = 0;
    pABB temp;

    printf("\n\nContando dados.......\n");
    fp = fopen(arq, leit); // abre para leitura
    if(fp == NULL){ // se arquivo vazio, leia:
        printf("Arquivo Vazio!!\n");
        return 0;
    }
    else{ // se tiver conteudo
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
}*/