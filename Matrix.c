#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>
#include "Matrix.h"

#define MATRIX_ERROR(x) printf("Matrix Error: calling %s() on NULL Matrix reference\n", x)
#define BOUND_ERROR(x) printf("Matrix Error: calling %s() with out of bounds reference\n", x)
#define EXIT exit(EXIT_FAILURE)

typedef struct EntryObj* Entry;

typedef struct MatrixObj{
    List* row;
    int size;
    int NNZ;
}MatrixObj;

typedef struct EntryObj{
    int x;
    int y
}EntryObj;

Matrix newMatrix(int n)
{
    Matrix M = malloc(sizeof(MatrixObj));
    
    M->row = malloc(sizeof(n));
    M->size = n*n;
    M->NNZ = 0;

    for(int i = 0; i < n; i++)
    {
        M->row[i] = newList();
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

    if(size(A) != size(B))
        return 0;
    //else same size

    for(int i = 0; i < size(A); i++)
    {
        List L1 = A->row[i];
        List L2 = B->row[i];

        for(moveFront(L1), moveFront(L2); index(L1) >= 0; moveNext(L1), moveNext(L2))
        {
            if(*(int*)get(L1) != *(int*)get(L2))
                return 0;

            moveNext(L1);
            moveNext(L2);

            if(*(double*)get(L1) != *(double*)get(L2))
                return 0;
        }   
    }
    return 1;
}

void makeZero(Matrix M)
{
    if(M == NULL)
    {
        MATRIX_ERROR("makeZero");
        EXIT;
    }

    for(int i = 0; i < size(M); i++)
        clear(M->row[i]);
}

void changeEntry(Matrix M, int i, int j, double x)
{
    if(M == NULL)
    {
        MATRIX_ERROR("changeEntry");
        EXIT;
    }

    List L = M->row[i];

    if(length(L) == 0)
    {
        append(L, &j);
        append(L, &x);
        return;
    }

    for(moveFront(L); index(L) >= 0; moveNext(L))
    {
        if(*(int*)get(L) == j)
        {
            moveNext(L);
            set(L, &x);
            break;
        }

        if(j < *(int*)get(L))
        {
            insertBefore(L, &j);
            insertBefore(L, &x);
            break;
        }

        moveNext(L);
    }

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