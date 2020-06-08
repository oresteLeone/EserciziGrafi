#ifndef graphADJ
#define graphADJ
#include "edgeADJ.h" //libreria archi



//definizione struttura grafo
struct graphADJType {
    int nv;         //numero vertici
    edgeADJ* adj;     //lista di adiacenza
};
typedef struct graphADJType* GraphADJ;


//inizializzazione grafo
GraphADJ initGraph(int n);

//inizializzazione archi
void initEdge(GraphADJ G);

//Free del grafo
void freeGraph(GraphADJ G);

//stampa del grafo
void printGraph(GraphADJ G);

//aggiungi nodo al grafo
void addNode(GraphADJ G);

//rimozione di un nodo dal grafo
void removeNode(GraphADJ G, int node_to_remove);

//aggiunge arco da source a target
void addEdge(GraphADJ G, int source, int target, int peso);

//rimuove arco da source a target
void removeEdge(GraphADJ G, int source, int target);

//funzione che restituisce l'array coi gradi entranti
int* gradiEntranti(GraphADJ G, int ArrayInDegree[] );

//restutuisce il grado entrante maggiore
int MaxInDegree(int ArrayInDegree[], int dim);

//restituisce il massimo grado uscente
int MaxOutDegree(GraphADJ G);

int* gradiUscenti(GraphADJ G, int ArrayOutDegree[]);

int checkSottografoPesiMultipli(edgeADJ listaG , edgeADJ listaH );

edgeADJ findNode(int target, edgeADJ listaH);

#endif