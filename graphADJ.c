#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "graphADJ.h"



//inizializzazione grafo
GraphADJ initGraph(int n) {
	GraphADJ G;
	int i;
	G = (GraphADJ)malloc(sizeof(struct graphADJType));
	if (G) {
		G->adj = (edgeADJ*)malloc(n * sizeof(struct edgeADJType));
		if (G->adj) {
			G->nv = n;
			for (i = 0;i < n;i++) {
				G->adj[i] = NULL;
			}
		}
	}
	return G;
}

//aggiunte iniziali degli archi del grafo 
void initEdge(GraphADJ G) {
	
}


//Free del grafo
void freeGraph(GraphADJ G) {
	if (G != NULL) {
		if (G->nv > 0) {
			int i = 0;
			for (i = 0; i < G->nv; i++) {
				freeList(G->adj[i]);
			}
		}
		free(G);
	}
}

//stampa del grafo
void printGraph(GraphADJ G) {
	if (G != NULL) {
		int i = 0;
		for (i = 0;i < G->nv;i++) {
			printf("%d -> ", i);
			printList(G->adj[i]);
			printf("\n");
		}
	}
}

//aggiungi nodo al grafo
void addNode(GraphADJ G) {
	if (G != NULL) {
		edgeADJ* old = G->adj;
		int i = 0;
		G->adj = (edgeADJ*)malloc((G->nv + 1) * sizeof(struct edgeADJType));
		for (i = 0;i < G->nv;i++)
			G->adj[i] = old[i];
		G->nv += 1;
		G->adj[G->nv - 1] = NULL;
	}
}

//rimozione di un nodo dal grafo
void removeNode(GraphADJ G, int node_to_remove) {
	if (G != NULL) {
		int i = 0;
		int x = 0;
		edgeADJ* tmp = G->adj;
		G->adj = (edgeADJ*)calloc(G->nv - 1, sizeof(struct edgeADJType));
		for (i = 0; i < G->nv; i++) {
			if (i != node_to_remove) {
				G->adj[x] = checkListRemoval(tmp[i], node_to_remove);
				x++;
			}
			else {
				freeList(tmp[i]);
			}
		}
		free(tmp);
		G->nv -= 1;
	}
}

//aggiunge arco da source a target
void addEdge(GraphADJ G, int source, int target, int peso) {
	assert(G != NULL);
	assert(source < G->nv);
	assert(target < G->nv);
	if (source != target) {
		G->adj[source] = appendNodeList(G->adj[source], target, peso);
	}

}

//rimuove arco da source a target
void removeEdge(GraphADJ G, int source, int target) {
	assert(G != NULL);
	assert(source < G->nv);
	assert(target < G->nv);
	if (source != target) {
		G->adj[source] = removeNodeList(G->adj[source], target);
	}
	
}

//funzione che restituisce l'array coi gradi entranti
int* gradiEntranti(GraphADJ G,int ArrayInDegree[]) {
	int i;
	for (i = 0;i < G->nv;i++) {
		ArrayInDegree[i] = 0;
	}
	for (i = 0;i < G->nv;i++) {
		traverselistIN(G->adj[i], ArrayInDegree);

	}
	return ArrayInDegree;
}

//restutuisce il grado entrante maggiore
int MaxInDegree(int ArrayInDegree[], int dim) {
	int max = 0;
	int i;
	for (i = 0;i < dim;i++) {
		if (max < ArrayInDegree[i]) {
			
			max = ArrayInDegree[i];
		}
	}
	return max;
}

//restituisce il massimo grado uscente
int MaxOutDegree(GraphADJ G){
    int max=0;
    int i;
    int tmp=0;
    for(i=0;i<G->nv;i++){
        tmp=DimLista(G->adj[i]);
        if(max < tmp)
            max = tmp;
    }
    return max;
}


int* gradiUscenti(GraphADJ G, int ArrayOutDegree[]){
	int i;
	for (i = 0;i < G->nv;i++) {
		ArrayOutDegree[i] = 0;
	}
	for (i = 0;i < G->nv;i++) {
		ArrayOutDegree[i] = DimLista(G->adj[i]);

	}
	return ArrayOutDegree;
}


int checkSottografoPesiMultipli(edgeADJ listaG, edgeADJ listaH){
	int check=1;
	edgeADJ NodoG;
	if(listaH){
		check=checkSottografoPesiMultipli(listaG,listaH->next);
		if(check==1){
			NodoG=findNode(listaH->key,listaG);
			if(NodoG){
				if( (listaH->peso)%(NodoG->peso) == 0 || (NodoG->peso)%(listaH->peso) == 0 ){
					check=1;
				}
				else 
					check=-1;
			}
			else 
				check=-1;
		}
	}
	return check;
}

edgeADJ findNode(int target, edgeADJ listaG){
	edgeADJ tmp=NULL;
	if(listaG){
		if(listaG->key == target){
			tmp=listaG;
		}else {
			tmp=findNode(target,listaG->next);

		}

	}
	return tmp;

}

void GetAcycle(GraphADJ G) {
  int i, *aux =(int* ) calloc(G->nv,sizeof(int));
  if(!aux) {
    printf("Errore di Allocazione\n");
  }else { 
    for(i = 0; i < G->nv; i++)
      if(!aux[i]) {
         GetAcycleUtil(G,i,aux);
      }
	  
    free(aux);
  }
} 

  void GetAcycleUtil(GraphADJ G, int i, int* aux) {
    edgeADJ e; 
    edgeADJ tmp;
    aux[i] = 1;
    for(e = G->adj[i]; e; ){
      	if(!aux[e->key]) { 
        	GetAcycleUtil(G,e->key,aux);
			e = e->next;
      	}else{
			int c=isParent(i, G->adj[e->key]);
			if(c){
				tmp=e->next;
				removeEdge(G,i,e->key);
				e=tmp;
			}
      		else{
				  int cycle=goThrough(i,e->key,G);
				  if(cycle){
					tmp=e->next;
					removeEdge(G,i,e->key);
					e=tmp;
				  }else
				  {
					e=e->next;
				  }
				  
			  }
      	}    
    }
  }

int isParent(int target, edgeADJ listSource ){
	int res=0;
	if(listSource){
		res=isParent(target, listSource->next);
		if(listSource->key == target){
			res=1;
		}
	}
	return res;

}

int goThrough(int target, int source , GraphADJ G){
	int res=0;
	if(G->adj[source]){
		res=isParent(target,G->adj[source]);
		if(res==0){
			res=goThrough(target,G->adj[source]->key, G);
			

		}
	}
	return res;
}


void compare(GraphADJ G, GraphADJ H){
	int i,check=1;
	if(G->nv < H->nv){
        printf("\nIl grafo H ha un numero maggiore di nodi rispetto a G, ");
        printf("H non può essere sottografo con pesi multipli di G\n");
        return;
    }else{
        for(i=0;i < H->nv;i++){
            check=checkSottografoPesiMultipli(G->adj[i], H->adj[i]);
			if(check==-1)
				break;
            }
        if(check==-1){
            printf("\nH non è un sottografo con pesi multipli di G\n");
        }else{
            printf("\nH e' un sottografo a pesi multipli di G\n");
        }
    }
}