#include <stdio.h>
#include <stdlib.h>

int main(){
    FILE *arquivo;
    char nome[5]="samu";
    int idade=0;
    float altura=0;
    char x='c';

    if((arquivo = fopen("samu.txt","w+t")) == NULL)
      {
        printf("Erro ao abrir arquivo!!!\n\n");
        exit(1);
      }

    fwrite(&nome,sizeof(nome),1,arquivo);
    fwrite(&idade,sizeof(idade),1,arquivo);
    fwrite(&altura,sizeof(altura),1,arquivo);

    fclose(arquivo);

    return(0);
  }
