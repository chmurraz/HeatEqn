#ifndef MATRIXFUNCTIONS_H
#define MATRIXFUNCTIONS_H

#include <stdio.h>
#include <math.h>
#define PI 3.14159265358979323846

typedef struct
{
	int n;
	long double **rows;
	long double *cols;
} Matrix;

Matrix* MatrixAlloc(int n);

void MatrixFree(Matrix *m);
void BuildTriDiag(Matrix *m, long double inferior, long double main, long double superior);
void PrintMatrix(Matrix *m);
long double Determinant(Matrix *m, int n);
void Invert(Matrix *m, Matrix *T);
long double Theta(Matrix *m, int n);
long double Phi(Matrix *m, int n);
void MatrixProduct(Matrix *a, Matrix *b, Matrix *T);
void MatrixVectorProduct(Matrix *a, long double *v);

#endif
