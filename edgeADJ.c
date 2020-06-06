#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "edgeADJ.h"

//stampa lista di adiacenza
void printList(edgeADJ L) {
    if (L != NULL) {
        printf("%d Peso: %d -> ",L->key, L->peso);
        printList(L->next);
    }
}

//rimuove le occorenze del nodo rimosso dalle liste di adiacenza
edgeADJ checkListRemoval(edgeADJ L, int node_to_remove) {
    if (L != NULL) {
        L->next = checkListRemoval(L->next, node_to_remove);
        if (L->key == node_to_remove) {
            edgeADJ tmp = L->next;
            free(L);
            return tmp;
        }
        else if (L->key > node_to_remove) {
            L->key -= 1;
        }
    }
    return L;
}

//inizializza un nodo della lista di adiacenza
edgeADJ initNodeList(int info, int peso) {
    edgeADJ L = (edgeADJ)malloc(sizeof(struct edgeADJType));
    L->key = info;
    L->peso = peso;
    L->next = NULL;
    return L;
}


edgeADJ randomList(int index, int mod) {
    edgeADJ L = NULL;
    int i = 0;
    for (i = 0; i < index; i++) {
        L = appendNodeList(L, rand() % mod, rand() % mod);
    }
    return L;
}

//inserisce un nodo in coda alla lista di adiacenza
edgeADJ appendNodeList(edgeADJ L, int target, int peso) {
    if (L != NULL) {
        if (L->key != target) {
            L->next = appendNodeList(L->next, target, peso);
        }
    }
    else {
        L = initNodeList(target, peso);
    }
    return L;
}

//inserisce un nodo in testa alla lista di adiacenza
edgeADJ addNodeHead(edgeADJ L, int target, int peso) {
    if (L != NULL) {
        edgeADJ G = (edgeADJ)malloc(sizeof(struct edgeADJType));
        G->key = target;
        L->peso = peso;
        G->next = L;
        return G;
    }
    return initNodeList(target, peso);
}

//rimuove la lista di adiacenza di un nodo
edgeADJ removeNodeList(edgeADJ L, int target) {
    if (L != NULL) {
        if (L->key == target) {
            edgeADJ tmp = L->next;
            free(L);
            return tmp;
        }
        L->next = removeNodeList(L->next, target);
    }
    return L;
}

//dealloca una lista
void freeList(edgeADJ L) {
    if (L != NULL) {
        freeList(L->next);
        free(L);
    }
}

//restituisce la dimensione della lista di adiacenza
int DimLista(edgeADJ L) {
    if (L == NULL)
        return 0;
    return 1 + DimLista(L->next);
}

//funzione per la visita di lista di adiacenza che aggiorna i gradi entranti nell array 
void traverselistIN(edgeADJ list, int ArrayInDegree[]) {
    if (list) {
        traverselistIN(list->next, ArrayInDegree);
        ArrayInDegree[list->key] += 1;
    }

}