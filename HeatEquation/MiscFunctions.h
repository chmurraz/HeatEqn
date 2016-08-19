#ifndef MISCFUNCTIONS_H
#define MISCFUNCTIONS_H

#include "MatrixFunctions.h"

typedef struct
{
	int M, n;					//	Time and space steps
	long double k, L, alpha;			//	Heat conduction parameters
	long double h, s;				//	Derived parameters
	Matrix *A;					//	This is the 2I + sB matrix
	Matrix *Ainv;				//	This is the inverse of A
	Matrix *B;					//	This is the 2I - sB matrix
	Matrix *AinvB;				//	This is the product of Ainv and B
	long double *xAxis;
	long double *yAxisTempData;
	int printFlag;
} HeatData;

void InputPrompter(HeatData *myData);
//long double** InvertMatrix(long double** inputMatrix);
//long double** MatrixOfMinors(long double** inputMatrix, int n);
//long double** MatrixOfCofactors(long double** inputMatrix, int n);
//long double Determinant(long double** inputMatrix, int n);
void GarbageCollect(HeatData *myData);
#endif