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
    int dim;
    int source,target;
    int* ArrayInDegree;
    int inDegree;
    int outDegree;

    clrscr();
    printf("\n--Dato un grafo orientato, calcolare il grado uscente e il grado entrante.");
    printf("Ripetere l'esercizio sia usando una rappresentazione a matrice di adiacenza che con liste di adiacenza--\n");
    
    do{
               
        printf("\n1. Crea grafo con liste di adiacenza\n2. Crea grafo con matrice di adiacenza");
        printf("\n3. Grado uscente ed entrante (lista di adiacenza)\n4. Grado uscente ed entrante (matrice di adiacenza)");
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
                    printf("\nInserire un numero massimo di archi: (non piu' di %d archi) ", n*(n-1));
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
                do{
                    printf("\nInserire numero nodi: (massimo %d nodi) ",maxnodi);
                    scanf("%d",&n);
                    if(n < 1 || n > maxnodi){
                        printf("numero non valido!\n");
                    }
                }while(n < 1 || n > maxnodi);
                Matrix=initMatrix(n);
                dim=n;
                do{
                    printf("\nInserire un numero massimo di archi: (non piu' di %d archi) ", n*(n-1));
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
                    Matrix[source][target] = 1;

                }
                printf("\nGrafo Matrice Creato: \n");
                printMatrix(Matrix,n);
                while(getchar() !='\n');
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
                inDegree=MaxInDegreeMATRIX(Matrix, dim);
                outDegree=MaxOutDegreeMATRIX(Matrix, dim);
                printf("\nIn Degree: %d",inDegree);
                printf("\nOut Degree: %d",outDegree);
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
    
    time_t t;
    int quit=0;
    int n,e,i,k;
    char index;
    char manuale;
    GraphADJ G;
    int** Matrix;
    int dim;
    int source,target;
    int* ArrayInDegree;
    int* ArrayOutDegree;
    int sum;

    clrscr();
    printf("\n--Dato un grafo orientato, stabilire se esiste un nodo pozzo.");
    printf("\nSi definisce nodo pozzo un nodo verso il quale convergono tutti gli altri nodi, ma dal quale non ci si può muovere.");
    printf("\nSe esso esiste, modificare opportunamente il grafo in modo da non avere più un nodo pozzo.");
    printf("\nRipetere l'esercizio sia usando una rappresentazione a matrice di adiacenza che con liste di adiacenza--\n");
    
    do{
        printf("\n\n1. Crea grafo con liste di adiacenza\n2. Crea grafo con matrice di adiacenza");
        printf("\n3. Trova nodo pozzo e correggi (lista di adiacenza)\n4. Trova nodo pozzo e correggi (matrice di adiacenza)");
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
                while(getchar() !='\n');
                printf("\nInserimento archi manuale o automatico casuale? (1 manuale / 0 casuale) ");
                manuale=catchRequest();
                if(manuale == '1'){
                    do{
                        printf("\nInserire numero di archi: (non piu' di %d archi) ", n*(n-1));
                        scanf("%d",&e);
                        if( e < 1 || e > (n*(n-1)) ){
                            printf("numero non valido!\n");
                        }
                    }while( e < 1 || e > (n*(n-1)) );
                    for(i=0;i<e;i++){
                        printf("Arco %d\n",i);
                        do {
                            printf("Nodo sorgente: ");
                            scanf("%d",&source);
                            if(source <0 || source > n ){
                                printf("Deve essere compreso tra 0 e %d!\n", n);
                            }
                        }while(source<0 || source > n );
                        do {
                            printf("Nodo destinazione: ");
                            scanf("%d",&target);
                            if(target <0 || target > n || target == source ){
                                printf("Deve essere compreso tra 0 e %d e non essere uguale alla sorgente!\n", n);
                            }
                        }while(target<0 || target > n || target == source);

                        addEdge(G, source, target, 1);

                    }

                }else {

                    do{
                        printf("\nInserire un numero massimo di archi: (non piu' di %d archi) ", n*(n-1));
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
                }
                printf("\nGrafo Creato: \n");
                printGraph(G);
                while(getchar() !='\n');
                break;
            
            case '2':
                clrscr();
                do{
                    printf("\nInserire numero nodi: (massimo %d nodi) ",maxnodi);
                    scanf("%d",&n);
                    if(n < 1 || n > maxnodi){
                        printf("numero non valido!\n");
                    }
                }while(n < 1 || n > maxnodi);
                Matrix=initMatrix(n);
                dim=n;
                while(getchar() !='\n');
                printf("\nInserimento archi manuale o automatico casuale? (1 manuale / 0 casuale) ");
                manuale=catchRequest();
                if(manuale == '1'){
                    do{
                        printf("\nInserire numero di archi: (non piu' di %d archi) ", n*(n-1));
                        scanf("%d",&e);
                        if( e < 1 || e > (n*(n-1)) ){
                            printf("numero non valido!\n");
                        }
                    }while( e < 1 || e > (n*(n-1)) );
                    for(i=0;i<e;i++){
                        printf("Arco %d\n",i);
                        do {
                            printf("Nodo sorgente: ");
                            scanf("%d",&source);
                            if(source <0 || source > n ){
                                printf("Deve essere compreso tra 0 e %d!\n", n);
                            }
                        }while(source<0 || source > n );
                        do {
                            printf("Nodo destinazione: ");
                            scanf("%d",&target);
                            if(target <0 || target > n || target == source ){
                                printf("Deve essere compreso tra 0 e %d e non essere uguale alla sorgente!\n", n);
                            }
                        }while(target<0 || target > n || target == source);

                        Matrix[source][target]=1;
                    }

                }else {

                    do{
                        printf("\nInserire un numero massimo di archi: (non piu' di %d archi) ", n*(n-1));
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
                        Matrix[source][target] = 1;

                    }
                }
                printf("\nGrafo Matrice Creato: \n");
                printMatrix(Matrix,n);
                while(getchar() !='\n');
                break;
            
            case '3':
                ArrayInDegree=(int*)malloc(sizeof(int)*G->nv);
                ArrayInDegree = gradiEntranti(G,ArrayInDegree);
                ArrayOutDegree=(int*)malloc(sizeof(int)*G->nv);
                ArrayOutDegree = gradiUscenti(G,ArrayOutDegree);
                for(i=0;i<G->nv;i++){
                    if(ArrayOutDegree[i] == 0){
                        if(ArrayInDegree[i] == G->nv-1){
                            printf("\n%d e' un nodo pozzo, Aggiunta di un arco per renderlo non tale: ",i);
                            printf("%d -> %d \n", i, (i+1)%G->nv);
                            addEdge( G, i, (i+1)%G->nv, 1);
                            printf("\nGrafo Risultante: \n");
                            printGraph(G);
                            break;
                        }else 
                            printf("\n%d non e' un nodo pozzo non avendo %d archi entranti (dovrebbero essere numero nodi -1) ", i, ArrayInDegree[i]);
                    }else
                        printf("\n%d non puo' essere un nodo pozzo poiché ha almeno un arco uscente", i);
                    
                }
                break;
            
            case '4':
                ArrayInDegree=(int*)malloc(sizeof(int)*dim);
                ArrayInDegree = gradiEntrantiMATRIX( Matrix, dim);
                ArrayOutDegree=(int*)malloc(sizeof(int)*dim);
                ArrayOutDegree = gradiUscentiMATRIX( Matrix, dim);
                for(i=0;i<dim;i++){
                    if(ArrayOutDegree[i] == 0 && ArrayInDegree[i] == dim-1){
                        printf("\n%d e' un nodo pozzo, Aggiunta di un arco per renderlo non tale: ",i);
                        printf("%d -> %d \n", i, (i+1)%G->nv);
                        Matrix[i][(i+1)%dim]=1;
                        printf("\nGrafo Risultante: \n");
                        printMatrix(Matrix, dim);
                        break;
                    }
                    else
                        printf("\n%d non puo' essere un nodo pozzo(non ha grado entrante %d e uscente 0)",i,dim-1);
                    
                }

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


void ese3(){

    time_t t;
    char index;
    char manuale;
    int quit=0;
    int i, n, e, source, target, peso;
    GraphADJ G, H;
    int check=1;


    clrscr();
    printf("\n--Dati due grafi orientati pesati con liste di adiacenza G e H,");
    printf("\nScrivere una funzione che controlli se H è un sottografo con pesi multipli di G:");
    printf("\nOvvero, H è un sottografo di G e ogni suo arco ha un peso multiplo rispetto al ");
    printf("peso del corrispondente arco in G--\n");

    do{
        printf("\n\n1. Crea grafo G\n2. Crea grafo H\n3. Compara\n0. Uscita\n");

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
                while(getchar() !='\n');
                printf("\nInserimento archi manuale o automatico casuale? (1 manuale / 0 casuale) ");
                do{
                    manuale=catchRequest();
                    if (manuale!='1' && manuale!='0')
                    {
                        printf("Inserire 1 o 0!\n");
                    }
                    
                }while(manuale !='1' && manuale!='0');
                
                if(manuale == '1'){
                    do{
                        printf("\nInserire numero di archi: (non piu' di %d archi) ", n*(n-1));
                        scanf("%d",&e);
                        if( e < 1 || e > (n*(n-1)) ){
                            printf("numero non valido!\n");
                        }
                    }while( e < 1 || e > (n*(n-1)) );
                    for(i=0;i<e;i++){
                        printf("Arco %d\n",i);
                        do {
                            printf("Nodo sorgente: ");
                            scanf("%d",&source);
                            if(source <0 || source > n ){
                                printf("Deve essere compreso tra 0 e %d!\n", n);
                            }
                        }while(source<0 || source > n );
                        do {
                            printf("Nodo destinazione: ");
                            scanf("%d",&target);
                            if(target <0 || target > n || target == source ){
                                printf("Deve essere compreso tra 0 e %d e non essere uguale alla sorgente!\n", n);
                            }
                        }while(target<0 || target > n || target == source);
                        do {
                            printf("Peso: ");
                            scanf("%d",&peso);
                            if(peso <1 ){
                                printf("inserisci un peso positivo!\n");
                            }
                        }while(peso < 1 );
                        addEdge(G, source, target, peso);

                    }

                }else if(manuale == '0') {

                    do{
                        printf("\nInserire un numero massimo di archi: (non piu' di %d archi) ", n*(n-1));
                        scanf("%d",&e);
                        if( e < 1 || e > (n*(n-1)) ){
                            printf("numero non valido!\n");
                        }
                    }while( e < 1 || e > (n*(n-1)) );
                    srand((unsigned int)time(&t));
                    for(i=0;i<e;i++){
                        source=rand()%n;
                        target=rand()%n;
                        peso=(rand()%100)+1;
                        if(target == source)
                            target++;
                        if(target == n)
                            target -=2;
                        addEdge(G,source,target,peso);

                    }
                }
                
                
                printf("\nGrafo G Creato: \n");
                printGraph(G);
                while(getchar() !='\n');
                break;
            
            case '2':
                clrscr();
                
                do{
                    printf("\nInserire numero nodi: (massimo %d nodi) ",maxnodi);
                    scanf("%d",&n);
                    if(n < 1 || n > maxnodi){
                        printf("numero non valido!\n");
                    }
                }while(n < 1 || n > maxnodi);
                
                H=initGraph(n);
                while(getchar() !='\n');
                printf("\nInserimento archi manuale o automatico casuale? (1 manuale / 0 casuale ) ");
                do{
                    manuale=catchRequest();
                    if (manuale!='1' && manuale!='0')
                    {
                        printf("Inserire 1 o 0!\n");
                    }
                    
                }while(manuale !='1' && manuale!='0');
                
                if(manuale == '1'){
                    do{
                        printf("\nInserire numero di archi: (non piu' di %d archi) ", n*(n-1));
                        scanf("%d",&e);
                        if( e < 1 || e > (n*(n-1)) ){
                            printf("numero non valido!\n");
                        }
                    }while( e < 1 || e > (n*(n-1)) );
                    for(i=0;i<e;i++){
                        printf("Arco %d\n",i);
                        do {
                            printf("Nodo sorgente: ");
                            scanf("%d",&source);
                            if(source <0 || source > n ){
                                printf("Deve essere compreso tra 0 e %d!\n", n);
                            }
                        }while(source<0 || source > n );
                        do {
                            printf("Nodo destinazione: ");
                            scanf("%d",&target);
                            if(target <0 || target > n || target == source ){
                                printf("Deve essere compreso tra 0 e %d e non essere uguale alla sorgente!\n", n);
                            }
                        }while(target<0 || target > n || target == source);
                        do {
                            printf("Peso: ");
                            scanf("%d",&peso);
                            if(peso <1 ){
                                printf("inserisci un peso positivo!\n");
                            }
                        }while(peso < 1 );
                        addEdge(H, source, target, peso);

                    }

                }else if(manuale =='0'){

                    do{
                        printf("\nInserire un numero massimo di archi: (non piu' di %d archi) ", n*(n-1));
                        scanf("%d",&e);
                        if( e < 1 || e > (n*(n-1)) ){
                            printf("numero non valido!\n");
                        }
                    }while( e < 1 || e > (n*(n-1)) );
                    srand((unsigned int)time(&t));
                    for(i=0;i<e;i++){
                        source=rand()%n;
                        target=rand()%n;
                        peso=(rand()%100)+1;
                        if(target == source)
                            target++;
                        if(target == n)
                            target -=2;
                        addEdge(H,source,target,peso);

                    }
                }
                
                printf("\nGrafo H Creato: \n");
                printGraph(H);
                while(getchar() !='\n');
                break;
                
            case '3':

                if(G->nv != H->nv){
                    printf("\nI grafi G e H hanno un numero differente di nodi, ");
                    printf("H non può essere sottografo con pesi multipli di G\n");
                    break;

                }else{
                    for(i=0;i<G->nv;i++){
                        if(DimLista(G->adj[i]) != DimLista(H->adj[i])){
                            printf("\nI nodi %d non hanno lo stesso numero di archi ",i);
                            check=-1;
                            break;
                        }
                        check=checkSottografoPesiMultipli(G->adj[i], H->adj[i]);
                    }
                    if(check==-1){
                        printf("\nH non è un sottografo con pesi multipli di G\n");
                    }else
                    {
                        printf("\nH e' un sottografo a pesi multipli di G\n");
                    }
                    

                }
            
            
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


void ese4(){
    char index;
    char manuale;
    int quit=0;

    clrscr();
    printf("\n--Dato un grafo G orientato rappresentato con liste di adiacenza, scrivere una funzione ");
    printf("che verifichi se ci siano cicli nel grafo e,in caso ne esista uno, elimini l’arco che lo crea.--\n");
    

    do{
        printf("\n\n1. Crea grafo G\n2. Verifica ciclo e correggi\n0. Uscita\n");

        index=catchRequest();
        switch(index){
            case '1':


                break;
            
            case '2':
            
            
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
