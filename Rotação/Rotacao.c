#include <stdio.h>
#include <math.h>
#include <string.h>
#include <Windows.h>
#define PI 3.14
#define TAM 360
#define DIM 200 

enum cores {PRETO,AZUL,VERDE,CIANO,VERMELHO,MAGENTA,MARROM,CINZACLARO,CINZAESCURO,AZULCLARO,VERDECLARO,CIANOCLARO,VERMELHOCLARO,MAGENTACLARO,AMARELO,BRANCO};
void textColor(int letras, int fundo){
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), letras + fundo*16);
}

void main(){
    int i, j, k, l, cordenadas[TAM*2+1], pontos[TAM][2], x=1, y=1;
    float rotacao=0;

    for(k=0; k<TAM*2; rotacao+=1 * PI/180){
        float rot[2][2] = {{cos(rotacao), -sin(rotacao)},{sin(rotacao), cos(rotacao)}};
        float mat[2][1] = {{x}, {y}};  
        float resultado[2+1] = {0,0};

        for(i=0; i<2; i++){
            for(j=0; j<2; j++){
                resultado[j] = rot[i][j]*mat[j][0];
                //printf("%.2f\n", resultado[j]);
            }  
            //printf("%f\n", resultado[0]*10 + resultado[1]*10);
            int resultado2 = (int) round(resultado[0]*70+50) + (int) round(resultado[1]*70+50);
            cordenadas[k] = resultado2;
            k++;
        }
        //printf("\n");
    }
    
    for(i=0, k=0; i<TAM; i++){
        //printf("%d ", cordenadas[i]);
        for(j=0; j<2; j++, k++){
            pontos[i][j] = cordenadas[k];
        }
    }

    for(i=0; i<TAM; i++){
        for(j=0; j<2; j++){
            printf("%d ", pontos[i][j]);
        }
        printf("\n");
    }

    printf("\n");
    int achou;
    for(i=0; i<DIM; i++){
        for(j=0; j<DIM; j++){
                achou=0;
                for(k=0; k<TAM; k++){
                    if (pontos[k][0]==j && pontos[k][1]==i){
                        textColor(PRETO, AZULCLARO);
                        printf("  ");
                        textColor(PRETO, PRETO);
                        achou=1;
                    }
                }
                if(achou==1)
                    continue;

                if (j==DIM-1){
                    printf("  \n");
                    continue;
                }
                printf("  ");
        }
    }
}