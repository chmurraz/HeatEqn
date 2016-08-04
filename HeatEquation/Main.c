#include <stdlib.h>
#include "MiscFunctions.h"

int main()
{
	int M, n;						//	Time and space mesh variables
	int i, j, count = 0;			//	For loop variables
	double k, L, alpha;				//	Time step

	//	Prompt the user for inputs
	InputPrompter(&alpha, &k, &L, &M, &n);
	
	//	Allocate memory for the matrix and x-coordinate data
	double **matrixA = (double **)malloc((n + 2) * sizeof(double*));
	double **matrixB = (double **)malloc((n + 2) * sizeof(double*));
	double *xAxis = (double *)malloc((n + 2) * sizeof(double));
	double *yAxis = (double *)malloc((n + 2) * sizeof(double));

	//	Now use the user inputs to create the matrix
	double h = L / (n + 1);
	double s = k*alpha / (pow(h, 2));

	//	Allocate the matrix and x-axis values
	int memoryAllocatedFlag = MallocMatrix(matrixA, matrixB, xAxis, yAxis, n, h, L);
	
	//	Build the matrices
	BuildTriDiag(matrixA, matrixB, n, s, 1);



			

	free(matrixA);
	free(matrixB);
	free(xAxis);
	free(yAxis);
	return 0;
}