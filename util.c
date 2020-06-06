#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "util.h"

//pulisce l'output
void clrscr(){
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}

//funzione per ottenere le richieste di un singolo carattere in input
char catchRequest()
{
    char richiesta, buf[maxstring];

    while(1){
        
        printf("\nInput: ");
        fgets(buf, maxstring, stdin);

        if (strlen(buf) == 2) {
            richiesta = buf[0];
            break;
        }
        else
            printf("\nInput non valido, inserire un unico carattere\n");
    }
 
    return richiesta;
}

void ese1(){
    time_t t;
    int quit=0;
    int n,e,i;
    char index;
    GraphADJ G;
    int** Matrix;
    int source,target;
    int* ArrayInDegree;
    int inDegree;
    int outDegree;
    clrscr();
    do{
        
        printf("\n--Dato un grafo orientato, calcolare il grado uscente e il grado entrante.");
        printf("Ripetere l'esercizio sia usando una rappresentazione a matrice di adiacenza che con liste di adiacenza--\n");
        
        printf("\n1.Crea grafo con liste di adiacenza\n2.Crea grafo con matrice di adiacenza");
        printf("\n3.Grado uscente ed entrante (lista di adiacenza)\n4.Grado uscente ed entrante (matrice di adiacenza)");
        printf("\n0. Uscita\n");
        index=catchRequest();
        switch(index){
            case '1':
                clrscr();
                
                do{
                    printf("\nInserire numero nodi: (massimo %d nodi) ",maxnodi);
                    scanf("%d",&n);
                    if(n < 1 || n > maxnodi){
                        printf("numero non valido!\n");
                    }
                }while(n < 1 || n > maxnodi);
                
                G=initGraph(n);
                do{
                    printf("\nInserire il numero di archi: (massimo %d archi) ", n*(n-1));
                    scanf("%d",&e);
                    if( e < 1 || e > (n*(n-1)) ){
                        printf("numero non valido!\n");
                    }
                }while( e < 1 || e > (n*(n-1)) );
                srand((unsigned int)time(&t));
                for(i=0;i<e;i++){
                    source=rand()%n;
                    target=rand()%n;
                    if(target == source)
                        target++;
                    if(target == n)
                        target -=2;
                    addEdge(G,source,target,1);

                }

                printf("\nGrafo Creato: \n");
                printGraph(G);
                while(getchar() !='\n');
                break;
            
            case '2':
            
                break;
            
            case '3':
                ArrayInDegree=(int*)malloc(sizeof(int)*G->nv);
                ArrayInDegree = gradiEntranti(G,ArrayInDegree);
                inDegree=MaxInDegree(ArrayInDegree,G->nv);
                outDegree=MaxOutDegree(G);
                printf("\nIn Degree: %d",inDegree);
                printf("\nOut Degree: %d",outDegree);

                break;
            
            case '4':
            
                break;
            
            case '0':
                printf("\nChiusura in corso\n");
                quit=1;
                break;
        
            default:
                printf("\nInput non valido!");
                break;
        }

    }while(quit!=1);

}


void ese2(){
    int quit=0;
}


void ese3(){
    int quit=0;
}


void ese4(){
    int quit=0;
}

