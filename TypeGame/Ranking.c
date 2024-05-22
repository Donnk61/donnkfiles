#include <stdio.h>

//Printar na tela, NEW RECORD, substituir no valor anterior

typedef struct rankTemplate{
    int score;
    char nome[20+1];
} RankTem;

int ler(){
    RankTem rankT;
    FILE *rankfile = fopen("Rank.txt", "r");
    if(rankfile){
        while(fscanf(rankfile, "%s %d",rankT.nome ,&rankT.score)!=EOF){
            printf("nome: %s, score: %d\n", rankT.nome, rankT.score);
        }
        fclose(rankfile);
    }
    else{
        printf("Falha ao abrir o arquivo");
        return 0;
    }
}

int main(){
    RankTem rankT;
    char continuar;
    int repetir;
    FILE *rankfile = fopen("Rank.txt", "w");
    if (rankfile){
        do{
            repetir=1;
            printf("Digite seu nome: ");
            fgets(rankT.nome, sizeof(rankT.nome), stdin);
            rankT.score = 10;
            printf("Digitado: %s", rankT.nome);
            fprintf(rankfile, "%s%d\n", rankT.nome, rankT.score);

            printf("Deseja continuar? s ou n\n");
            scanf("%c", &continuar);
            fflush(stdin);
            if (continuar=='n'){
                repetir=0;
            }
        }while(repetir==1);
        fclose(rankfile);
        ler();
    }
    else{
        printf("Falha ao abrir o arquivo");
        return 0;
    }
}