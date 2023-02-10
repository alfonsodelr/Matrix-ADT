#include <setjmp.h>
#include <signal.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "List.h"
#include "Matrix.h"

#define FIRST_TEST Empty_getSize
#define MAXSCORE 52
#define CHARITY 10

#define RED "\033[0;31m"
#define CYAN "\033[0;36m"
#define GREEN "\033[0;32m"
#define NC "\033[0m"

static uint8_t testsPassed;
static volatile sig_atomic_t testStatus;
static uint8_t disable_exit_handler;
jmp_buf test_crash;

enum Test_e {
  Empty_getSize = 0,
  NonEmpty_getSize,

  Empty_getNNZ,
  MakeZero_getNNZ,
  ChangeEntry_getNNZ,
  Copy_getNNZ,
  Transpose_getNNZ,
  Sum_getNNZ,
  Diff_getNNZ,
  ScalarMult_getNNZ,
  Product_getNNZ,

  Empty_equals,
  NonEmpty_equals,

  NUM_TESTS,
};

char *testName(int test) {
  if (test == Empty_getSize)
    return "Empty_getSize";
  if (test == NonEmpty_getSize)
    return "NonEmpty_getSize";

  if (test == Empty_getNNZ)
    return "Empty_getNNZ";
  if (test == MakeZero_getNNZ)
    return "MakeZero_getNNZ";
  if (test == ChangeEntry_getNNZ)
    return "ChangeEntry_getNNZ";
  if (test == Copy_getNNZ)
    return "Copy_getNNZ";
  if (test == Transpose_getNNZ)
    return "Transpose_getNNZ";
  if (test == Sum_getNNZ)
    return "Sum_getNNZ";
  if (test == Diff_getNNZ)
    return "Diff_getNNZ";
  if (test == ScalarMult_getNNZ)
    return "ScalarMult_getNNZ";
  if (test == Product_getNNZ)
    return "Product_getNNZ";

  if (test == Empty_equals)
    return "Empty_equals";
  if (test == NonEmpty_equals)
    return "NonEmpty_equals";

  return "";
}

// return 0 if pass otherwise the number of the test that was failed
uint8_t runTest(Matrix *pA, Matrix *pB, Matrix *pC, Matrix *pD, int test) {
  Matrix A = *pA;
  Matrix B = *pB;

  switch (test) {
  case Empty_getSize: {
    if (size(A) != 10)
      return 1;
    return 0;
  }
  case NonEmpty_getSize: {
    changeEntry(A, 1, 1, 4);
    changeEntry(A, 1, 2, 2);
    changeEntry(A, 1, 3, 0);
    changeEntry(A, 2, 1, 2);
    changeEntry(A, 3, 1, 0);
    changeEntry(A, 2, 2, 2);
    changeEntry(A, 3, 3, 0);
    if (size(A) != 10)
      return 1;
    return 0;
  }
  case Empty_getNNZ: {
    if (NNZ(A) != 0)
      return 1;
    return 0;
  }
  case MakeZero_getNNZ: {
    changeEntry(A, 1, 1, 4);
    changeEntry(A, 1, 2, 2);
    changeEntry(A, 1, 3, 0);
    changeEntry(A, 2, 1, 2);
    changeEntry(A, 3, 1, 0);
    changeEntry(A, 2, 2, 2);
    changeEntry(A, 3, 3, 0);
    makeZero(A);
    if (NNZ(A) != 0)
      return 1;
    return 0;
  }
  case ChangeEntry_getNNZ: {
    changeEntry(A, 2, 1, 2);
    changeEntry(A, 3, 1, 5);
    changeEntry(A, 1, 2, 2);
    changeEntry(A, 1, 3, 5);
    changeEntry(A, 1, 1, 4);
    changeEntry(A, 2, 2, 2);
    changeEntry(A, 2, 5, 0);
    changeEntry(A, 2, 3, 0);
    changeEntry(A, 3, 3, 5);
    if (NNZ(A) != 7)
      return 1;
    changeEntry(A, 1, 3, 0);
    changeEntry(A, 3, 1, 0);
    changeEntry(A, 3, 3, 0);
    if (NNZ(A) != 4)
      return 2;
    changeEntry(A, 7, 6, 42);
    changeEntry(A, 10, 1, 24);
    if (NNZ(A) != 6)
      return 3;
    changeEntry(A, 7, 6, 0);
    if (NNZ(A) != 5)
      return 4;
    makeZero(A);
    changeEntry(A, 5, 5, 5);
    if (NNZ(A) != 1)
      return 5;
    return 0;
  }
  case Copy_getNNZ: {
    *pC = copy(A);
    if (NNZ(*pC) != 0)
      return 1;
    changeEntry(A, 1, 1, 1);
    if (NNZ(*pC) != 0)
      return 2;
    *pD = copy(A);
    if (NNZ(*pD) != 1)
      return 3;
    return 0;
  }
  case Transpose_getNNZ: {
    *pC = transpose(A);
    if (NNZ(*pC) != 0)
      return 1;
    changeEntry(A, 1, 1, 4);
    changeEntry(A, 1, 2, 2);
    changeEntry(A, 1, 3, 0);
    changeEntry(A, 2, 1, 2);
    changeEntry(A, 3, 1, 0);
    changeEntry(A, 2, 2, 2);
    changeEntry(A, 3, 3, 0);
    *pD = transpose(A);
    if (NNZ(*pD) != 4)
      return 2;
    return 0;
  }
  case Sum_getNNZ: {
    changeEntry(A, 1, 1, 4);
    changeEntry(A, 1, 2, 2);
    changeEntry(A, 1, 3, 0);
    changeEntry(A, 2, 1, 2);
    changeEntry(A, 3, 1, 0);
    changeEntry(A, 2, 2, 2);
    changeEntry(A, 3, 3, 0);
    *pC = sum(A, A);
    if (NNZ(*pC) != 4 || NNZ(A) != 4)
      return 1;
    changeEntry(B, 1, 1, -4);
    changeEntry(B, 1, 2, 0);
    changeEntry(B, 2, 1, 0);
    changeEntry(B, 2, 2, -2);
    changeEntry(B, 2, 4, 2);
    changeEntry(B, 3, 1, 0);
    changeEntry(B, 3, 2, 2);
    changeEntry(B, 7, 8, 5);
    *pD = sum(A, B);
    if (NNZ(*pD) != 5)
      return 2;
    return 0;
  }
  case Diff_getNNZ: {
    changeEntry(A, 1, 1, -4);
    changeEntry(A, 1, 2, -2);
    changeEntry(A, 1, 3, 0);
    changeEntry(A, 2, 5, 4);
    changeEntry(A, 2, 1, -2);
    changeEntry(A, 3, 1, 2);
    changeEntry(A, 2, 2, -2);
    changeEntry(A, 3, 3, 0);
    *pC = diff(A, A);
    if (NNZ(*pC) != 0 || NNZ(A) != 6)
      return 1;
    changeEntry(B, 1, 1, -4);
    changeEntry(B, 1, 2, 0);
    changeEntry(B, 2, 1, 0);
    changeEntry(B, 2, 2, -2);
    changeEntry(B, 2, 4, 2);
    changeEntry(B, 3, 1, 2);
    changeEntry(B, 3, 2, 2);
    changeEntry(B, 7, 8, 5);
    *pD = diff(A, B);
    if (NNZ(*pD) != 6)
      return 2;
    return 0;
  }
  case ScalarMult_getNNZ: {
    changeEntry(A, 1, 1, 4);
    changeEntry(A, 1, 2, 2);
    changeEntry(A, 1, 3, 0);
    changeEntry(A, 2, 1, 2);
    changeEntry(A, 3, 1, 0);
    changeEntry(A, 2, 2, 2);
    changeEntry(A, 3, 3, 0);
    *pC = scalarMult(-20, A);
    if (NNZ(*pC) != 4)
      return 1;
    makeZero(A);
    *pD = scalarMult(-20, A);
    if (NNZ(*pD) != 0)
      return 2;
    return 0;
  }
  case Product_getNNZ: {
    changeEntry(A, 1, 1, 1);
    changeEntry(A, 2, 2, 1);
    changeEntry(A, 3, 3, 1);
    *pC = product(A, A);
    if (NNZ(*pC) != 3)
      return 1;
    changeEntry(A, 1, 1, 1);
    changeEntry(A, 1, 2, 2);
    changeEntry(A, 1, 3, 3);
    changeEntry(A, 2, 1, 4);
    changeEntry(A, 2, 2, 5);
    changeEntry(A, 2, 3, 6);
    changeEntry(A, 3, 1, 7);
    changeEntry(A, 3, 2, 8);
    changeEntry(A, 3, 3, 9);
    changeEntry(B, 1, 1, 1);
    changeEntry(B, 2, 2, 1);
    *pD = product(A, B);
    if (NNZ(*pD) != 6)
      return 2;
    return 0;
  }
  case Empty_equals: {
    *pC = newMatrix(15);
    if (!equals(A, B))
      return 1;
    if (equals(A, *pC))
      return 2;
    *pD = newMatrix(10);
    changeEntry(*pD, 5, 5, 5);
    makeZero(*pD);
    if (!equals(A, *pD))
      return 3;
    return 0;
  }
  case NonEmpty_equals: {
    *pC = newMatrix(15);
    changeEntry(A, 1, 1, 1);
    changeEntry(*pC, 1, 1, 1);
    if (equals(A, *pC))
      return 1;
    *pD = newMatrix(15);
    changeEntry(A, 1, 1, 1);
    changeEntry(A, 1, 3, 1);
    changeEntry(B, 1, 1, 1);
    changeEntry(B, 1, 3, 1);
    if (!equals(A, B))
      return 2;
    changeEntry(A, 1, 3, 0);
    if (equals(A, B))
      return 3;
    changeEntry(A, 1, 1, 0);
    makeZero(B);
    changeEntry(A, 10, 10, 10);
    changeEntry(B, 10, 10, 10);
    if (!equals(A, B))
      return 4;

    freeMatrix(pA);
    freeMatrix(pB);
    A = *pA = newMatrix(100);
    B = *pB = newMatrix(100);
    int valcount = 1;
    for (int j = 1; j <= 100; j++) {
      for (int k = 1; k <= 100; k++) {
        // hint: this is 1-10000 left-to-right row-by-row
        changeEntry(A, j, k, valcount++);
      }
      changeEntry(B, j, j, 1); // hint: this is the identity matrix
    }
    freeMatrix(pC);
    freeMatrix(pD);
    *pC = scalarMult(2, A);
    *pD = sum(A, A);
    if (!equals(*pC, *pD))
      return 5;

    freeMatrix(pC);
    freeMatrix(pD);
    *pC = scalarMult(-2, A);
    Matrix As1 = diff(A, A);
    Matrix As2 = diff(As1, A);
    *pD = diff(As2, A);
    freeMatrix(&As1);
    freeMatrix(&As2);
    if (!equals(*pC, *pD))
      return 6;

    freeMatrix(pC);
    *pC = product(A, B);
    if (!equals(*pC, A))
      return 7;

    return 0;
  }
  }
  return 254;
}

void segfault_handler(int signal) { // everyone knows what this is
  testStatus = 255;
  longjmp(test_crash, 1);
}

void exit_attempt_handler(void) { // only I decide when you are done
  if (disable_exit_handler)
    return; // allow this to be disabled
  testStatus = 255;
  longjmp(test_crash, 2);
}

void abrupt_termination_handler(int signal) { // program killed externally
  testStatus = 255;
  longjmp(test_crash, 3);
}

int main(int argc, char **argv) {
  if (argc > 2 || (argc == 2 && strcmp(argv[1], "-v") != 0)) {
    printf("Usage: %s [-v]", (argc > 0 ? argv[0] : "./GraphTest"));
    exit(1);
  }

  printf("\n"); // more spacing
  if (argc == 2)
    printf("\n"); // consistency in verbose mode

  testsPassed = 0;
  disable_exit_handler = 0;
  atexit(exit_attempt_handler);
  signal(SIGSEGV, segfault_handler);

  for (uint8_t i = FIRST_TEST; i < NUM_TESTS; i++) {
    Matrix A = newMatrix(10);
    Matrix B = newMatrix(10);
    Matrix C, D;
    uint8_t fail_type = setjmp(test_crash);
    if (fail_type == 0) {
      testStatus = runTest(&A, &B, &C, &D, i);
      freeMatrix(&A);
      freeMatrix(&B);
      if (i >= Copy_getNNZ) {
        freeMatrix(&C);
        if (testStatus == 0 || testStatus > 1)
          freeMatrix(&D);
      }
    }
    if (argc == 2) { // it's verbose mode
      printf("Test %s: %s", testName(i),
             testStatus == 0 ? GREEN "PASSED" NC : RED "FAILED" NC);
      if (testStatus == 255) {
        printf(": due to a " RED "%s" NC "\n", fail_type == 1 ? "segfault"
                                               : fail_type == 2
                                                   ? "program exit"
                                                   : "program interruption");
        printf(RED "\nWARNING: Program will now stop running tests\n\n" NC);
        break;

      } else if (testStatus == 254) {
        printf(": undefined test\n");
      } else if (testStatus != 0) {
        printf(": test" CYAN " %d\n" NC, testStatus);
      } else {
        printf("\n");
      }
    }
    if (testStatus == 0) {
      testsPassed++;
    }
  }

  disable_exit_handler = 1;

  uint8_t totalScore = (MAXSCORE - NUM_TESTS * 4) + testsPassed * 4;

  if (argc == 2) {
    if (testStatus == 255) {
      totalScore = CHARITY;
      printf(RED "Receiving charity points because your program crashes\n" NC);
    } else {
      printf("\nYou passed %d out of %d tests\n", testsPassed, NUM_TESTS);
    }
  }
  printf(
      "\nYou will receive %d out of %d possible points on the MatrixTest\n\n",
      totalScore, MAXSCORE);

  return 0;
}


// #include<stdlib.h>
// #include<stdio.h>
// #include<stdbool.h>
// #include"Matrix.h"

// int main(){
//    int n=100000;
//    Matrix A = newMatrix(n);
//    Matrix B = newMatrix(n);
//    printf("CHANGING ENTRIES\n"); 
//    Matrix C, D, E, F, G, H;

//    changeEntry(A, 1,1,1); changeEntry(B, 1,1,1);
//    changeEntry(A, 1,2,2); changeEntry(B, 1,2,0);
//    changeEntry(A, 1,3,3); changeEntry(B, 1,3,1);
//    changeEntry(A, 2,1,4); changeEntry(B, 2,1,0);
//    changeEntry(A, 2,2,5); changeEntry(B, 2,2,1);
//    changeEntry(A, 2,3,6); changeEntry(B, 2,3,0);
//    changeEntry(A, 3,1,7); changeEntry(B, 3,1,1);
//    changeEntry(A, 3,2,8); changeEntry(B, 3,2,1);
//    changeEntry(A, 3,3,9); changeEntry(B, 3,3,1);

//    printf("%d\n", NNZ(A));
//    printMatrix(stdout, A);
//    printf("\n");

//    printf("%d\n", NNZ(B));
//    printMatrix(stdout, B);
//    printf("\n");

//    C = scalarMult(1.5, A);
//    printf("%d\n", NNZ(C));
//    printMatrix(stdout, C);
//    printf("\n");

//    D = sum(A, B);
//    printf("%d\n", NNZ(D));
//    printMatrix(stdout, D);
//    printf("\n");

//    E = diff(A, A);
//    printf("%d\n", NNZ(E));
//    printMatrix(stdout, E);
//    printf("\n");

//    F = transpose(B);
//    printf("%d\n", NNZ(F));
//    printMatrix(stdout, F);
//    printf("\n");

//    G = product(B, B);
//    printf("%d\n", NNZ(G));
//    printMatrix(stdout, G);
//    printf("\n");

//    H = copy(A);
//    printf("%d\n", NNZ(H));
//    printMatrix(stdout, H);
//    printf("\n");

//    printf("%s\n", equals(A, H)?"true":"false" );
//    printf("%s\n", equals(A, B)?"true":"false" );
//    printf("%s\n", equals(A, A)?"true":"false" );

//    makeZero(A);
//    printf("%d\n", NNZ(A));
//    printMatrix(stdout, A);

//    freeMatrix(&A);
//    freeMatrix(&B);
//    freeMatrix(&C);
//    freeMatrix(&D);
//    freeMatrix(&E);
//    freeMatrix(&F);
//    freeMatrix(&G);
//    freeMatrix(&H);

//    return EXIT_SUCCESS;
// }

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
//    Matrix B = newMatrix(n);
//    Matrix N = newMatrix(n);
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

//    changeEntry(N, 1, 1, 1.0);
//    changeEntry(N, 1, 2, 2.0);
//    changeEntry(N, 1, 3, 3.0);
//    changeEntry(N, 2, 1, 4.0);
//    changeEntry(N, 2, 2, 5.0);
//    changeEntry(N, 2, 3, 6.0);
//    changeEntry(N, 3, 1, 7.0);
//    changeEntry(N, 3, 2, 8.0);
//    changeEntry(N, 3, 3, 9.0);

//    changeEntry(B, 3, 1, 7.0);
//    changeEntry(B, 3, 2, 8.0);
//    changeEntry(B, 3, 3, 9.0);

//    changeEntry(Z, 1, 1, 9.0);
//    changeEntry(Z, 1, 2, 9.0);
//    changeEntry(Z, 2, 1, 9.0);
//    changeEntry(Z, 3, 2, 9.0);
//    changeEntry(Z, 3, 3, 9.0);

//    printf("%d\n", NNZ(M));

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

//    D = diff(M, N);
//    printf("PRINTING SUBTRACTED MATRIX...\n");
//    printf("%d\n", NNZ(D));
//    printMatrix(stdout, D);

//    printf("PRINTING TRANSPOSE OF M\n");
//    T = transpose(M);
//    printMatrix(stdout, T);

//    printf("PRINTING PRODUCT OF M AND M\n");
//    P = product(M, M);
//    printMatrix(stdout, P);

//    return 0;
// }