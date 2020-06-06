#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "graphMATRIX.h"

int** initMatrix(int dim){
    int** matrix=(int**)malloc(sizeof(int*)*dim);
    int i,k;
    for(i=0;i<dim;i++)
        matrix[i]=(int*)malloc(sizeof(int)*dim);
    
    for(i=0;i<dim;i++){
        for(k=0;k<dim;k++){
            matrix[i][k] = 0;
        }
    }
  return matrix;
}

int MaxInDegreeMATRIX(int** Matrix, int dim){
    int i,k,max=0,sum;
    
    for(i=0;i<dim;i++){
        sum=0;
        for(k=0;k<dim;k++){
            sum += Matrix[k][i];
        }
        if(max<sum)
            max=sum;
    }
    return max;
}

int MaxOutDegreeMATRIX(int** Matrix, int dim){
    int i,k,max=0,sum;
    
    for(i=0;i<dim;i++){
        sum=0;
        for(k=0;k<dim;k++){
            sum += Matrix[i][k];
        }
        if(max<sum)
            max=sum;
    }
    return max;
}

void printMatrix(int** Matrix,int dim){
    int i,k;
    printf("\n\t");
    for (i = 0; i < dim; i++){
        printf("%d\t",i);
    }
    printf("\n");
    for(i=0;i<dim;i++){
        printf("%d\t",i);
        for(k=0;k<dim;k++){
            printf("%d\t",Matrix[i][k]);
        }
        printf("\n");
    }
    
    printf("\n");
}
