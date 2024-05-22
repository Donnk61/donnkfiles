#include <stdio.h>
#include <time.h>
#include <stdlib.h>

#define DIM 7

int *gerarnum(int num_definido, int *num_aleatorio){
  srand(time(NULL));
  int i, j, nao_igual;

  do{
    nao_igual = 0;
    for (i=0; i<num_definido; i++){
      int num_gerado;   

      num_gerado = rand() % 49 + 1;
      num_aleatorio[i] = num_gerado;
      //printf("num gerado: %d\n", num_aleatorio[i]);
    }

    for (i=0; i<num_definido; i++){
      int indice;

      for(j=0; j<num_definido; j++){
        if(i == j)
          continue;
        if(num_aleatorio[i] == num_aleatorio[j]){
          nao_igual = 1;
          //printf("num repetido: %d - %d\n", num_aleatorio[i], num_aleatorio[j]);
        }
      }
    }
    
  }while(nao_igual==1);  

  printf("------------------------\n");
  return num_aleatorio;
}

int checar_num(int i,int *num_aleatorio, int num_definido){
    int x;
    for (x=0; x<num_definido; x++){
      if(i==num_aleatorio[x]){      
        return 1;
      }
    } 
    return 0;
}

int main(){
  int i, j, x, num=1, num_aleatorio[DIM*DIM], mat[DIM][DIM], num_definido;

  printf("Digite o numero de apostas(1 a 15): ");
  do{
    scanf("%d", &num_definido);
  }while(num_definido > 15 || num_definido <= 0);

  gerarnum(num_definido, num_aleatorio);

  for(i=0; i<DIM; i++){
    for(j=0; j<DIM; j++, num++){
      mat[i][j] = num;

      if(checar_num(num, num_aleatorio, num_definido)==1){
        printf("XX ");
      }
      else{
        printf("%2.d ", num);
      }
    }
      printf("\n"); 
  }

  return 0;
}
