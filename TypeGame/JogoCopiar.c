#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <Windows.h>

char comparar_string(char *str_resultado, char *string_digitada, int score, int *modos){
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
            printf("SCORE: %d    TEMPO: %d   QNT_PALAVRAS: %d\n", score-1, modos[0], modos[1]);
            if(score-1 < 3)
                printf("Habilidade: Iniciante\n");
            if(score-1 >= 3 && score-1 < 6)
                printf("Habilidade: Intermediario\n");
            if(score-1 >= 6)
                printf("\nHabilidade: MESTRE DO TYPEGAME!\n");

            printf("-----------------------------\n");
            printf("String Correta: %s\nSua String: %s\n", str_resultado, string_digitada);
            printf("-----------------------------\n");
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

int *Modo_De_Jogo(int tempo, int qnt_palavra, int *modos){
    int selecionar;
    //modo[0] = tempo    modo[1] = qnt_palavra
    printf("Selecione o modo de jogo:\n1 - Progressao (tmp=10, qnt_palavras=2)\n2 - CUSTOM\n");
    scanf("%d", &selecionar);

    switch(selecionar){
        case 1 : 
            system("cls");
            printf("Modo de jogo 'PROGRESSAO' definido!\n\n");
            printf("----' Jogo comeca em 5 segs!! '----");
            modos[0] = 8;
            modos[1] = 2;
            Sleep(5000);
            break;
        case 2 : 
            system("cls");
            printf("Configuracoes do modo 'CUSTOM'!\n\n"); 
            printf("Qnts de palavras desejadas: ");
            scanf("%d", &modos[1]);
            printf("Digite o tempo desejado: ");
            scanf("%d", &modos[0]);
            system("cls");
            printf("Modo de jogo 'CUSTOM' definido!\n"); 
            printf("---' Jogo comeca em 5 segs!! '---");
            Sleep(5000);
            break;
        default :  printf("ARGUMENTO ERRADO!"); return 0;
    }
    return modos;
}

void main(){
    int qnt_palavra, i, tempo, score=0, modos[1+1];
    char str_resultado[5*20+1], str_digitada[5*20+1];
    char *ptr_resultado = str_resultado;
    char *ptr_digitada = str_digitada;
    int *ptr_modos = modos;

    char LINHA[] = "-----------------------------\n";

    printf("----- ' Bem-Vindo ao: ' -----\n");
    printf("------- ' TypeGame ' --------\n");
    printf("%s\n", LINHA);

    Modo_De_Jogo(tempo, qnt_palavra, ptr_modos);

    do{
        gerar_palavra(modos[1], ptr_resultado);

        system("cls");

        printf("------> Decore o texto <-----\n\n");
        for (i=0; str_resultado[i] != '\0'; i++)
            printf("%c", str_resultado[i]);

        printf("\n\nSEGUNDOS RESTANTES:\n ");
        for (i=modos[0]; i>0; i--){
            printf("\r%d", i);
            Sleep(1000);
        }

       system("cls");

        fflush(stdin);
        printf("\nDigite a string:\n");
        fgets(str_digitada, sizeof(str_digitada), stdin);

        if (modos[0]!=2 && modos[1]!=8){
            modos[0] -= 1;
            modos[1] += 1;
        }   
        score += 1;
        system("cls");
    } while(comparar_string(ptr_resultado, ptr_digitada, score, ptr_modos) == 1);
}