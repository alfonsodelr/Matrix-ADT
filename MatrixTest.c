#include<stdlib.h>
#include<stdio.h>
#include<stdbool.h>
#include"Matrix.h"

int main(){
   int n=100000;
   Matrix A = newMatrix(n);
   Matrix B = newMatrix(n);
   printf("CHANGING ENTRIES\n"); 
   Matrix C, D, E, F, G, H;

   changeEntry(A, 1,1,1); changeEntry(B, 1,1,1);
   changeEntry(A, 1,2,2); changeEntry(B, 1,2,0);
   changeEntry(A, 1,3,3); changeEntry(B, 1,3,1);
   changeEntry(A, 2,1,4); changeEntry(B, 2,1,0);
   changeEntry(A, 2,2,5); changeEntry(B, 2,2,1);
   changeEntry(A, 2,3,6); changeEntry(B, 2,3,0);
   changeEntry(A, 3,1,7); changeEntry(B, 3,1,1);
   changeEntry(A, 3,2,8); changeEntry(B, 3,2,1);
   changeEntry(A, 3,3,9); changeEntry(B, 3,3,1);

   printf("%d\n", NNZ(A));
   printMatrix(stdout, A);
   printf("\n");

   printf("%d\n", NNZ(B));
   printMatrix(stdout, B);
   printf("\n");

   C = scalarMult(1.5, A);
   printf("%d\n", NNZ(C));
   printMatrix(stdout, C);
   printf("\n");

   D = sum(A, B);
   printf("%d\n", NNZ(D));
   printMatrix(stdout, D);
   printf("\n");

   E = diff(A, A);
   printf("%d\n", NNZ(E));
   printMatrix(stdout, E);
   printf("\n");

   F = transpose(B);
   printf("%d\n", NNZ(F));
   printMatrix(stdout, F);
   printf("\n");

   G = product(B, B);
   printf("%d\n", NNZ(G));
   printMatrix(stdout, G);
   printf("\n");

   H = copy(A);
   printf("%d\n", NNZ(H));
   printMatrix(stdout, H);
   printf("\n");

   printf("%s\n", equals(A, H)?"true":"false" );
   printf("%s\n", equals(A, B)?"true":"false" );
   printf("%s\n", equals(A, A)?"true":"false" );

   makeZero(A);
   printf("%d\n", NNZ(A));
   printMatrix(stdout, A);

   freeMatrix(&A);
   freeMatrix(&B);
   freeMatrix(&C);
   freeMatrix(&D);
   freeMatrix(&E);
   freeMatrix(&F);
   freeMatrix(&G);
   freeMatrix(&H);

   return EXIT_SUCCESS;
}

/*
Output of this program:
9
1: (1, 1.0) (2, 2.0) (3, 3.0)
2: (1, 4.0) (2, 5.0) (3, 6.0)
3: (1, 7.0) (2, 8.0) (3, 9.0)

6
1: (1, 1.0) (3, 1.0)
2: (2, 1.0)
3: (1, 1.0) (2, 1.0) (3, 1.0)

9
1: (1, 1.5) (2, 3.0) (3, 4.5)
2: (1, 6.0) (2, 7.5) (3, 9.0)
3: (1, 10.5) (2, 12.0) (3, 13.5)

9
1: (1, 2.0) (2, 2.0) (3, 4.0)
2: (1, 4.0) (2, 6.0) (3, 6.0)
3: (1, 8.0) (2, 9.0) (3, 10.0)

0

6
1: (1, 1.0) (3, 1.0)
2: (2, 1.0) (3, 1.0)
3: (1, 1.0) (3, 1.0)

7
1: (1, 2.0) (2, 1.0) (3, 2.0)
2: (2, 1.0)
3: (1, 2.0) (2, 2.0) (3, 2.0)

9
1: (1, 1.0) (2, 2.0) (3, 3.0)
2: (1, 4.0) (2, 5.0) (3, 6.0)
3: (1, 7.0) (2, 8.0) (3, 9.0)

true
false
true
0
*/

//////////////////////////////////////////////////////////////

// int main(int argc, char* argv[])
// {
//    int n = 3;
   
//    Matrix M = newMatrix(n);
//    Matrix Z = newMatrix(n);
//    Matrix C = NULL;
//    Matrix T = NULL;
//    Matrix P = NULL;
//    Matrix S = NULL;
//    Matrix D = NULL;

//    //1 - 9
//    changeEntry(M, 1, 1, 1.0);
//    changeEntry(M, 1, 2, 2.0);
//    changeEntry(M, 1, 3, 3.0);
//    changeEntry(M, 2, 1, 4.0);
//    changeEntry(M, 2, 2, 5.0);
//    changeEntry(M, 2, 3, 6.0);
//    changeEntry(M, 3, 1, 7.0);
//    changeEntry(M, 3, 2, 8.0);
//    changeEntry(M, 3, 3, 9.0);

//    changeEntry(Z, 1, 1, 9.0);
//    changeEntry(Z, 1, 2, 9.0);
//    changeEntry(Z, 2, 1, 9.0);
//    changeEntry(Z, 3, 2, 9.0);
//    changeEntry(Z, 3, 3, 9.0);

//    printf("PRINTING ORIGINAL MATRIX...\n");
//    printMatrix(stdout, M);

//    printf("PRINTING COPY MATRIX...\n");
//    C = copy(M);
//    printMatrix(stdout, C);

//    printf("PRINTING TRANSPOSE MATRIX...\n");
//    T = transpose(M);
//    printMatrix(stdout, T);

//    printf("PRINTING SCALED MATRIX...\n");
//    P = scalarMult(2.0, M);
//    printMatrix(stdout, P);

//    printf("PRINTING Z MATRIX...\n");
//    printMatrix(stdout, Z);

//    S = sum(M, Z);
//    printf("PRINTING SUMMED MATRIX...\n");
//    printMatrix(stdout, S);

//    D = diff(M, Z);
//    printf("PRINTING SUBTRACTED MATRIX...\n");
//    printMatrix(stdout, D);

//    printf("PRINTING TRANSPOSE OF M\n");
//    T = transpose(M);
//    printMatrix(stdout, T);

//    printf("PRINTING PRODUCT OF M AND M\n");
//    P = product(M, M);
//    printMatrix(stdout, P);

//    return 0;
   
// }