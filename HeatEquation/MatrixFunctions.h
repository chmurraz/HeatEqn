#ifndef MATRIXFUNCTIONS_H
#define MATRIXFUNCTIONS_H

#include <stdio.h>
#include <math.h>
#define PI 3.14159265358979323846

typedef struct
{
	int n;					//	Dimension 'n' of the matrix
	long double **rows;		//	Pointer to the rows of the matrix
	long double *cols;		//	Pointer to the column of the matrix
} Matrix;

Matrix* MatrixAlloc(int n);

void MatrixFree(Matrix *m);
void BuildTriDiag(Matrix *m, long double inferior, long double main, long double superior);
void PrintMatrix(Matrix *m);
long double Determinant(Matrix *m, int n);
void Invert(Matrix *m, Matrix *T);
void MatrixProduct(Matrix *a, Matrix *b, Matrix *T);
void MatrixVectorProduct(Matrix *a, long double *v);

#endif
