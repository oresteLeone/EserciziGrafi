#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "util.h"

int main(){
    
    int quit = 0;
    char richiesta;

    do{
        printf("\nEsercizi Grafi:\n");
        printf("\n1.Esercizio 1");
        printf("\n2.Esercizio 2");
        printf("\n3.Esercizio 3");
        printf("\n4.Esercizio 4");
        printf("\n0.Chiusura\n");

        richiesta=catchRequest();
        switch (richiesta){

        case '1':
            ese1();
            break;
        
        case '2':
            ese2();
            break;
        
        case '3':
            ese3();
            break;
        
        case '4':
            ese4();
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

    return 0;
}