#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "MiscFunctions.h"

int main()
{
	int M, n;					//	Time and space mesh variables
	int i,j,count = 0;			//	For loop variables
	double k, L, alpha;			//	Time step


	//	Prompt the user for inputs
	InputPrompter(&alpha, &k, &L, &M, &n);

	//	Now use the inputs to create the matrix
	double h = L / (n + 1);
	double s = k*alpha / (pow(h, 2));
	double diag = 2 + 2 * s;
	double offDiag = -1 * s;
	
	//	Allocate memory for the matrix
	double **matrix	= (double **)malloc((n + 2) * sizeof(double*));
	int memoryAllocatedFlag = MallocMatrix(matrix,n);

	//	
	BuildTriDiag(matrix, n, diag, offDiag, 1);



			

	free(matrix);
	return 0;
}