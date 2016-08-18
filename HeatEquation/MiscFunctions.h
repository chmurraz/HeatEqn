#ifndef MISCFUNCTIONS_H
#define MISCFUNCTIONS_H

typedef struct
{
	int M, n;					//	Time and space steps
	double k, L, alpha;			//	Heat conduction parameters
	double h, s;				//	Derived parameters
	double **matrixA;			//	This is the 2I + sB matrix
	double **matrixB;			//	This is the 2I - sB matrix
	double *xAxis;
	double *yAxisTempData;
	int printFlag;
} HeatData;

void BuildTriDiag(HeatData *myData);
void InputPrompter(HeatData *myData);
int MallocMatrix(HeatData *myData);
double** InvertMatrix(double** inputMatrix);
double** MatrixOfMinors(double** inputMatrix, int n);
double** MatrixOfCofactors(double** inputMatrix, int n);
double Determinant(double** inputMatrix, int n);
void GarbageCollect(HeatData myData);
#endif