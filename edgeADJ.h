#ifndef edgeADJlib
#define edgeADJlib


//definizione struttura degli archi
struct edgeADJType {
    int key;         //chiave numerica del nodo
    int peso;        //peso    
    struct edgeADJType* next;  //nodo successivo
};
typedef struct edgeADJType* edgeADJ;

//stampa lista di adiacenza
void printList(edgeADJ L);

//rimuove le occorenze del nodo rimosso dalle liste di adiacenza
edgeADJ checkListRemoval(edgeADJ L, int node_to_remove);

//inizializza un nodo della lista di adiacenza
edgeADJ initNodeList(int info, int peso);


edgeADJ randomList(int index, int mod);

//inserisce un nodo in coda alla lista di adiacenza
edgeADJ appendNodeList(edgeADJ L, int target, int peso);

//inserisce un nodo in testa alla lista di adiacenza
edgeADJ addNodeHead(edgeADJ L, int target, int peso);

//rimuove la lista di adiacenza di un nodo
edgeADJ removeNodeList(edgeADJ L, int target);

//dealloca una lista
void freeList(edgeADJ L);

//restituisce la dimensione della lista di adiacenza
int DimLista(edgeADJ L);

//funzione per la visita di lista di adiacenza che aggiorna i gradi entranti nell array 
void traverselistIN(edgeADJ list, int ArrayInDegree[]);
#endif