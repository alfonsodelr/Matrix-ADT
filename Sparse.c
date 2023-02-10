#include<stdlib.h>
#include<stdio.h>
#include<stdbool.h>
#include"Matrix.h"

int main(int argc, char* argv[])
{
    if(argc != 3)
    {
        fprintf( stderr, "ERROR: MUST PASS TWO ARGUMENTS\n");
        return -1;
    }

    //------------------OPENING FILE ARGUMENTS---------------------//

    FILE* file = fopen(argv[1], "r");
    FILE* write = fopen(argv[2], "w");

    if(file == NULL)
    {
        fprintf(stderr, "File Error: Failed to open %s", argv[1]);
        exit(EXIT_FAILURE);
    }

    if(write == NULL)
    {
        fprintf(stderr, "File Error: Failed to open %s", argv[2]);
        exit(EXIT_FAILURE);
    }

    int a = 0, b = 0, c = 0;

    fscanf(file, "%d %d %d", &a, &b, &c);
    fscanf(file, "%*[^\n]");

    Matrix A = newMatrix(a);
    Matrix B = newMatrix(a);

    for(int i = 0; i < b; i++)
    {
        int x = 0, y = 0;
        double z = 0.0;
        fscanf(file, "%d %d %lf", &x, &y, &z);
        changeEntry(A, x, y, z);
    }
    
    fscanf(file, "%*[^\n]");

    for(int i = 0; i < c; i++)
    {
        int x = 0, y = 0;
        double z = 0.0;
        fscanf(file, "%d %d %lf", &x, &y, &z);
        changeEntry(B, x, y, z);
    }

    //-----------------NNZ OF MATRIX A------------------------//
    fprintf(write, "A has %d non-zero entries:\n", NNZ(A));
    printMatrix(write, A);

    fprintf(write, "\n");

    //-----------------NNZ OF MATRIX B------------------------//
    fprintf(write, "B has %d non-zero entries:\n", NNZ(B));
    printMatrix(write, B);

    fprintf(write, "\n");

    //-----------------SCALAR MULTIPLICATION-----------------//
    Matrix SM = scalarMult(1.5, A);

    fprintf(write, "(1.5)*A = \n");
    printMatrix(write, SM);

    fprintf(write, "\n");

    //-----------------SUM OF A AND B-----------------//
    Matrix S1 = sum(A, B);

    fprintf(write, "A+B = \n");
    printMatrix(write, S1);

    fprintf(write, "\n");

    //-----------------SUM OF A AND A-----------------//
    Matrix S2 = sum(A, A);

    fprintf(write, "A+A = \n");
    printMatrix(write, S2);

    fprintf(write, "\n");

    //-----------------DIFF OF B AND A-----------------//
    Matrix D1 = diff(B, A);

    fprintf(write, "B-A = \n");
    printMatrix(write, D1);

    fprintf(write, "\n");

    //-----------------DIFF OF A AND A-----------------//
    Matrix D2 = diff(A, A);

    fprintf(write, "A-A = \n");
    printMatrix(write, D2);

    fprintf(write, "\n");

    //-----------------TRANSPOSE OF A-----------------//
    Matrix T = transpose(A);

    fprintf(write, "Transpose(A) = \n");
    printMatrix(write, T);

    fprintf(write, "\n");

    //-----------------PRODUCT OF A AND B-----------------//
    Matrix P1 = product(A, B);

    fprintf(write, "A*B = \n");
    printMatrix(write, P1);

    fprintf(write, "\n");

    //-----------------PRODUCT OF B AND B-----------------//
    Matrix P2 = product(B, B);

    fprintf(write, "B*B = \n");
    printMatrix(write, P2);

    fprintf(write, "\n");

    freeMatrix(&A);
    freeMatrix(&B);
    freeMatrix(&SM);
    freeMatrix(&S1);
    freeMatrix(&S2);
    freeMatrix(&D1);
    freeMatrix(&D2);
    freeMatrix(&T);
    freeMatrix(&P1);
    freeMatrix(&P2);

    fclose(file);
    fclose(write);

    return 0;
}