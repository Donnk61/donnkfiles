#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <Windows.h>

char comparar_string(char *str_resultado, char *string_digitada, int tempo, int qnt_palavra, int score){
    int i;

    for (i=0; str_resultado[i] != '\0'; i++){
        if (str_resultado[i] != string_digitada[i]){
            // printf("Nao igual %c - %c\n", str_resultado[i], string_digitada[i]);

            printf(" _____                          ____                   \n");
            printf("/ ____|                        / __ \\                 \n");
            printf("| |  __  __ _ _ __ ___   ___  | |  | |_   _____ _ __   \n");
            printf("| | |_ |/ _` | '_ ` _ \\ / _ \\ | |  | \\ \\ / / _\\ '__/ \n");
            printf("| |__| | (_| | | | | | |  __/ | |__| |\\ V /  __/ |    \n");
            printf("\\_____|\\__,_|_| |_| |_|\\___|   \\____/  \\_/\\___|_|    \n\n");
            printf("SCORE: %d    TEMPO: %d   QNT_PALAVRAS: %d\n", score-1, tempo, qnt_palavra);
            if(score-1 < 3)
                printf("Habilidade: Iniciante\n");
            if(score-1 >= 3 && score-1 < 6)
                printf("Habilidade: Intermediario\n");
            if(score-1 >= 6)
                printf("Habilidade: MESTRE DO TYPEGAME!\n");

            return 0;
        }
        // printf("Igual %c - %c\n", str_resultado[i], string_digitada[i]);
    }
    //printf("1");
    return 1;
}

int *escolher_palavra(int qnt_palavra, int *num_aleatorio){
    srand(time(NULL));
    int i;

    for (i=0; i<qnt_palavra; i++){    
        num_aleatorio[i] = rand() % 5;  
    }
    return num_aleatorio;
}

char *gerar_palavra(int qnt_palavra, char *str_resultado){
    int i, j, x, num_aleatorio[200];
    int *ptr = num_aleatorio;

    char palavras[5][20] = {
        {'P','o','v','o'},
        {'B','r','a','s','i','l','e','i','r','o'},
        {'P','e','s','s','o','a'},
        {'P','a','i','s'},
        {'I','n','d','i','g','e','n','a'}
    };
    
    escolher_palavra(qnt_palavra, ptr);    

    /*
    for(i=0; i<qnt_palavra; i++){        
        printf("%d ", num_aleatorio[i]);
    }*/

    for(i=0, x=0; i<qnt_palavra; i++){
        int indice = num_aleatorio[i];
        for(j=0; palavras[indice][j] != '\0'; j++, x++){
            //printf("%c", palavras[indice][j]);
            str_resultado[x] = palavras[indice][j];
        }
    }
    str_resultado[x] = '\0';

    return str_resultado;
}

void main(){
    int qnt_palavra, i, tempo, score=0;
    char str_resultado[5*20+1], str_digitada[5*20+1];
    char *ptr_resultado = str_resultado;
    char *ptr_digitada = str_digitada;

    char LINHA[] = "-----------------------------\n";

    printf("----- ' Bem-Vindo ao: ' -----\n");
    printf("------- ' TypeGame ' --------\n");
    printf("%s\n", LINHA);

    printf("Digite a qnt de palavras: ");
    scanf("%d", &qnt_palavra);

    printf("\nDigite o tempo desejado: ");
    scanf("%d", &tempo);

    do{
        gerar_palavra(qnt_palavra, ptr_resultado);

        system("cls");

        printf("------> Decore o texto <-----\n\n");
        for (i=0; str_resultado[i] != '\0'; i++)
            printf("%c", str_resultado[i]);

        printf("\n\nSEGUNDOS RESTANTES:\n ");
        for (i=tempo; i>0; i--){
            printf("\r%d", i);
            Sleep(1000);
        }

        system("cls");

        fflush(stdin);
        printf("\nDigite a string:\n");
        fgets(str_digitada, sizeof(str_digitada), stdin);

        system("cls");
        score += 1;
    } while(comparar_string(ptr_resultado, ptr_digitada, tempo, qnt_palavra, score) == 1);
}