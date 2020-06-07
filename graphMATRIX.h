#ifndef matrixlib
#define matrixlib

int** initMatrix(int dim);

int MaxInDegreeMATRIX(int** Matrix, int dim);

int MaxOutDegreeMATRIX(int** Matrix, int dim);

void printMatrix(int** Matrix,int dim);

int* gradiEntrantiMATRIX(int** Matrix, int dim);

int* gradiUscentiMATRIX(int** Matrix, int dim);

#endif