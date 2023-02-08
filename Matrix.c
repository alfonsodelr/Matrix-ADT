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
    int col;
    double data;
}EntryObj;

Matrix newMatrix(int n)
{
    Matrix M = malloc(sizeof(MatrixObj));
    
    M->row = malloc(sizeof(n));
    M->size = n;
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

    for(int i = 0; i < size(A); i++)
    {
        List L1 = A->row[i];
        List L2 = B->row[i];

        for(moveFront(L1), moveFront(L2); index(L1) >= 0; moveNext(L1), moveNext(L2))
        {
            if(((Entry)get(L1))->col != ((Entry)get(L2))->col)
                return 0;
            if(((Entry)get(L1))->data != ((Entry)get(L2))->data)
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

    M->NNZ = 0;
}

void changeEntry(Matrix M, int i, int j, double x)
{
    if(M == NULL)
    {
        MATRIX_ERROR("changeEntry");
        EXIT;
    }

    if(i > size(M) || j > size(M))
    {
        BOUND_ERROR("changeEntry");
        EXIT;
    }

    Entry E = malloc(sizeof(EntryObj));
    E->col = j;
    E->data = x;

    List L = M->row[i-1];

    if(length(L) == 0)
    {
        append(L, E);
        M->NNZ++;
        return;
    }

    for(moveFront(L); index(L) >= 0; moveNext(L))
    {
        if(((Entry)get(L))->col == j)
        {
            insertBefore(L, E);
            delete(L);
            return;
        }

        if(j < ((Entry)get(L))->col)
        {
            insertBefore(L, E);
            M->NNZ++;
            return;
        }
    }

    append(L, E);
}

Matrix copy(Matrix A)
{
    if(A == NULL)
    {
        MATRIX_ERROR("copy");
        EXIT;
    }

    Matrix M = newMatrix(size(A));

    for(int i = 0; i < size(A); i++)
    {
        List A_List = A->row[i];
        List M_List = M->row[i];

        for(moveFront(A_List); index(A_List) >= 0; moveNext(A_List))
        {
            Entry E = malloc(sizeof(EntryObj));
            E->col = ((Entry)get(A_List))->col;
            E->data = ((Entry)get(A_List))->data;
            append(M_List, E);
        }
    }

    M->NNZ = A->NNZ;
    M->size = A->size;

    return M;
}

Matrix transpose(Matrix A)
{
    if(A == NULL)
    {
        MATRIX_ERROR("transpose");
        EXIT;
    }

    Matrix M = newMatrix(size(A));

    for(int i = 0; i < size(A); i++)
    {
        List L = A->row[i];
        for(moveFront(L); index(L) >= 0; moveNext(L))
        {
            changeEntry(M, ((Entry)get(L))->col, i+1, 
            ((Entry)get(L))->data);
        }
    }

    return M;
}

Matrix scalarMult(double x, Matrix A)
{
    if(A == NULL)
    {
        MATRIX_ERROR("scalarMult");
        EXIT;
    }

    Matrix M = newMatrix(size(A));

    for(int i = 0; i < size(A); i++)
    {
        List L = A->row[i];
        for(moveFront(L); index(L)>=0; moveNext(L))
        {
            double product = (((Entry)get(L))->data) * x;
            changeEntry(M, i+1, ((Entry)get(L))->col, product);
        }
    }

    return M;
}

Matrix sum(Matrix A, Matrix B)
{
    if(A == NULL)
    {
        MATRIX_ERROR("scalarMult");
        EXIT;
    }

    Matrix M = newMatrix(size(A));

    for(int i = 0; i <= size(A); i++)
    {
        List L1 = A->row[i];
        List L2 = B->row[i];

        for(int j = 1; j <= size(A); j++)
        {
            double x = 0.0, y = 0.0;
            moveFront(L1);
            moveFront(L2);

            if(length(L1) == 0)
            {
                x = 0.0;
            }
            else
            {
                if(((Entry)get(L1))->col == j)
                {
                    x = ((Entry)get(L1))->data;
                    moveNext(L1);
                }
                else
                {
                    x = 0.0;
                    moveNext(L1);
                }
            }

            if(length(L2) == 0)
            {
                y = 0.0;
            }
            else
            {
                if(((Entry)get(L2))->col == j)
                {
                    y = ((Entry)get(L2))->data;
                    moveNext(L2);
                }
                else
                {
                    y = 0.0;
                    moveNext(L2);
                }
            }

            double sum = x + y; 
            printf("SUM: %.1lf\n", sum);

            changeEntry(M, i+1, j, sum);
        }
    }

    return M;
}

Matrix diff(Matrix A, Matrix B)
{
    Matrix M = NULL;


    return M;
}

Matrix product(Matrix A, Matrix B)
{
    Matrix M = NULL;


    return M;
}

void printMatrix(FILE* out, Matrix M)
{
    for(int i = 0; i < size(M); i++)
    {
        fprintf(stdout, "%d: ", i+1);
        List L = M->row[i];

        for(moveFront(L); index(L) >= 0; moveNext(L))
        {
            fprintf(out, "(%d, %.1lf) ", ((Entry)get(L))->col, (((Entry)get(L))->data));
        }

        fprintf(out, "\n");
    }
}