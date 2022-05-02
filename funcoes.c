#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include "header.h"

//Conectar ao header para tudo o que fizer aqui, fica tudo ligado ao main

int quantidadeJobs(Job * jp) {
  int soma = 0;
  while (jp != NULL) {
    jp = jp -> seguinte;
    soma++;
  }
  return (soma);
}

int quantidadeOperacoes(Operation * op) {
  int soma = 0;
  while (op != NULL) {
    op = op -> seguinte;
    soma++;
  }
  return (soma);
}

//Inserir
Job* inserirJobs(Job * jp, int id, int* operacao){

  Job *jb = (Job*) malloc(sizeof(Job));

  if (jb!=NULL)
  {
    jb->id = id;
    //Copiar array
    int sizearrayoperacao=sizeof(operacao);
    for(int h=0;h<sizearrayoperacao;h++){
      jb->operacao[h] = operacao[h] ;
    }
    
    jb->seguinte = jp;
    return(jb);
  }
  else return(jp);
}

//Operação
Operation* inserirOperacoes(Operation * op, int id, int* maq, int* temp, int size){
  Operation *ot = (Operation*) malloc(sizeof(Operation));
  ot->id=id;
  
  //Passa de um array para o outro (maquina)
  for(int i=0; i<size;i++){
    if(maq[i]!=0){
      ot->maquina[i]=maq[i]; 
    } 
  }

  //Passa de um array para o outro (tempo)
  for(int j=0; j<size;j++){
    if(temp[j]!=0){
      ot->tempo[j]=temp[j];

    } 
  }

  ot->sizeMT=size;
  ot->seguinte=NULL;
  if(op == NULL){
    op= ot;
  }else{
    Operation* lastnode = op;
    while(lastnode->seguinte != NULL){
      lastnode = lastnode->seguinte;
    }
    lastnode->seguinte = ot;
  }
  return op;
}

Operation* removerOperacoes(Operation * op, int id){
  
  if( op == NULL) return NULL; //Se nao tiver nenhuma operação, retorna ao menu.

  if(op->id == id){ //remove primeiro
    Operation* aux = op; //aux é a copia da lista. 
    op=op->seguinte; 
    free(aux);
  }
  else{//Remove no meio 
    Operation *aux=op;//copia da lista de op
    Operation *auxAnt = aux;//copia da copia da lista de op (aux aponta pra copia da auxiliar, )
    while(aux && aux->id != id){
      auxAnt=aux;
      aux = aux->seguinte;
    }
    if(aux != NULL){ //Remove no fim
      auxAnt->seguinte= aux->seguinte; //
      free(aux);
    }

  }
  return op;
}

Operation* procuraOperacoes(Operation* op, int id){ //Procura a operação que tiver o id igual ao que inserirmos.
  if(op==NULL) return NULL;
  else{
    Operation* aux = op;
    while(aux != NULL){
      if(aux->id == id){
        return aux;
      }
      aux= aux->seguinte;
    }
    return NULL;
  }
}

Operation* alteraOperacao(Operation* op, int id,int* maq,int* temp,int size){
  Operation* aux = procuraOperacoes(op, id);
  if(aux != NULL){
    aux->sizeMT=size; //altera para o novo size.
    //Insere as maquinas de novo
    //Passa de um array para o outro (maquina)
    for(int i=0; i<size;i++){
    aux->maquina[i]=maq[i]; //iguala as maquinas que estavam na operação sao substituidas pelas maquinas novas que foram adicionadas.
    }

    //Passa de um array para o outro (tempo)
    for(int j=0; j<size;j++){
    aux->tempo[j]=temp[j];
    }

  }
  return op;
}

//Listar
void listarJobs(Job *jp){
  while (jp!=NULL)
 {
    printf("Job n %d\n",jp->id );
    for(int j=0; j<7;j++){
      if(jp->operacao[j]==0) break;
      printf(" Lista de operacoes:%d\n", jp->operacao[j]);
      
    }
    jp = jp->seguinte;
 }
}

void listarOperations(Operation *op){
  while (op!=NULL)
 {
    printf("Operacao n %d\n",op->id );

    //Lista as maquinas que se pode usar 
    printf(" Lista   de  Maquinas:(");
    for(int j=0; j<op->sizeMT;j++){  
      if(j == op->sizeMT){
        printf("%d", op->maquina[j]);
        break;
      }else
          printf("%d,", op->maquina[j]); 
    }
    printf(")\n");

    //Lista o tempo que cada maquina demora
    printf("Tempo de cada Maquina:[");
    for(int j=0; j<op->sizeMT;j++){  
      if(op->tempo[j+1]==0){
        printf("%d", op->tempo[j]);
        break;
      }else
        printf("%d,", op->tempo[j]); 
    }
    printf("]\n");
    printf("Size:%d\n",op->sizeMT);

    op = op->seguinte;
 }
}

//Menu e função que retorna ao menu
int menu(){
    int opcao;

    do{
        printf("---------MENU-------\n");
        printf("1 - Inserir job com operacoes\n");
        printf("2 - Quantidade de jobs\n");
        printf("3 - Listar jobs\n");
        printf("4 - Remover operacao\n");
        printf("5 - Alterar operacao\n");
        printf("6 - Listar operacoes\n");
        printf("7 - Guardar \n");
        printf("8 - Media minima por job\n");
        printf("9 - Media maxima por job\n");
        printf("10 - Inserir operacoes\n");
        printf("0 - Sair\n");
        printf("Opcao:");
        scanf("%d",&opcao); 
    }
    while ((opcao>12)||(opcao<0));
    return(opcao);
}
 //Calculos
void medMinJob(Job *jp,Operation *op){
  int min;
  int incre=0;
  while (jp!=NULL){

    printf("Job n %d tempo minino: \n",jp->id );
    for(int j=0; j<8;j++){
      if(jp->operacao[j]==0) break;
      printf("Operacao n: %d\n",jp->operacao[j]);

     //Função de retornar a operacao min
      min = minOperacao(op,jp->operacao[j]);
      incre += min;
    }
    printf("O minimo de tempo e de %d minutos\n",incre+1);
    jp = jp->seguinte;
 }
}

void medMaxJob(Job *jp,Operation *op){
  int max;
  int incre=0;
  while (jp!=NULL){

    printf("Job n %d tempo maximo:\n",jp->id );
    for(int j=0; j<8;j++){
      if(jp->operacao[j]==0) break;
      printf("Operacao n :%d\n",jp->operacao[j]);

     //Função de retornar a operacao max 
      max = maxOperacao(op,jp->operacao[j]);
      incre += max;
    }
    printf("O maximo de tempo e de %d minutos\n",incre-1);
    jp = jp->seguinte;
 }
}

int minOperacao(Operation *op, int id){ //Soma o tempo minimo de cada operação, soma e da o tempo min do job.
  Operation* aux = procuraOperacoes(op, id);
  int min=100;
  int temp=0;
  //Verifica se é null
  if(aux!=NULL){
    //Lê todos os tempos e guarda o min
    for(int i=0;i<op->sizeMT;i++){
      if(aux->tempo[i] < min){
        min=aux->maquina[i];
        temp=aux->tempo[i];
      }

    }
  } 

  printf("Maquina n %d e a mais rapida\n",min);
  return (temp);  
}
 

int maxOperacao(Operation *op, int id){
  Operation* aux = procuraOperacoes(op, id);
  int max=0;
  int temp=0;

  //Ler todos os tempos 
  if(aux!=NULL){//Verifica se e null
    printf("%d",op->sizeMT);
    for(int i=0;i<op->sizeMT;i++){//Le todos os tempos e guarda o maximo
      if(aux->tempo[i] > max){
        max=aux->maquina[i];
        temp=aux->tempo[i];
      }

    }
  } 

  printf("Maquina n %d e a mais rapida\n",max);
  return (temp);  
} 

