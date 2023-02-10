#ifndef MATRIX_H
#define MATRIX_H

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <assert.h>
#include "List.h"

typedef struct MatrixObj* Matrix;

Matrix newMatrix(int n);
// newMatrix()
// Returns a reference to a new nXn Matrix object in the zero state.
void freeMatrix(Matrix* pM);
// freeMatrix()
// Frees heap memory associated with *pM, sets *pM to NULL.
int size(Matrix M);
// Access functions
// size()
// Return the size of square Matrix M.
int NNZ(Matrix M);
// NNZ()
// Return the number of non-zero elements in M.
int equals(Matrix A, Matrix B);
// equals()
// Return true (1) if matrices A and B are equal, false (0) otherwise.
void makeZero(Matrix M);
// Manipulation procedures
// makeZero()
// Re-sets M to the zero Matrix state.
void changeEntry(Matrix M, int i, int j, double x);
// changeEntry()
// Changes the ith row, jth column of M to the value x.
// Pre: 1<=i<=size(M), 1<=j<=size(M)
Matrix copy(Matrix A);
// Matrix Arithmetic operations
// copy()
// Returns a reference to a new Matrix object having the same entries as A.
Matrix transpose(Matrix A);
// transpose()
// Returns a reference to a new Matrix object representing the transpose
// of A.
Matrix scalarMult(double x, Matrix A);
// scalarMult()
// Returns a reference to a new Matrix object representing xA.
Matrix sum(Matrix A, Matrix B);
// sum()
// Returns a reference to a new Matrix object representing A+B.
// pre: size(A)==size(B)
Matrix diff(Matrix A, Matrix B);
// diff()
// Returns a reference to a new Matrix object representing A-B.
// pre: size(A)==size(B)
Matrix product(Matrix A, Matrix B);
// product()
// Returns a reference to a new Matrix object representing AB
// pre: size(A)==size(B)
void printMatrix(FILE* out, Matrix M);
// printMatrix()
// Prints a string representation of Matrix M to filestream out. Zero rows
// are not printed. Each non-zero row is represented as one line consisting
// of the row number, followed by a colon, a space, then a space separated
// list of pairs "(col, val)" giving the column numbers and non-zero values
// in that row. The double val will be rounded to 1 decimal point.

#endif