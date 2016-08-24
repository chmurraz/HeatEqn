#ifndef MISCFUNCTIONS_H
#define MISCFUNCTIONS_H

#include "MatrixFunctions.h"

typedef struct
{
	int M, n;							//	Time and space steps
	long double k, L, alpha;			//	Heat conduction parameters
	long double h, s;					//	Derived parameters
	Matrix *A;							//	This is the 2I + sB matrix
	Matrix *Ainv;						//	This is the inverse of A
	Matrix *B;							//	This is the 2I - sB matrix
	Matrix *AinvB;						//	This is the product of Ainv and B
	long double *xAxis;					//	This is x-axis data
	long double *yAxisTempData;			//	This is the temperature data at the current time step
	int printFlag;						//	Print to console flag, used during debugging
} HeatData;

void InputPrompter(HeatData *myData);
long double InitialTemp(long double x, HeatData *myData);
void BoundaryConditions(HeatData *myData);
void GarbageCollect(HeatData *myData);
void WriteToFile(HeatData *myData);
#endif