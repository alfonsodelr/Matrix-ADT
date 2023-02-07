#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>
#include "Matrix.h"

#define MATRIX_ERROR(x) printf("Matrix Error: calling %s() on NULL Matrix reference\n", x)
#define BOUND_ERROR(x) printf("Matrix Error: calling %s() with out of bounds reference\n", x)
#define EXIT exit(EXIT_FAILURE)

typedef struct MatrixObj{
    List* Entry;
    int size;
    int NNZ;
}MatrixObj;

Matrix newMatrix(int n)
{
    Matrix M = malloc(sizeof(MatrixObj));
    
    M->Entry = malloc(sizeof(n));
    M->size = 0;
    M->NNZ = 0;

    for(int i = 0; i < n; i++)
    {
        M->Entry[i] = newList();
    }

    return M;
}

void freeMatrix(Matrix* pM)
{

}

int size(Matrix M)
{
    if(M == NULL)
    {
        MATRIX_ERROR("size");
        EXIT;
    }

    return M->size;
}

int NNZ(Matrix M)
{
    if(M == NULL)
    {
        MATRIX_ERROR("NNZ");
        EXIT;
    }

    return M->NNZ;
}

int equals(Matrix A, Matrix B)
{
    if(A == NULL || B == NULL)
    {
        MATRIX_ERROR("equals");
        EXIT;
    }

    for(moveFront(A), moveFront(B); index(A) != -1; moveNext(A), moveNext(B))
    {
        
    }


    return 1;
}

void makeZero(Matrix M)
{

}

void changeEntry(Matrix M, int i, int j, double x)
{

}

Matrix copy(Matrix A)
{

}

Matrix transpose(Matrix A)
{

}

Matrix scalarMult(double x, Matrix A)
{

}

Matrix sum(Matrix A, Matrix B)
{

}

Matrix diff(Matrix A, Matrix B)
{

}

Matrix product(Matrix A, Matrix B)
{

}

void printMatrix(FILE* out, Matrix M)
{

}