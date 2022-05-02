#include <stdio.h>
#include <stdlib.h>
#include "header.h"

int main()
{
    Job *jobs = NULL;
    Operation * operacoes = NULL; 
     //Cria uma lista predefinida das operações de dos jobs com os respetivos tempos

    int idCount=0;

    int option;
    int aa[MAXOPERATION]={1,2,3};
    int bb[3]={1,2,3};
    int cc[3]={7,4,9};
    int rr[3]={2,6,5};
    int tt[3]={6,5,5};
    int kk[1]={3};
    int ii[1]={5};
    int hh[2]={6,6};
    int qt,qt2=0;
    int idOp=0;

    do{
        option = menu();
        switch(option){
            case 1:
                //Inserir os jobs
                printf("Inserindo Jobs\n");
                jobs=inserirJobs(jobs,1,aa);

                //Insere as seguintes operações de cima
                operacoes= inserirOperacoes(operacoes,1,bb,cc,3);
                operacoes= inserirOperacoes(operacoes,2,rr,tt,3);   
                operacoes= inserirOperacoes(operacoes,3,kk,ii,1);
                break; 
            case 2:
                printf("Quantidade: %d\n", quantidadeJobs(jobs));
                break;
            case 3:
                listarJobs(jobs);
                break;
           case 4:{
                int idRemover=0;
                system("cls");
                printf("-----Remover operacao-----\n\n");
                printf("Qual o id da operacao que deseja remover? ");
                scanf("%d",&idRemover);
                removerOperacoes(operacoes,idRemover);
                break;
            }    
            case 5:{
                int idAlterar=0;
                system("cls");
                printf("-----Alterar Operacao-----\n\n");
                printf("-----Inserir operacoes-----\n");
                printf("Qual o id da operacao que deseja alterar? ");
                scanf("%d",&idAlterar);
                printf("Com quantas maquinas? ");
                scanf("%d",&qt);

                int maq[qt];
                int temp[qt];
                for(int i=0; i<qt; i++){
                    printf("\nMaquina numero: ");
                    scanf("%d",&maq[i]);
                    printf("Tempo da maquina %d: ",i+1);
                    scanf("%d",&temp[i]);
                }
                alteraOperacao(operacoes,idAlterar,maq,temp,qt);
                break;
            }
            case 6:
                system("cls");
                //Lista as operações adicionadas no case 1
                listarOperations(operacoes);
                break;
            case 7:
                //Guardar dados              
                break;
            case 8:
                system("cls");
                printf("-----tempo minimo do job-----\n");
                medMinJob(jobs,operacoes);
                break;
            case 9:
               printf("-----tempo maximo do job-----\n");
                medMaxJob(jobs,operacoes);
                break;
            case 10:{
                //Ve quantas operações já tem inseridas para ter o id correto da que irá ser adicionada
                idCount=quantidadeOperacoes(operacoes);
                idCount++;
                //Inserir operações e ver a quantidade de maquinas
                system("cls");
                printf("-----Inserir operacoes-----\n");
                printf("Quantas maquinas? ");
                scanf("%d",&qt);

                int maq[qt];
                int temp[qt];
                for(int i=0; i<qt; i++){
                    printf("\nMaquina numero: ");
                    scanf("%d",&maq[i]);
                    printf("Tempo da maquina %d: ",i+1);
                    scanf("%d",&temp[i]);
                }
                
                operacoes=inserirOperacoes(operacoes,idCount,maq,temp,qt);

                break; 
            }
            default:
                break;
        }
    }while(option != 0);

    return 0;
}
