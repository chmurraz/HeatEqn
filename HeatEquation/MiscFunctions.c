#include "MiscFunctions.h"


void InputPrompter(HeatData *myData)
{
	/*
	printf_s("Enter 'M' the number of time steps\n");
	scanf_s("%d", &(myData->M));
	printf("Enter 'n' the number of internal spacial mesh points.\nNote, the code will use (n+2) mesh points.\nThis includes the n internal mesh points and two additional boundary points: x0 and xn.\n");
	scanf_s("%d", &(myData->n));
	printf("Enter 'k' the time step.");
	scanf_s("%lf", &(myData->k));
	printf("Enter 'L' the rod length.");
	scanf_s("%lf", &(myData->L));
	printf("Enter 'alpha' the thermal diffusivity.");
	scanf_s("%lf", &(myData->alpha));
	*/

	myData->M = 5;
	myData->n = 50;
	myData->L = 5;
	myData->k = 0.1;
	myData->alpha = 0.1;

	//	Now use the user inputs to create the derived parameters
	//	NOTE:  n tracks the number of internal mesh points (not including x0 and xn)
	//	so the value of h is calculated on (n+1) and not n or (n+2)
	myData->h = myData->L / (myData->n + 1);
	myData->s = myData->k*myData->alpha / (pow(myData->h, 2));

	//	Allocate memory for the dynamic variables.
	//	NOTE:  If there are n internal mesh points, then there are a system of
	//	(n+2) equations, requring an (n+2) matrix.
	myData->A = MatrixAlloc(myData->n+2);
	myData->Ainv = MatrixAlloc(myData->n + 2);
	myData->B = MatrixAlloc(myData->n+2);
	myData->AinvB = MatrixAlloc(myData->n + 2);
	myData->xAxis = (long double *)malloc((myData->n + 2) * sizeof(long double));
	myData->yAxisTempData = (long double *)malloc((myData->n + 2) * sizeof(long double));

	//	Populate the x- and y-axis data
	for (int i = 0; i < myData->n + 2; i++)
	{
		long double x = i*myData->h;
		myData->xAxis[i] = x;
		myData->yAxisTempData[i] = 50 * x*sin(2 * PI*x / myData->L) + 15;
	}


	//	Set matrix print flag to 1 (true) by default
	myData->printFlag = 1;
}

/*

long double** InvertMatrix(long double** inputMatrix)
{

	return NULL;
}

long double ** MatrixOfMinors(long double** inputMatrix, int n)
{
	return NULL;
}

long double ** MatrixOfCofactors(long double ** inputMatrix, int n)
{
	return NULL;
}

long double Determinant(long double** inputMatrix, int n)
{
	int i,j,k;

	//	STEP 1:	Search the matrix for the row or column with the largest number of zeros in it
	//			Assume the 0th row is the maximum to begin with

	int maxZeroLocation = 0;
	int maxZeroCount = 0;
	int zeroCount;
	for (i = 0; i < n + 1; i++)
	{
		//	Count the zeros in the ith row
		zeroCount = 0;
		for (j = 0; i < n + 1; j++)
		{
			if (inputMatrix[i][j] == 0)
				zeroCount++;
		}
		//	Update the max and store row location, if applicable
		if (zeroCount > maxZeroCount)
		{
			maxZeroCount = zeroCount;
			maxZeroLocation = i;
		}
			

		//	Count the zeros in the ith column
		zeroCount = 0;
		for (j = 0; j < n + 1; j++)
		{
			if (inputMatrix[j][i] == 0)
				zeroCount++;
		}
		//	Update the max and store col location, if applicable
		if (zeroCount > maxZeroCount)
		{
			maxZeroCount = zeroCount;
			maxZeroLocation = -1*i;
		}
	}

	//	CONCLUSION STEP 1:
	//	If maxZeroLocation is +x then the xth row has the most zeros
	//	If maxZeroLocation is -x then the xth col has the most zeros
	//	If there are no zeros in the matrix, then the 0th row will be used by default.

	//	STEP 2:  Expand the determinant (recursively) about this optimal row/column





	//	Allocate memory for pointer variables to store the cofactor and minor matrices for the input matrix
	long double **minor = (long double **)malloc((n + 1) * sizeof(long double*));
	long double *cofactor = (long double **)malloc(n * sizeof(long double));
	for (i = 0; i <= n+1; i++)
	{
		minor[i] = (long double **)malloc(n * sizeof(long double));
	}

	//	Loop through and initialize the cofactor and matrix minors
	for (i = 0; i <= n + 1; i++)
	{
		cofactor[i] = ((-1) ^ i)*inputMatrix[0][i];
		for (j = 0; j <= n; j++)
			for (k = 0; k <= n; k++)
			{
				if (k < i)
					minor[j][k] = inputMatrix[i + 1][k];
				if (k > i)
					minor[j][k] = inputMatrix[i + 1][k+1];
			}
	}

	//	Free the memory
	for (i = 0; i <= n + 1; i++)
	{
		free(minor[i]);
	}
	free(minor);
	free(cofactor);




	//	Allocate memory for an (n) x (n) matrix composed of all elements of the original matrix
	//	except for the first row and ith column.  Note this matrix dimension is
	//	one less than the original matrix (n+1) x (n+1).  This is the minor matrix

	//	If n-2 = 2, compute the determinant of the minor matrix via formula.
	//	If n-2 > 2, compute the determinant of the minor matrix recursively

	//	Multiply the cofactor by the determinant of the minor matrix and sum the results.

	return 0.0;
}

*/

void GarbageCollect(HeatData *myData)
{
	MatrixFree(myData->A);
	MatrixFree(myData->Ainv);
	MatrixFree(myData->B);
	free(myData->xAxis);
	free(myData->yAxisTempData);
}