#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <Windows.h>
//ASCII 3D
//modo[0] = tempo    modo[1] = qnt_palavra    modo[2] = tema    modo[3] = jogar dnv

//Menu interativo
//Ver se é possível add música
//Salvar pontuação/Tabela de Ranking/Jogar novamente

int comparar_string(char *str_resultado, char *string_digitada){
    int i, continuar;

    for (i=0;str_resultado[i] != '\0'; i++){        
        if (string_digitada[i] != str_resultado[i]){
            // printf("Nao igual %c - %c\n", str_resultado[i], string_digitada[i]);
            system("cls");
            printf("-------------------------------------------------[ ]: ]-----------------------------------------------\n");
            printf("                 ________         ______                ______           \n");
            printf("                |\\  _____\\       |\\___   \\  ___        |\\___   \\  ___    \n");
            printf("                \\ \\  \\__/        \\|___|\\  \\|\\__\\       \\|___|\\  \\|\\__\\   \n");
            printf("                 \\ \\   __\\            \\ \\  \\|__|            \\ \\  \\|__|   \n");
            printf("                  \\ \\  \\_|            _\\_\\  \\  ___          _\\_\\  \\  ___ \n");
            printf("                   \\ \\__\\            |\\______\\|\\__\\        |\\______\\|\\__\\\n");
            printf("                    \\|__|            \\|______|\\|__|        \\|______|\\|__|\n");           
            printf("--------------------------------------------[ VOCE PERDEU ]-------------------------------------------\n"); 
            Beep(450, 500); Beep(375, 500); Beep(300, 2000);
            system("cls");
            return 0;
        }
        break;
        // printf("Igual %c - %c\n", str_resultado[i], string_digitada[i]);
    }
    //printf("1");
    return 1;
} 

int *escolher_palavra(int qnt_palavra, int *num_aleatorio, int modos[]){
    srand(time(NULL));
    int i;
    if (modos[2]==1){
        for (i=0; i<qnt_palavra; i++){    
            num_aleatorio[i] = rand() % 5;  
        }
    } 
    if(modos[2]==2){
        for (i=0; i<qnt_palavra; i++){
            do{    
                num_aleatorio[i] = rand() % 10;
            }while(num_aleatorio[i]<4);
            //printf("%d", num_aleatorio[i]);
        }
    }
    if (modos[2]==3){
        for (i=0; i<qnt_palavra; i++){    
            num_aleatorio[i] = rand() % 10;  
        }
    } 
    return num_aleatorio;
}

char *gerar_palavra(int qnt_palavra, char *str_resultado, int modos[]){
    int i, j, x, num_aleatorio[200];
    int *ptr = num_aleatorio;

    char palavras[10][20+1] = {
        {'P','o','v','o'},
        {'B','r','a','s','i','l','e','i','r','o'},
        {'P','e','s','s','o','a'},
        {'P','a','i','s'},
        {'I','n','d','i','g','e','n','a'},
    // ----------------------------------------- 
        {'Q','u','a','d','r','o'},
        {'P','r','o','f','e','s','s','o','r'},
        {'P','i','n','c','e','l'},
        {'M','e','s','a'},
        {'A','l','u','n','o'}
    };
    
    escolher_palavra(qnt_palavra, ptr, modos);    

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
            str_resultado[x] = ' ';
            x++;
    }
        if (x > 0 && str_resultado[x-1] == ' '){
            str_resultado[x-1] = '\0';
        }
    return str_resultado;
}

int *Modo_De_Jogo(int tempo, int qnt_palavra, int *modos){
    int selecionar, falso=0, i;
    do{
        falso=1;
        printf("                                   [* SELECIONE O -MODO- DE JOGO *]\n");
        printf("                                     1 - Endless   |   2 - CUSTOM\n\n");
        scanf("%d", &selecionar);
        if (selecionar>2 || selecionar<0){
            falso=0;
            printf("                                      MODO DE JOGO INVALIDO!!\n\n");
        }

    }while(falso==0);

    do{
        falso=1;
        printf("                                   [* SELECIONE O -TEMA- DO JOGO *]\n");
        printf("                      1 - Brasil   |   2 - Escola   |   3 - TODOS   |   (4-sair)\n");
        scanf("%d", &modos[2]);
        if (modos[2]>4 || modos[2]<0){
            falso=0;
            printf("                                      TEMA DO JOGO INVALIDO!!\n\n");
        }
        if (modos[2]==4){
            return 0;
        }

    }while(falso==0);
    system("cls");

    switch(selecionar){
        case 1 : 
            printf("--------------------------------------[* MODO DE JOGO DEFINDO *]--------------------------------------\n");
            printf("             _______   ________   ________  ___       _______   ________   ________      \n");
            printf("            |\\  ___ \\ |\\   ___  \\|\\   ___ \\|\\  \\     |\\  ___ \\ |\\   ____\\ |\\   ____\\     \n");
            printf("            \\ \\   __/|\\ \\  \\\\ \\  \\ \\  \\_|\\ \\ \\  \\    \\ \\   __/|\\ \\  \\___|_\\ \\  \\___|_    \n");
            printf("             \\ \\  \\_|/_\\ \\  \\\\ \\  \\ \\  \\\\\\ \\ \\  \\    \\ \\  \\_|/_\\ \\_____  \\\\ \\_____  \\   \n");
            printf("              \\ \\  \\_|\\ \\ \\  \\\\ \\  \\ \\  \\\\\\ \\ \\  \\____\\ \\  \\_|\\ \\|____|\\  \\\\|____|\\  \\  \n");
            printf("               \\ \\_______\\ \\__\\\\ \\__\\ \\_______\\ \\_______\\ \\_______\\____\\_\\  \\ ____\\_\\  \\ \n");
            printf("                \\|_______|\\|__| \\|__|\\|_______|\\|_______|\\|_______|\\_________\\\\_________\\\n");
            printf("                                                                  \\|_________\\|_________|\n");
            printf("-----------------------------------[* JOGO COMECA EM 5 SEGUNDOS!! *]----------------------------------\n");

            modos[0] = 8;
            modos[1] = 2;
            for(i=0; i<5; i++){
                if (i==4){
                    Beep(400,2000);
                    continue;
                }
                else
                    Beep(250,500);
                Sleep(1000);
            }
            break;
        case 2 : 
            printf("--------------------------------------[* MODO DE JOGO DEFINDO *]--------------------------------------\n");
            printf("             ________  _______  _________  _________  ___  ________   ________  ________      \n");
            printf("            |\\   ____\\|\\  ___ \\|\\___   ___\\\\___   ___\\\\  \\|\\   ___  \\|\\   ____\\|\\   ____\\     \n");
            printf("            \\ \\  \\___|\\ \\   __/\\|___ \\  \\_\\|___ \\  \\_\\ \\  \\ \\  \\\\ \\  \\ \\  \\___|\\ \\  \\___|_    \n");
            printf("             \\ \\_____  \\ \\  \\_|/__  \\ \\  \\     \\ \\  \\ \\ \\  \\ \\  \\\\ \\  \\ \\  \\  __\\ \\_____  \\   \n");
            printf("              \\|____|\\  \\ \\  \\_|\\ \\  \\ \\  \\     \\ \\  \\ \\ \\  \\ \\  \\\\ \\  \\ \\  \\|\\  \\|____|\\  \\  \n");
            printf("                ____\\_\\  \\ \\_______\\  \\ \\__\\     \\ \\__\\ \\ \\__\\ \\__\\\\ \\__\\ \\_______\\____\\_\\  \\ \n");
            printf("               |\\_________\\|_______|   \\|__|      \\|__|  \\|__|\\|__| \\|__|\\|_______|\\_________\\\n");
            printf("               \\|_________|                                                       \\|_________|\n");
            printf("------------------------------------------[* CONFIGURACOES *]-----------------------------------------\n");

            printf("                                   [* QUANTAS -PALAVRAS- DESEJA? *]\n");
            scanf("%d", &modos[1]);
            printf("                                     [* QUANTO -TEMPO- DESEJA? *]\n");
            scanf("%d", &modos[0]);
            printf("-----------------------------------[* JOGO COMECA EM 5 SEGUNDOS!! *]----------------------------------\n");
            for(i=0; i<5; i++){
                if (i==4){
                    Beep(400,2000);
                    continue;
                }
                else
                    Beep(250,500);
                Sleep(1000);
            }
            break;
        default :  printf("ARGUMENTO ERRADO!"); return 0;
    }
    return modos;
}

int main(){
    int qnt_palavra, i, tempo, score=0, modos[3+1], duracao=550, continuar, speed=250;
    char str_resultado[5*20+1], str_digitada[5*20+1], fim;
    char *ptr_resultado = str_resultado;
    char *ptr_digitada = str_digitada;
    int *ptr_modos = modos;

    do{
        printf("\n");
        char bemvindo[14+1] = {'B','e','m','-','v','i','n','d','o','s',' ','a','o',':'};
        for(i=0; bemvindo[i] != '\0'; i++){
            printf("%c", bemvindo[i]);
            Beep(300, speed);
            Sleep(speed);
        }

        printf("----------------------------------------------------------------------------------------\n"); Sleep(speed);    
        printf(" _________    ___    ___ ________  _______           ________  ________  _____ ______   _______      \n"); Sleep(speed);
        printf("|\\___   ___\\ |\\  \\  /  /|\\   __  \\|\\  ___ \\         |\\   ____\\|\\   __  \\|\\   _ \\  _   \\|\\  ___ \\     \n"); Sleep(speed);
        printf("\\|___ \\  \\_| \\ \\  \\/  / | \\  \\|\\  \\ \\   __/|        \\ \\  \\___|\\ \\  \\|\\  \\ \\  \\\\\\__\\ \\  \\ \\   __/|    \n"); Sleep(speed);
        printf("     \\ \\  \\   \\ \\    / / \\ \\   ____\\ \\  \\_|/__       \\ \\  \\  __\\ \\   __  \\ \\  \\\\|__| \\  \\ \\  \\_|/__  \n"); Sleep(speed);
        printf("      \\ \\  \\   \\/  /  /   \\ \\  \\___|\\ \\  \\_|\\ \\       \\ \\  \\|\\  \\ \\  \\ \\  \\ \\  \\    \\ \\  \\ \\  \\_|\\ \\ \n"); Sleep(speed);
        printf("       \\ \\__\\__/  / /      \\ \\__\\    \\ \\_______\\       \\ \\_______\\ \\__\\ \\__\\ \\__\\    \\ \\__\\ \\_______\\\n"); Sleep(speed);
        printf("        \\|__|\\___/ /        \\|__|     \\|_______|        \\|_______|\\|__|\\|__|\\|__|     \\|__|\\|_______|\n"); Sleep(speed);
        printf("            \\|___|/                                                                  \n"); Sleep(speed);
        printf("------------------------------------------------------------------------------------------------------\n"); Sleep(speed+50);
        
        if (Modo_De_Jogo(tempo, qnt_palavra, ptr_modos)==0){
            return 0;
        }

        do{
            continuar = 0;
            gerar_palavra(modos[1], ptr_resultado, modos);

            system("cls");
            printf("        ________  _______   ________  ________  ________  ________  _________  _______      \n");
            printf("        |\\   ___ \\|\\  ___ \\ |\\   ____\\|\\   __  \\|\\   __  \\|\\   __  \\|\\___   ___\\\\  ___ \\     \n");
            printf("        \\ \\  \\_|\\ \\ \\   __/|\\ \\  \\___|\\ \\  \\|\\  \\ \\  \\|\\  \\ \\  \\|\\  \\|___ \\  \\_\\ \\   __/|    \n");
            printf("         \\ \\  \\ \\\\ \\ \\  \\_|/_\\ \\  \\    \\ \\  \\\\\\  \\ \\   _  _\\ \\   __  \\   \\ \\  \\ \\ \\  \\_|/__  \n");
            printf("          \\ \\  \\_\\\\ \\ \\  \\_|\\ \\ \\  \\____\\ \\  \\\\\\  \\ \\  \\\\  \\\\ \\  \\ \\  \\   \\ \\  \\ \\ \\  \\_|\\ \\ \n");
            printf("           \\ \\_______\\ \\_______\\ \\_______\\ \\_______\\ \\__\\\\ _\\\\ \\__\\ \\__\\   \\ \\__\\ \\ \\_______\\\n");
            printf("            \\|_______|\\|_______|\\|_______|\\|_______|\\|__|\\|__|\\|__|\\|__|    \\|__|  \\|_______|\n");
            printf("-----------------------------------------[* DECORE O TEXTO! *]----------------------------------------\n\n");
            for (i=0; str_resultado[i] != '\0'; i++)
                printf("%c", str_resultado[i]);
            
            printf("\n\n\t\t\t\t\t  SEGUNDOS RESTANTES:\n ");
            for (i=modos[0]; i>0; i--){
                printf("\r\t\t\t\t\t\t  %d", i);
                Sleep(1000);
            }

            system("cls");

            fflush(stdin);
            printf(" _______   ________   _________  _______   ________          _________  _______      ___    ___ _________   \n");
            printf("|\\  ___ \\ |\\   ___  \\|\\___   ___\\\\  ___ \\ |\\   __  \\        |\\___   ___\\\\  ___ \\    |\\  \\  /  /|\\___   ___\\ \n");
            printf("\\ \\   __/|\\ \\  \\\\ \\  \\|___ \\  \\_\\ \\   __/|\\ \\  \\|\\  \\       \\|___ \\  \\_\\ \\   __/|   \\ \\  \\/  / ||___ \\  \\_| \n");
            printf(" \\ \\  \\_|/_\\ \\  \\\\ \\  \\   \\ \\  \\ \\ \\  \\_|/_\\ \\   _  _\\           \\ \\  \\ \\ \\  \\_|/__  \\ \\    / /     \\ \\  \\  \n");
            printf("  \\ \\  \\_|\\ \\ \\  \\\\ \\  \\   \\ \\  \\ \\ \\  \\_|\\ \\ \\  \\\\  \\|           \\ \\  \\ \\ \\  \\_|\\ \\  /     \\/       \\ \\  \\ \n");
            printf("   \\ \\_______\\ \\__\\\\ \\__\\   \\ \\__\\ \\ \\_______\\ \\__\\\\ _\\            \\ \\__\\ \\ \\_______\\/  /\\   \\        \\ \\__\\\n");
            printf("    \\|_______|\\|__| \\|__|    \\|__|  \\|_______|\\|__|\\|__|            \\|__|  \\|_______/__/ /\\ __\\        \\|__|\n");
            printf("                                                                                    |__|/ \\|__|             \n");
            printf("-----------------------------------------[* DIGITE O TEXTO! *]----------------------------------------\n\n");
            fgets(str_digitada, sizeof(str_digitada), stdin);

            if (modos[0]!=2 && modos[1]!=8){
                modos[0] -= 1;
                modos[1] += 1;
            }else
                duracao -= 50;  

            if (comparar_string(ptr_resultado, ptr_digitada) == 1){
                system("cls");
                score += 1;
                continuar = 1;
                printf("          _____          ________  ________  ___  ________   _________            ______      \n");
                printf("         / __  \\        |\\   __  \\|\\   __  \\|\\  \\|\\   ___  \\|\\___   ___\\      ___|\\___   \\    \n");
                printf("        |\\/_|\\  \\       \\ \\  \\|\\  \\ \\  \\|\\  \\ \\  \\ \\  \\\\ \\  \\|___ \\  \\_|     |\\__\\|___|\\  \\   \n");
                printf("        \\|/ \\ \\  \\       \\ \\   ____\\ \\  \\\\\\  \\ \\  \\ \\  \\\\ \\  \\   \\ \\  \\      \\|__|    \\ \\  \\  \n");
                printf("             \\ \\  \\       \\ \\  \\___|\\ \\  \\\\\\  \\ \\  \\ \\  \\\\ \\  \\   \\ \\  \\         ___  _\\_\\  \\ \n");
                printf("              \\ \\__\\       \\ \\__\\    \\ \\_______\\ \\__\\ \\__\\\\ \\__\\   \\ \\__\\       |\\__\\|\\______\\\n");
                printf("               \\|__|        \\|__|     \\|_______|\\|__|\\|__| \\|__|    \\|__|       \\|__|\\|______|\n");
                printf("---------------------------------------[* PONTUACAO ATUAL: %d *]---------------------------------------\n\n", score);
                Beep(350, duracao); Beep(400, duracao); Beep(450, duracao);
                Sleep(1000);
            }
            else{ 
                printf("-------------------------------------------------[ ]: ]-----------------------------------------------\n");
                printf(" ________  ________  _____ ______   _______           ________  ___      ___ _______   ________     \n");
                printf("|\\   ____\\|\\   __  \\|\\   _ \\  _   \\|\\  ___ \\         |\\   __  \\|\\  \\    /  /|\\  ___ \\ |\\   __  \\    \n");
                printf("\\ \\  \\___|\\ \\  \\|\\  \\ \\  \\\\\\__\\ \\  \\ \\   __/|        \\ \\  \\|\\  \\ \\  \\  /  / | \\   __/|\\ \\  \\|\\  \\   \n");
                printf(" \\ \\  \\  __\\ \\   __  \\ \\  \\\\|__| \\  \\ \\  \\_|/__       \\ \\  \\\\\\  \\ \\  \\/  / / \\ \\  \\_|/_\\ \\   _  _\\  \n");
                printf("  \\ \\  \\|\\  \\ \\  \\ \\  \\ \\  \\    \\ \\  \\ \\  \\_|\\ \\       \\ \\  \\\\\\  \\ \\    / /   \\ \\  \\_|\\ \\ \\  \\\\  \\| \n");
                printf("   \\ \\_______\\ \\__\\ \\__\\ \\__\\    \\ \\__\\ \\_______\\       \\ \\_______\\ \\__/ /     \\ \\_______\\ \\__\\\\ _\\ \n");
                printf("    \\|_______|\\|__|\\|__|\\|__|     \\|__|\\|_______|        \\|_______|\\|__|/       \\|_______|\\|__|\\|__|\n");
                printf("-----------------------------------------------[* INFOS *]--------------------------------------------\n\n");

                printf("SCORE: %d    TEMPO: %d   QNT_PALAVRAS: %d   ", score, modos[0], modos[1]);
                if(score < 4)
                    printf("Habilidade: Iniciante\n");
                if(score >= 4 && score < 7)
                    printf("Habilidade: Intermediario\n");
                if(score >= 7)
                    printf("\nHabilidade: MESTRE DO TYPEGAME!\n");

                printf("\n----------------------------------------------[* STRINGS *]-------------------------------------------\n\n");
                printf("String Correta: %s\nSua String: %s\n", str_resultado, str_digitada);
                printf("---------------------------------------------[* CONTINUE *]-------------------------------------------\n\n");
                printf("[* SALVAR PONTUACAO: 'p' *]          [* JOGAR NOVAMENTE: 'j' *]          [* SAIR: 's' *]\n");
                do{
                    i=1;
                    scanf("%c", &fim);
                    fflush(stdin);
                    if(fim=='s')
                        return 0;
                    else if(fim=='j'){
                        i=0;
                        continuar=0;
                        modos[3]=1;
                        speed=0;
                        system("cls");
                    }
                    else if(fim=='p'){
                        i=0;
                    }
                    else
                        printf("Opcao invalida, tente novamente!\n");                 
                }while(i);
            }
        }while(continuar);
    }while(modos[3]==1);
}