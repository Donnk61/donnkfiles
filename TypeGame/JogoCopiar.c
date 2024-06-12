#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <Windows.h>
#include <pthread.h>
//ASCII 3D
//modo[0] = tempo    modo[1] = qnt_palavra    modo[2] = tema    modo[3] = jogar dnv

//viaráveis globais
volatile int pararcronometro = 0;
volatile int tempocronometro;
typedef struct dataTemplate{
    char nome[20+1];
    unsigned int senha;
    int score;
} dataTem;

//declarações
enum cores {PRETO,AZUL,VERDE,CIANO,VERMELHO,MAGENTA,MARROM,CINZACLARO,CINZAESCURO,AZULCLARO,VERDECLARO,CIANOCLARO,VERMELHOCLARO,MAGENTACLARO,AMARELO,BRANCO};
enum ascii {GAMEOVER, NEWRECORD, FAIL, MOREPOINT, ENTERTEXT, DECORATE, SETTINGS, ENDLESS, TYPEGAME, SIGNIN, STARTUP, SIGNUP, TIMEOVER, MAX, VIDA};
void textColor(int letras, int fundo);
void ASCII(int texto);
void clear();
void *musicIntro();
void *cronometro();
int comparar_string(char str_resultado[], char str_digitada[]);
void copiar_string(char *entrada, char *saida);
void remover_enter(char str[]);
int atualizar_data(int score, char nome[]);
void top_1();
void ler_data();
int escrever_data();
int buscar_data(char nome_digitado[], int senha_digitada);
void ver_pontuacao(char nome[]);
void *escolher_palavra(int qnt_palavra, int *num_aleatorio, int modos[]);
char *gerar_palavra(int qnt_palavra, char *str_resultado, int modos[]);

int main(){
    int modos[3+1], speed=100, qnt_palavra, tempo, score, duracao, senha_digitada, newrecord, acertos, mensagem_dificuldade, vida;
    int i, j, selecionar, falso, endless, continuar; //Controles
    float tempomedio[20];
    char str_resultado[5*20+1], str_digitada[5*20+1], nome_digitado[20+1], escolha_inicio, fim;
    char *ptr_resultado = str_resultado;
    char *ptr_digitada = str_digitada;
    int *ptr_modos = modos;
    dataTem rankT;
    pthread_t thread1, thread2;

    clear();
    pthread_create(&thread1, NULL, musicIntro, NULL);
    do{ 
        //2 prosseguir
        ASCII(STARTUP);
        printf("[* CADASTRAR: 'C' *]        [* LOGIN: 'L' *]        [* SAIR: 'S' *]""        [* VER CADASTROS: 'V' *]\n");
        do{ 
            //1 prosseguir
            falso=0;
            printf("--> ");
            escolha_inicio = getchar();
            fflush(stdin);
            switch (escolha_inicio){
                case 'C' : 
                    clear(); 
                    if(escrever_data()==1){
                        clear();
                        textColor(VERDE, PRETO);
                        printf("Usuario cadastrado com sucesso!\n");
                        textColor(CINZACLARO, PRETO);
                    };
                    falso=1;
                    break;
                case 'V' : ler_data(); break;
                case 'L' :
                    clear();
                    ASCII(SIGNIN);
                    printf("\t\t\t\t  [* DIGITE SEU USUARIO(s/espaco): *]\n--> ");
                    fgets(nome_digitado, sizeof(nome_digitado), stdin);
                    remover_enter(nome_digitado);
                    fflush(stdin);
                    printf("\t\t\t\t  [* DIGITE SUA SENHA(apenas nums): *]\n--> ");
                    scanf("%d", &senha_digitada);
                    fflush(stdin);
                    clear();
                    falso=1;
                    //printf("%s%d", nome_digitado, senha_digitada);
                    if(buscar_data(nome_digitado, senha_digitada)==1){
                        textColor(VERDECLARO, PRETO);
                        printf("Login feito com sucesso!\n");
                        textColor(CINZACLARO, PRETO);
                        printf("Iniciando jogo..."); Sleep(3000);
                        clear();
                        falso=2;
                    }
                    break;        
                    case 'S' : return 0;
                    default : textColor(VERMELHO, PRETO); printf("Escolha errada!\n\n"); textColor(CINZACLARO, PRETO);
                }
        }while(falso==0);
    }while(falso!=2);

    copiar_string(nome_digitado, rankT.nome);

    do{
        endless=0;
        duracao=550;
        score=0;
        newrecord=0;
        acertos=0;
        mensagem_dificuldade=0;
        printf("\n");
        
        char bemvindo[] = "Bem-vindo(a) ao:";
        for(i=0; bemvindo[i] != '\0'; i++){
            printf("%c", bemvindo[i]);
            //Beep(300, speed);
            Sleep(speed);
        }

        ASCII(TYPEGAME);
        
        do{
            fflush(stdin);
            falso=1;
            printf("\t\t\t\t   [* SELECIONE O -MODO- DE JOGO *]\n");
            textColor(VERMELHO, PRETO);
            printf("\t\t1 - Endless (2 vidas)");
            textColor(CINZACLARO, PRETO);
            printf("   |   ");
            textColor(AZULCLARO, PRETO);
            printf("2 - CUSTOM (1 vida | nao salva pontuacao)\n\n"); textColor(CINZACLARO, PRETO); printf("--> ");
            scanf("%d", &selecionar);

            if (selecionar!=2 && selecionar!=1){
                falso=0;
                textColor(VERMELHO, PRETO);
                printf("\t\t  MODO DE JOGO INVALIDO!!\n\n");
                textColor(CINZACLARO, PRETO);
            }

        }while(falso==0);

        do{
            fflush(stdin);
            falso=1;
            printf("\t\t\t\t   [* SELECIONE O -TEMA- DO JOGO *]\n"); 
            textColor(VERMELHO, PRETO);
            printf("\t\t\t1 - Brasil");
            textColor(CINZACLARO, PRETO);
            printf("   |   "); 
            textColor(AZULCLARO, PRETO);
            printf("2 - Escola"); 
            textColor(CINZACLARO, PRETO);
            printf("   |   "); 
            textColor(VERMELHO, PRETO);
            printf("3 - "); textColor(AZULCLARO, PRETO); printf("TODOS"); 
            textColor(CINZACLARO, PRETO);
            printf("   |   "); 
            textColor(VERMELHOCLARO, PRETO);
            printf("(4-sair)\n"); 
            textColor(CINZACLARO, PRETO);
            printf("--> ");
            scanf("%d", &modos[2]);
            if (modos[2]<1 || modos[2]>4){
                falso=0;
                textColor(VERMELHO, PRETO);
                printf("\t\t\t\t\t\t\t   TEMA DO JOGO INVALIDO!!\n\n");
                textColor(CINZACLARO, PRETO);
            }
            if (modos[2]==4){
                return 0;
            }

        }while(falso==0);
        clear();

        switch(selecionar){
            case 1 : 
                ASCII(ENDLESS);
                vida = 1;
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
                endless=1;
                break;
            case 2 : 
                ASCII(SETTINGS);
                do{
                    fflush(stdin);
                    falso=1;
                    printf("\t\t\t   [* QUANTAS -PALAVRAS- DESEJA? (min 1 | max 10) *]\n--> ");
                    scanf("%d", &modos[1]);
                    if(modos[1]<1 || modos[1]>10){
                        textColor(VERMELHO, PRETO); printf("Quantidade incorreta\n"); textColor(CINZACLARO, PRETO);
                        falso=0;
                    }
                }while(falso==0);

                do{
                    fflush(stdin);
                    falso=1;
                    printf("\t\t\t    [* QUANTO -TEMPO- DESEJA? (min 1 | max 20) *]\n--> ");
                    scanf("%d", &modos[0]);
                    if(modos[0]<1 || modos[0]>20){
                        textColor(VERMELHO, PRETO);
                        printf("Tempo incorreto\n");
                        textColor(CINZACLARO, PRETO);
                        falso=0;
                    }
                }while(falso==0);

                printf("[*-----------------------------------[* JOGO COMECA EM 5 SEGUNDOS!! *]----------------------------------*]\n");
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
        pthread_join(thread1, NULL);

        j=0;
        do{
            pararcronometro=0;
            continuar = 0;
            gerar_palavra(modos[1], ptr_resultado, modos);
            clear();
            if (mensagem_dificuldade==1){
                textColor(VERMELHO, PRETO);    
            }
            ASCII(DECORATE);
            textColor(CINZACLARO, PRETO); printf("--> ");
            textColor(VERDE, PRETO);
            for (i=0; str_resultado[i] != '\0'; i++)
                printf("%c", str_resultado[i]);
            textColor(CINZACLARO, PRETO);
            printf(" <--");

            printf("\n\n\t\t\t\t\t  SEGUNDOS RESTANTES:\n ");
            for (i=modos[0]; i>0; i--){
                printf("\r\t\t\t\t\t\t  %d", i);
                Sleep(1000);
            }

            clear();
            ASCII(ENTERTEXT);
            pthread_create(&thread2, NULL, cronometro, NULL);
            fflush(stdin);
            fgets(str_digitada, sizeof(str_digitada), stdin);
            remover_enter(str_digitada);
            pararcronometro=1;

            int tempofim=0;
            if (tempocronometro>=15)
                tempofim=1;

            pthread_join(thread2, NULL);

            int msg_vida=0;
            if (comparar_string(str_resultado, str_digitada)==1 && tempofim==0){
                clear();
                tempomedio[j] = tempocronometro;
                j++;
                acertos +=1;
                continuar =1;
                ASCII(MOREPOINT);

                if (tempocronometro>=0 && tempocronometro<=2){
                    score +=3;
                }
                else if (tempocronometro>=3 && tempocronometro<=6){
                    score +=2;
                }
                else if (tempocronometro>=7 && tempocronometro<15){
                    score +=1;
                }

                printf("[*---------------------------------------[* PONTUACAO ATUAL: %d *]---------------------------------------*]\n\n", score); Sleep(100);
                printf("\t\t\t\t    [* TEMPO GASTO PARA DIGITAR: %d *]", tempocronometro);
                Beep(350, duracao); Beep(400, duracao); Beep(450, duracao);
                Sleep(duracao*5);

                if (modos[0]!=2 && modos[1]!=8 && endless==1){
                    modos[0] -= 1;
                    modos[1] += 1;
                    duracao -= 50;  
                }
                else if (mensagem_dificuldade==0){
                    clear();
                    ASCII(MAX);
                    textColor(VERMELHO, PRETO); printf("\t\t\t\tDIFICULDADE MAXIMA ATINGIDA!!\n"); textColor(CINZACLARO, PRETO);
                    mensagem_dificuldade=1;
                    Sleep(4000);
                }

            }
            else if(vida!=0){
                clear();
                vida -= 1;
                if (msg_vida==0){
                    ASCII(VIDA);
                    printf("\t\t\t\t\t VIDAS RESTANTES: %d\n\n", vida);
                    msg_vida=1;
                }
                Sleep(2000);
                continuar = 1;
            }
            else{ 
                clear();
                tempomedio[j] = 0;
                ASCII(FAIL);
                Beep(450, 500); Beep(375, 500); Beep(300, 2000);

                clear();
                if(endless==1){
                    if(atualizar_data(score, nome_digitado)==1)
                        newrecord=1;
                }

                if(newrecord==1){
                    ASCII(NEWRECORD);
                }
                else{
                    ASCII(GAMEOVER);
                }
                printf("[*-----------------------------------------------[* INFOS *]--------------------------------------------*]\n\n"); Sleep(100);
                printf("SCORE: %d    TEMPO: %d   QNT_PALAVRAS: %d   ", score, modos[0], modos[1]); Sleep(100);
                if(score < 9)
                    printf("Habilidade do %s: Iniciante\n", nome_digitado); Sleep(100);
                if(score >= 9 && score < 18)
                    printf("Habilidade do %s: Intermediario\n", nome_digitado); Sleep(100);
                if(score >= 18)
                    printf("\nHabilidade do %s: MESTRE DO TYPEGAME!\n", nome_digitado); Sleep(100);
                
                
                if (tempomedio[j-1]!=0){
                    for(i=1; tempomedio[i]>0 && tempomedio[i]<15; i++){
                        tempomedio[0] += tempomedio[i];
                    }
                    tempomedio[0] = tempomedio[0]/acertos;
                }
                printf("ACERTOS: %d   TEMPO MEDIO DE RESPOSTA: %.2f", acertos, tempomedio[0]);

                printf("\n[*----------------------------------------------[* STRINGS *]-------------------------------------------*]\n\n"); Sleep(100);
                printf("String Correta: "); textColor(VERDE, PRETO); printf("%s\n", str_resultado); textColor(CINZACLARO, PRETO); printf("Sua String: ");textColor(VERMELHO, PRETO); printf("%s\n\n", str_digitada); textColor(CINZACLARO, PRETO); Sleep(100);
                printf("[*---------------------------------------------[* CONTINUE *]-------------------------------------------*]\n\n"); Sleep(100);
                textColor(AZULCLARO, PRETO);printf("[* VER MELHOR PONTUACAO: 'P' *]");
                textColor(AMARELO, PRETO); printf("    [* TOP 1: 'R' *]");
                textColor(VERDECLARO, PRETO);printf("    [* JOGAR NOVAMENTE: 'J' *]");
                textColor(VERMELHO, PRETO);printf("    [* SAIR: 'S' *]\n"); textColor(CINZACLARO, PRETO);
                do{
                    printf("--> ");
                    i=1;
                    fim = getchar();
                    fflush(stdin);
                    switch(fim){
                        case 'S' : return 0;
                        case 'J' : i=0; continuar=0; modos[3]=1; speed=0; clear(); break;
                        case 'P' : ver_pontuacao(nome_digitado); break;
                        case 'R' : top_1(); break;
                        default : textColor(VERMELHO, PRETO); printf("Opcao invalida, tente novamente!\n"); textColor(CINZACLARO, PRETO);
                    }                
                }while(i);
            }
        }while(continuar);
    }while(modos[3]==1);
}

//funções
void ASCII(int texto){
    switch (texto){
        case GAMEOVER :
            printf("[*-------------------------------------------------[ ]: ]-----------------------------------------------]*\n"); Sleep(100); textColor(VERMELHO, PRETO);
            printf("    ________  ________  _____ ______   _______           ________  ___      ___ _______   ________     \n"); Sleep(100); 
            printf("   |\\   ____\\|\\   __  \\|\\   _ \\  _   \\|\\  ___ \\         |\\   __  \\|\\  \\    /  /|\\  ___ \\ |\\   __  \\    \n"); Sleep(100);
            printf("   \\ \\  \\___|\\ \\  \\|\\  \\ \\  \\\\\\__\\ \\  \\ \\   __/|        \\ \\  \\|\\  \\ \\  \\  /  / | \\   __/|\\ \\  \\|\\  \\   \n"); Sleep(100);
            printf("    \\ \\  \\  __\\ \\   __  \\ \\  \\\\|__| \\  \\ \\  \\_|/__       \\ \\  \\\\\\  \\ \\  \\/  / / \\ \\  \\_|/_\\ \\   _  _\\  \n"); Sleep(100);
            printf("     \\ \\  \\|\\  \\ \\  \\ \\  \\ \\  \\    \\ \\  \\ \\  \\_|\\ \\       \\ \\  \\\\\\  \\ \\    / /   \\ \\  \\_|\\ \\ \\  \\\\  \\| \n"); Sleep(100);
            printf("      \\ \\_______\\ \\__\\ \\__\\ \\__\\    \\ \\__\\ \\_______\\       \\ \\_______\\ \\__/ /     \\ \\_______\\ \\__\\\\ _\\ \n"); Sleep(100);
            printf("       \\|_______|\\|__|\\|__|\\|__|     \\|__|\\|_______|        \\|_______|\\|__|/       \\|_______|\\|__|\\|__|\n\n"); Sleep(100);textColor(CINZACLARO, PRETO);
            break;

        case NEWRECORD :
            printf("[*-------------------------------------------------[ [: ]-----------------------------------------------*]\n"); Sleep(100); textColor(VERMELHOCLARO, PRETO);
            printf(" ________   _______   ___       __           ________  _______   ________  ________  ________  ________     \n"); Sleep(100); textColor(VERMELHO, PRETO);
            printf("|\\   ___  \\|\\  ___ \\ |\\  \\     |\\  \\        |\\   __  \\|\\  ___ \\ |\\   ____\\|\\   __  \\|\\   __  \\|\\   ___ \\    \n"); Sleep(100); textColor(AMARELO, PRETO);
            printf("\\ \\  \\\\ \\  \\ \\   __/|\\ \\  \\    \\ \\  \\       \\ \\  \\|\\  \\ \\   __/|\\ \\  \\___|\\ \\  \\|\\  \\ \\  \\|\\  \\ \\  \\_|\\ \\   \n"); Sleep(100); textColor(VERDECLARO, PRETO);
            printf(" \\ \\  \\\\ \\  \\ \\  \\_|/_\\ \\  \\  __\\ \\  \\       \\ \\   _  _\\ \\  \\_|/_\\ \\  \\    \\ \\  \\\\\\  \\ \\   _  _\\ \\  \\ \\\\ \\  \n"); Sleep(100); textColor(VERDE, PRETO);
            printf("  \\ \\  \\\\ \\  \\ \\  \\_|\\ \\ \\  \\|\\__\\_\\  \\       \\ \\  \\\\  \\\\ \\  \\_|\\ \\ \\  \\____\\ \\  \\\\\\  \\ \\  \\\\  \\\\ \\  \\_\\\\ \\ \n"); Sleep(100); textColor(AZULCLARO, PRETO);
            printf("   \\ \\__\\\\ \\__\\ \\_______\\ \\____________\\       \\ \\__\\\\ _\\\\ \\_______\\ \\_______\\ \\_______\\ \\__\\\\ _\\\\ \\_______\\\n"); Sleep(100); textColor(AZUL, PRETO);
            printf("    \\|__| \\|__|\\|_______|\\|____________|        \\|__|\\|__|\\|_______|\\|_______|\\|_______|\\|__|\\|__|\\|_______|\n\n"); Sleep(100); textColor(CINZACLARO, PRETO);
            break;
        
        case FAIL :
            printf("[*-------------------------------------------------[ ]: ]----------------------------------------------*]\n"); Sleep(250); textColor(VERMELHO, PRETO);
            printf("                         ________         ______                ______           \n"); Sleep(250);
            printf("                        |\\  _____\\       |\\___   \\  ___        |\\___   \\  ___    \n"); Sleep(250);
            printf("                        \\ \\  \\__/        \\|___|\\  \\|\\__\\       \\|___|\\  \\|\\__\\   \n"); Sleep(250);
            printf("                         \\ \\   __\\            \\ \\  \\|__|            \\ \\  \\|__|   \n"); Sleep(250);
            printf("                          \\ \\  \\_|            _\\_\\  \\  ___          _\\_\\  \\  ___ \n"); Sleep(250);
            printf("                           \\ \\__\\            |\\______\\|\\__\\        |\\______\\|\\__\\\n"); Sleep(250);
            printf("                            \\|__|            \\|______|\\|__|        \\|______|\\|__|\n\n"); Sleep(250); textColor(CINZACLARO, PRETO);
            printf("[*--------------------------------------------[ VOCE PERDEU ]-------------------------------------------*]\n"); Sleep(250); 
            break;

        case MOREPOINT : 
            printf("[*-------------------------------------------------------------------------------------------------------*]\n"); textColor(VERDECLARO, PRETO);
            printf("                 ________  ________  ___  ________   _________            ______      \n"); Sleep(100);
            printf("                |\\   __  \\|\\   __  \\|\\  \\|\\   ___  \\|\\___   ___\\      ___|\\___   \\    \n"); Sleep(100);
            printf("                \\ \\  \\|\\  \\ \\  \\|\\  \\ \\  \\ \\  \\\\ \\  \\|___ \\  \\_|     |\\__\\|___|\\  \\   \n"); Sleep(100);
            printf("                 \\ \\   ____\\ \\  \\\\\\  \\ \\  \\ \\  \\\\ \\  \\   \\ \\  \\      \\|__|    \\ \\  \\  \n"); Sleep(100);
            printf("                  \\ \\  \\___|\\ \\  \\\\\\  \\ \\  \\ \\  \\\\ \\  \\   \\ \\  \\         ___  _\\_\\  \\ \n"); Sleep(100);
            printf("                   \\ \\__\\    \\ \\_______\\ \\__\\ \\__\\\\ \\__\\   \\ \\__\\       |\\__\\|\\______\\\n"); Sleep(100);
            printf("                    \\|__|     \\|_______|\\|__|\\|__| \\|__|    \\|__|       \\|__|\\|______|\n\n"); Sleep(100); textColor(CINZACLARO, PRETO);
            break;

        case ENTERTEXT :
            printf("[*-------------------------------------------------------------------------------------------------------*]\n"); textColor(VERDE, PRETO);
            printf(" _______   ________   _________  _______   ________          _________  _______      ___    ___ _________   \n");
            printf("|\\  ___ \\ |\\   ___  \\|\\___   ___\\\\  ___ \\ |\\   __  \\        |\\___   ___\\\\  ___ \\    |\\  \\  /  /|\\___   ___\\ \n");
            printf("\\ \\   __/|\\ \\  \\\\ \\  \\|___ \\  \\_\\ \\   __/|\\ \\  \\|\\  \\       \\|___ \\  \\_\\ \\   __/|   \\ \\  \\/  / ||___ \\  \\_| \n");
            printf(" \\ \\  \\_|/_\\ \\  \\\\ \\  \\   \\ \\  \\ \\ \\  \\_|/_\\ \\   _  _\\           \\ \\  \\ \\ \\  \\_|/__  \\ \\    / /     \\ \\  \\  \n");
            printf("  \\ \\  \\_|\\ \\ \\  \\\\ \\  \\   \\ \\  \\ \\ \\  \\_|\\ \\ \\  \\\\  \\|           \\ \\  \\ \\ \\  \\_|\\ \\  /     \\/       \\ \\  \\ \n");
            printf("   \\ \\_______\\ \\__\\\\ \\__\\   \\ \\__\\ \\ \\_______\\ \\__\\\\ _\\            \\ \\__\\ \\ \\_______\\/  /\\   \\        \\ \\__\\\n");
            printf("    \\|_______|\\|__| \\|__|    \\|__|  \\|_______|\\|__|\\|__|            \\|__|  \\|_______/__/ /\\ __\\        \\|__|\n"); 
            printf("                                                                                    |__|/ \\|__|             \n\n"); textColor(CINZACLARO, PRETO);
            printf("[*-----------------------------------------[* DIGITE O TEXTO! *]----------------------------------------*]\n\n--> ");
            break;

        case DECORATE :
            printf("[*------------------------------------------------------------------------------------------------------*]\n");
            printf("         ________  _______   ________  ________  ________  ________  _________  _______      \n");
            printf("        |\\   ___ \\|\\  ___ \\ |\\   ____\\|\\   __  \\|\\   __  \\|\\   __  \\|\\___   ___\\\\  ___ \\     \n");
            printf("        \\ \\  \\_|\\ \\ \\   __/|\\ \\  \\___|\\ \\  \\|\\  \\ \\  \\|\\  \\ \\  \\|\\  \\|___ \\  \\_\\ \\   __/|    \n");
            printf("         \\ \\  \\ \\\\ \\ \\  \\_|/_\\ \\  \\    \\ \\  \\\\\\  \\ \\   _  _\\ \\   __  \\   \\ \\  \\ \\ \\  \\_|/__  \n");
            printf("          \\ \\  \\_\\\\ \\ \\  \\_|\\ \\ \\  \\____\\ \\  \\\\\\  \\ \\  \\\\  \\\\ \\  \\ \\  \\   \\ \\  \\ \\ \\  \\_|\\ \\ \n");
            printf("           \\ \\_______\\ \\_______\\ \\_______\\ \\_______\\ \\__\\\\ _\\\\ \\__\\ \\__\\   \\ \\__\\ \\ \\_______\\\n");
            printf("            \\|_______|\\|_______|\\|_______|\\|_______|\\|__|\\|__|\\|__|\\|__|    \\|__|  \\|_______|\n\n");
            printf("[*-----------------------------------------[* DECORE O TEXTO! *]----------------------------------------*]\n\n");
            break;

        case SETTINGS : 
            printf("[*--------------------------------------[* MODO DE JOGO DEFINDO *]--------------------------------------*]\n\n"); Sleep(100); textColor(AZULCLARO, PRETO);
            printf("             ________  _______  _________  _________  ___  ________   ________  ________      \n"); Sleep(100);
            printf("            |\\   ____\\|\\  ___ \\|\\___   ___\\\\___   ___\\\\  \\|\\   ___  \\|\\   ____\\|\\   ____\\     \n"); Sleep(100);
            printf("            \\ \\  \\___|\\ \\   __/\\|___ \\  \\_\\|___ \\  \\_\\ \\  \\ \\  \\\\ \\  \\ \\  \\___|\\ \\  \\___|_    \n"); Sleep(100);
            printf("             \\ \\_____  \\ \\  \\_|/__  \\ \\  \\     \\ \\  \\ \\ \\  \\ \\  \\\\ \\  \\ \\  \\  __\\ \\_____  \\   \n"); Sleep(100);
            printf("              \\|____|\\  \\ \\  \\_|\\ \\  \\ \\  \\     \\ \\  \\ \\ \\  \\ \\  \\\\ \\  \\ \\  \\|\\  \\|____|\\  \\  \n"); Sleep(100);
            printf("                ____\\_\\  \\ \\_______\\  \\ \\__\\     \\ \\__\\ \\ \\__\\ \\__\\\\ \\__\\ \\_______\\____\\_\\  \\ \n"); Sleep(100);
            printf("               |\\_________\\|_______|   \\|__|      \\|__|  \\|__|\\|__| \\|__|\\|_______|\\_________\\\n"); Sleep(100);
            printf("               \\|_________|                                                       \\|_________|\n\n"); Sleep(100); textColor(CINZACLARO, PRETO);                
            printf("[*------------------------------------------[* CONFIGURACOES *]-----------------------------------------*]\n"); Sleep(100);
            break;

        case ENDLESS :
            printf("[*--------------------------------------[* MODO DE JOGO DEFINDO *]--------------------------------------*]\n\n"); Sleep(100); textColor(VERMELHO, PRETO);
            printf("             _______   ________   ________  ___       _______   ________   ________      \n"); Sleep(100);
            printf("            |\\  ___ \\ |\\   ___  \\|\\   ___ \\|\\  \\     |\\  ___ \\ |\\   ____\\ |\\   ____\\     \n"); Sleep(100);
            printf("            \\ \\   __/|\\ \\  \\\\ \\  \\ \\  \\_|\\ \\ \\  \\    \\ \\   __/|\\ \\  \\___|_\\ \\  \\___|_    \n"); Sleep(100);
            printf("             \\ \\  \\_|/_\\ \\  \\\\ \\  \\ \\  \\\\\\ \\ \\  \\    \\ \\  \\_|/_\\ \\_____  \\\\ \\_____  \\   \n"); Sleep(100);
            printf("              \\ \\  \\_|\\ \\ \\  \\\\ \\  \\ \\  \\\\\\ \\ \\  \\____\\ \\  \\_|\\ \\|____|\\  \\\\|____|\\  \\  \n"); Sleep(100);
            printf("               \\ \\_______\\ \\__\\\\ \\__\\ \\_______\\ \\_______\\ \\_______\\____\\_\\  \\ ____\\_\\  \\ \n"); Sleep(100);
            printf("                \\|_______|\\|__| \\|__|\\|_______|\\|_______|\\|_______|\\_________\\\\_________\\\n"); Sleep(100);
            printf("                                                                  \\|_________\\|_________|\n\n"); Sleep(100); textColor(CINZACLARO, PRETO);
            printf("[*-----------------------------------[* JOGO COMECA EM 5 SEGUNDOS!! *]----------------------------------*]\n"); Sleep(100);
            break;

        case TYPEGAME : 
            printf("[*--------------------------------------------------------------------------------------*]\n\n"); Sleep(100); textColor(VERMELHOCLARO, PRETO);    
            printf(" _________    ___    ___ ________  _______           ________  ________  _____ ______   _______      \n"); Sleep(100); textColor(VERMELHO, PRETO);
            printf("|\\___   ___\\ |\\  \\  /  /|\\   __  \\|\\  ___ \\         |\\   ____\\|\\   __  \\|\\   _ \\  _   \\|\\  ___ \\     \n"); Sleep(100); textColor(AMARELO, PRETO);
            printf("\\|___ \\  \\_| \\ \\  \\/  / | \\  \\|\\  \\ \\   __/|        \\ \\  \\___|\\ \\  \\|\\  \\ \\  \\\\\\__\\ \\  \\ \\   __/|    \n"); Sleep(100); textColor(VERDECLARO, PRETO);
            printf("     \\ \\  \\   \\ \\    / / \\ \\   ____\\ \\  \\_|/__       \\ \\  \\  __\\ \\   __  \\ \\  \\\\|__| \\  \\ \\  \\_|/__  \n"); Sleep(100); textColor(VERDE, PRETO);
            printf("      \\ \\  \\   \\/  /  /   \\ \\  \\___|\\ \\  \\_|\\ \\       \\ \\  \\|\\  \\ \\  \\ \\  \\ \\  \\    \\ \\  \\ \\  \\_|\\ \\ \n"); Sleep(100); textColor(AZULCLARO, PRETO);
            printf("       \\ \\__\\__/  / /      \\ \\__\\    \\ \\_______\\       \\ \\_______\\ \\__\\ \\__\\ \\__\\    \\ \\__\\ \\_______\\\n"); Sleep(100); textColor(AZULCLARO, PRETO);
            printf("        \\|__|\\___/ /        \\|__|     \\|_______|        \\|_______|\\|__|\\|__|\\|__|     \\|__|\\|_______|\n"); Sleep(100); textColor(AZUL, PRETO);
            printf("            \\|___|/                                                                  \n\n"); Sleep(100); textColor(CINZACLARO, PRETO);
            printf("[*------------------------------------------------------------------------------------------------------*]\n\n"); Sleep(150);
            break;

        case SIGNIN :
            printf("[*-----------------------------------------------------------------------------------------------------*]\n"); textColor(VERDECLARO, PRETO);
            printf("                     ________  ___  ________  ________           ___  ________      \n");
            printf("                    |\\   ____\\|\\  \\|\\   ____\\|\\   ___  \\        |\\  \\|\\   ___  \\    \n");
            printf("                    \\ \\  \\___|\\ \\  \\ \\  \\___|\\ \\  \\\\ \\  \\       \\ \\  \\ \\  \\\\ \\  \\   \n");
            printf("                     \\ \\_____  \\ \\  \\ \\  \\  __\\ \\  \\\\ \\  \\       \\ \\  \\ \\  \\\\ \\  \\  \n");
            printf("                      \\|____|\\  \\ \\  \\ \\  \\|\\  \\ \\  \\\\ \\  \\       \\ \\  \\ \\  \\\\ \\  \\ \n");
            printf("                        ____\\_\\  \\ \\__\\ \\_______\\ \\__\\\\ \\__\\       \\ \\__\\ \\__\\\\ \\__\\\n");
            printf("                       |\\_________\\|__|\\|_______|\\|__| \\|__|        \\|__|\\|__| \\|__|\n");
            printf("                       \\|_________|                                                 \n"); textColor(CINZACLARO, PRETO);
            printf("[*----------------------------------------------[* LOGIN *]--------------------------------------------*]\n\n");
            break;

        case STARTUP :
            printf("[*-----------------------------------------------------------------------------------------------------*]\n"); textColor(VERDECLARO, PRETO);
            printf("                 ________  _________  ________  ________  _________  ___  ___  ________   \n");
            printf("                |\\   ____\\|\\___   ___\\\\   __  \\|\\   __  \\|\\___   ___\\\\  \\|\\  \\|\\   __  \\  \n");
            printf("                \\ \\  \\___|\\|___ \\  \\_\\ \\  \\|\\  \\ \\  \\|\\  \\|___ \\  \\_\\ \\  \\\\\\  \\ \\  \\|\\  \\ \n");
            printf("                 \\ \\_____  \\   \\ \\  \\ \\ \\   __  \\ \\   _  _\\   \\ \\  \\ \\ \\  \\\\\\  \\ \\   ____\\\n");
            printf("                  \\|____|\\  \\   \\ \\  \\ \\ \\  \\ \\  \\ \\  \\\\  \\|   \\ \\  \\ \\ \\  \\\\\\  \\ \\  \\___|\n");
            printf("                    ____\\_\\  \\   \\ \\__\\ \\ \\__\\ \\__\\ \\__\\\\ _\\    \\ \\__\\ \\ \\_______\\ \\__\\   \n");
            printf("                   |\\_________\\   \\|__|  \\|__|\\|__|\\|__|\\|__|    \\|__|  \\|_______|\\|__|   \n");
            printf("                   \\|_________|                                                          \n"); textColor(CINZACLARO, PRETO);
            printf("[*------------------------------------------[* INICIALIZACAO *]----------------------------------------*]\n\n");
            break;

        case SIGNUP :
            printf("[*-----------------------------------------------------------------------------------------------------*]\n"); textColor(AMARELO, PRETO);
            printf("                     ________  ___  ________  ________           ___  ___  ________   \n");
            printf("                    |\\   ____\\|\\  \\|\\   ____\\|\\   ___  \\        |\\  \\|\\  \\|\\   __  \\  \n");
            printf("                    \\ \\  \\___|\\ \\  \\ \\  \\___|\\ \\  \\\\ \\  \\       \\ \\  \\\\\\  \\ \\  \\|\\  \\ \n");
            printf("                     \\ \\_____  \\ \\  \\ \\  \\  __\\ \\  \\\\ \\  \\       \\ \\  \\\\\\  \\ \\   ____\\\n");
            printf("                      \\|____|\\  \\ \\  \\ \\  \\|\\  \\ \\  \\\\ \\  \\       \\ \\  \\\\\\  \\ \\  \\___|\n");
            printf("                        ____\\_\\  \\ \\__\\ \\_______\\ \\__\\\\ \\__\\       \\ \\_______\\ \\__\\   \n");
            printf("                       |\\_________\\|__|\\|_______|\\|__| \\|__|        \\|_______|\\|__|   \n");
            printf("                       \\|_________|                                                    \n"); textColor(CINZACLARO, PRETO);
            printf("[*---------------------------------------------[* CADASTRO *]------------------------------------------*]\n\n");
            break;
        
        case TIMEOVER :
            printf("[*-----------------------------------------------------------------------------------------------------*]\n"); Sleep(100); textColor(VERMELHO, PRETO);
            printf("     _________  ___  _____ ______   _______           ________  ___      ___ _______   ________     \n"); Sleep(100);
            printf("    |\\___   ___\\\\  \\|\\   _ \\  _   \\|\\  ___ \\         |\\   __  \\|\\  \\    /  /|\\  ___ \\ |\\   __  \\    \n"); Sleep(100);
            printf("    \\|___ \\  \\_\\ \\  \\ \\  \\\\\\__\\ \\  \\ \\   __/|        \\ \\  \\|\\  \\ \\  \\  /  / | \\   __/|\\ \\  \\|\\  \\   \n"); Sleep(100);
            printf("         \\ \\  \\ \\ \\  \\ \\  \\\\\\|__| \\  \\ \\  \\_|/__       \\ \\  \\\\\\  \\ \\  \\/  / / \\ \\  \\_|/_\\ \\   _  _\\  \n"); Sleep(100);
            printf("          \\ \\  \\ \\ \\  \\ \\  \\    \\ \\  \\ \\  \\_|\\ \\       \\ \\  \\\\\\  \\ \\    / /   \\ \\  \\_|\\ \\ \\  \\\\  \\| \n"); Sleep(100);
            printf("           \\ \\__\\ \\ \\__\\ \\__\\    \\ \\__\\ \\_______\\       \\ \\_______\\ \\__/ /     \\ \\_______\\ \\__\\\\ _\\ \n"); Sleep(100);
            printf("            \\|__|  \\|__|\\|__|     \\|__|\\|_______|        \\|_______|\\|__|/       \\|_______|\\|__|\\|__|\n"); Sleep(100); textColor(CINZACLARO, PRETO);
            printf("[*-----------------------------------------------------------------------------------------------------*]\n"); Sleep(100);
            break;

        case MAX :
            printf("[*-----------------------------------------------------------------------------------------------------*]\n"); Sleep(100); textColor(VERMELHO, PRETO);
            printf("     _____ ______   ________     ___    ___      ________  ___  ________ ________ ___  ________     \n"); Sleep(100);
            printf("    |\\   _ \\  _   \\|\\   __  \\   |\\  \\  /  /|    |\\   ___ \\|\\  \\|\\  _____\\\\  _____\\\\  \\|\\   ____\\    \n"); Sleep(100);
            printf("    \\ \\  \\\\\\__\\ \\  \\ \\  \\|\\  \\  \\ \\  \\/  / /    \\ \\  \\_|\\ \\ \\  \\ \\  \\__/\\ \\  \\__/\\ \\  \\ \\  \\___|    \n"); Sleep(100);
            printf("     \\ \\  \\\\|__| \\  \\ \\   __  \\  \\ \\    / /      \\ \\  \\ \\\\ \\ \\  \\ \\   __\\\\ \\   __\\\\ \\  \\ \\  \\       \n"); Sleep(100);
            printf("      \\ \\  \\    \\ \\  \\ \\  \\ \\  \\  /     \\/        \\ \\  \\_\\\\ \\ \\  \\ \\  \\_| \\ \\  \\_| \\ \\  \\ \\  \\____  \n"); Sleep(100);
            printf("       \\ \\__\\    \\ \\__\\ \\__\\ \\__\\/  /\\   \\         \\ \\_______\\ \\__\\ \\__\\   \\ \\__\\   \\ \\__\\ \\_______\\\n"); Sleep(100);
            printf("        \\|__|     \\|__|\\|__|\\|__/__/ /\\ __\\         \\|_______|\\|__|\\|__|    \\|__|    \\|__|\\|_______|\n"); Sleep(100);
            printf("                                |__|/ \\|__|                                                  \n"); Sleep(100); textColor(CINZACLARO, PRETO);
            printf("[*-----------------------------------------------------------------------------------------------------*]\n"); Sleep(100); Sleep(100);
            break;

        case VIDA :
            printf("[*-----------------------------------------------------------------------------------------------------*]\n"); Sleep(100); textColor(AMARELO, PRETO);
            printf("                    _____          ___       ___  ________ _______               ______      \n"); Sleep(100);
            printf("                   / __  \\        |\\  \\     |\\  \\|\\  _____\\\\  ___ \\          ___|\\   ___\\    \n"); Sleep(100);
            printf("     ____________ |\\/_|\\  \\       \\ \\  \\    \\ \\  \\ \\  \\__/\\ \\   __/|        |\\__\\ \\  \\__|    \n"); Sleep(100);
            printf("    |\\____________\\|/ \\ \\  \\       \\ \\  \\    \\ \\  \\ \\   __\\\\ \\  \\_|/__      \\|__|\\ \\  \\      \n"); Sleep(100);
            printf("    \\|____________|    \\ \\  \\       \\ \\  \\____\\ \\  \\ \\  \\_| \\ \\  \\_|\\ \\         __\\ \\  \\____ \n"); Sleep(100);
            printf("                        \\ \\__\\       \\ \\_______\\ \\__\\ \\__\\   \\ \\_______\\       |\\__\\ \\______\\\n"); Sleep(100);
            printf("                         \\|__|        \\|_______|\\|__|\\|__|    \\|_______|       \\|__|\\|______|\n"); Sleep(100); textColor(CINZACLARO, PRETO);
            printf("[*-----------------------------------------------------------------------------------------------------*]\n"); Sleep(100); Sleep(100);

        default:
            break;
    }
}

void clear(){
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}

void textColor(int letras, int fundo){
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), letras + fundo*16);
}

void *musicIntro(){
    Beep(247, 500); Beep(417, 500); Beep(417, 500); Beep(370, 500); Beep(417, 500); Beep(329, 500); Beep(247, 500); 
    Beep(247, 500); Beep(247, 500); Beep(417, 500); Beep(417, 500); Beep(370, 500); Beep(417, 500); Beep(497, 500);
    Sleep(500);
    Beep(497, 500); Beep(277, 500); Beep(277, 500); Beep(440, 500); Beep(440, 500); Beep(417, 500); Beep(370, 500);
    Beep(329, 500); Beep(247, 500); Beep(417, 500); Beep(417, 500); Beep(370, 500); Beep(417, 500);Beep(329, 500);
    return NULL;
}

void *cronometro(){
    int i;
    for(i=0; i<16 && pararcronometro==0; i++){             
        //printf("%d - ", i);
        Sleep(1000);
        tempocronometro=i;
    }
    if (tempocronometro==15){
        clear();
        ASCII(TIMEOVER);
        printf("\t\t\t [* TEMPO LIMITE ATINGIDO, aperte enter para continuar... *]");
    }
    return NULL;
}

int comparar_string(char str_resultado[], char str_digitada[]){
    int i;

    for (i=0; str_resultado[i] != '\0' || str_digitada[i] != '\0'; i++){        
        if (str_resultado[i] != str_digitada[i]){
            //printf("Nao igual %c:%d - %c \n", str_resultado[i], i, string_digitada[i]);
            return 0;
        }
        //printf("Igual %c - %c\n", str_resultado[i], string_digitada[i]);
    }
    return 1;
} 

void copiar_string(char *entrada, char *saida){
    int i;

    for(i=0; entrada[i]!='\0'; i++){
        saida[i] = entrada[i]; 
    }
    saida[i]='\0';
}

void remover_enter(char str[]){
    int i;

    for(i=0; str[i]!='\0'; i++){
        if (str[i]=='\n'){
            str[i]='\0';
            //printf("removeu\n");
        }
    }
}

int atualizar_data(int score, char nome[]){
    dataTem dataT; dataTem dataH;
    FILE *datafile = fopen("Data.txt", "r");
    FILE *tmpdatafile = fopen("TmpData.txt", "w");

    if(datafile){
        int newrecord=0;
        while(fscanf(datafile, "%s %d %d", dataT.nome, &dataT.senha, &dataT.score)!=EOF){
            if(comparar_string(dataT.nome, nome)){
                if(dataT.score < score){
                    dataT.score = score;
                    newrecord=1;
                    //printf("\nNEW RECORD!!!\n");
                }
            }
            fprintf(tmpdatafile, "%s %d %d\n", dataT.nome, dataT.senha, dataT.score);
        }

        fclose(datafile);
        fclose(tmpdatafile);

        remove("Data.txt");
        rename("TmpData.txt", "Data.txt");
        if(newrecord==1)
            return 1;
    }
    else{
        printf("Falha ao abrir o arquivo");
    }
}

void top_1(){
    dataTem dataT, tmp ,maior;
    FILE *datafile = fopen("Data.txt", "r");
    FILE *tmpfile = fopen("TmpData.txt", "w+");

    if(datafile && tmpfile){
        while(fscanf(datafile, "%s %d %d", dataT.nome, &dataT.senha, &dataT.score)!=EOF){
            fprintf(tmpfile, "%s %d %d\n", dataT.nome, dataT.senha, dataT.score);
        }
        rewind(datafile);
        rewind(tmpfile);

        fscanf(datafile, "%s %d %d", dataT.nome, &dataT.senha, &dataT.score);
        maior.score = dataT.score;
        copiar_string(dataT.nome, maior.nome);
        
        while(fscanf(tmpfile, "%s %d %d", tmp.nome, &tmp.senha, &tmp.score)!=EOF){
            if(tmp.score > maior.score){
                //printf("%d - %d\n", tmp.score, dataT.score);
                maior.score = tmp.score;
                copiar_string(tmp.nome, maior.nome);
            }
        }

        fclose(datafile);
        fclose(tmpfile);
        remove("TmpData.txt");

        printf("USUARIO: %s  SCORE: %d\n\n", maior.nome, maior.score);
    }
    else
        printf("Falha ao abrir o arquivo");
}

void ler_data(){
    dataTem dataT;
    int i;
    FILE *datafile = fopen("Data.txt", "r");
    if(datafile){ 
        while(fscanf(datafile, "%s %d %d",dataT.nome ,&dataT.senha, &dataT.score)!=EOF){
            printf("usuario: %s, senha: %d, score: %d\n", dataT.nome, dataT.senha, dataT.score);
        }
        fclose(datafile);
        printf("\n");
    }
    else{
        printf("Falha ao abrir o arquivo");
    }
}

int escrever_data(){
    dataTem dataT, dataH;
    FILE *datafile = fopen("Data.txt", "r+");
    int continuar;

    if (datafile){
        do{
            continuar=0;
            printf("\t\t\t\t    [* DIGITE SEU USUARIO(s/espaco): *]\n--> ");
            fgets(dataT.nome, sizeof(dataT.nome), stdin);
            remover_enter(dataT.nome);
            rewind(datafile);

            //verifica se já tem o usuario
            while(fscanf(datafile, "%s %d %d", dataH.nome, &dataH.senha, &dataH.score)!=EOF){
                if (comparar_string(dataT.nome, dataH.nome)==1){
                    printf("Usuario ja cadastrado!\n\n");
                    continuar=1;
                }
            }
            fflush(stdin);
        }while(continuar);

        printf("\t\t\t\t   [* DIGITE SUA SENHA(apenas nums): *]\n--> ");
        scanf("%d", &dataT.senha);
        fflush(stdin);

        dataT.score = 0;
        fprintf(datafile, "%s %d %d\n", dataT.nome, dataT.senha, dataT.score);
        fclose(datafile); 
        return 1;        
    }
    else{
        printf("Falha ao abrir o arquivo");
    }
}

int buscar_data(char nome_digitado[], int senha_digitada){
    dataTem dataT;
    FILE *datafile = fopen("Data.txt", "r"); 
    if(datafile){ 
        while(fscanf(datafile, "%s %d %d", dataT.nome, &dataT.senha, &dataT.score)!=EOF){
            //printf("\n%s %d %d\n\n",dataT.nome, dataT.senha, dataT.score);
            if (comparar_string(nome_digitado, dataT.nome)==1 && dataT.senha==senha_digitada){
                fclose(datafile);
                return 1;
            }
        }
        fclose(datafile);
        textColor(VERMELHO, PRETO);
        printf("Usuario ou senha incorreta\n");
        textColor(CINZACLARO, PRETO);
        return 0;
    }
    else{
        printf("Falha ao abrir o arquivo"); 
        return 0;
    }
}

void ver_pontuacao(char nome[]){
    dataTem dataT;
    FILE *datafile = fopen("Data.txt", "r");

    if(datafile){
        while(fscanf(datafile ,"%s %d %d", dataT.nome, &dataT.senha, &dataT.score)!=EOF){
            if(comparar_string(dataT.nome, nome)==1){
                printf("Melhor Pontuacao: %d\n\n", dataT.score);
            }
        }
        fclose(datafile);
    }
    else
        printf("Falha ao abrir o arquivo");
}

void *escolher_palavra(int qnt_palavra, int *num_aleatorio, int modos[]){
    srand(time(NULL));
    int i;
    if (modos[2]==1){
        for (i=0; i<qnt_palavra; i++){    
            num_aleatorio[i] = rand() % 10;  
        }
    } 
    if(modos[2]==2){
        for (i=0; i<qnt_palavra; i++){
            do{    
                num_aleatorio[i] = rand() % 20;
            }while(num_aleatorio[i]<10);
            //printf("%d", num_aleatorio[i]);
        }
    }
    if (modos[2]==3){
        for (i=0; i<qnt_palavra; i++){    
            num_aleatorio[i] = rand() % 20;  
        }
    } 
}

char *gerar_palavra(int qnt_palavra, char *str_resultado, int modos[]){
    int i, j, x, num_aleatorio[20];
    int *ptr = num_aleatorio;

    char palavras[][20+1] = {
        {"Povo"},
        {"Brasileiro"},
        {"Pessoa"},
        {"Pais"},
        {"Indigena"},
        {"Futebol"},
        {"Redentor"},
        {"Samba"},
        {"Carnaval"},
        {"Floresta"},
    // ----------------------------------------- 
        {"Quadro"},
        {"Professor"},
        {"Pincel"},
        {"Mesa"},
        {"Aluno"},
        {"Projetor"},
        {"Cadeira"},
        {"Apagador"},
        {"Mochila"},
        {"Leonardo"}
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