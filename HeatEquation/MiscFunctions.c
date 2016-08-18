#include "MiscFunctions.h"
#include <stdio.h>
#include <math.h>

void InputPrompter(HeatData *myData)
{
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

	//	Now use the user inputs to create the derived parameters
	myData->h = myData->L / (myData->n + 1);
	myData->s = myData->k*myData->alpha / (pow(myData->h, 2));

	//	Allocate memory for the dynamic variables
	myData->matrixA = (double **)malloc((myData->n + 1) * sizeof(double*));
	myData->matrixB = (double **)malloc((myData->n + 1) * sizeof(double*));
	myData->xAxis = (double *)malloc((myData->n + 1) * sizeof(double));
	myData->yAxisTempData = (double *)malloc((myData->n + 1) * sizeof(double));

	//	Set matrix print flag to 1 (true) by default
	myData->printFlag = 1;
}

int MallocMatrix(HeatData *myData)
{
	int i, j;
	double pi = 3.14159;
	for (i = 0; i < myData->n + 1; i++)
	{
		myData->matrixA[i] = (double *)malloc((myData->n + 1) * sizeof(double));
		myData->matrixB[i] = (double *)malloc((myData->n + 1) * sizeof(double));
		myData->xAxis[i] = myData->h*i;
		myData->yAxisTempData[i] = 50 * myData->h*i * sin(2 * pi*myData->h*i / myData->L) + 15;
	}

	if (myData->matrixA == NULL || myData->matrixB == NULL || myData->xAxis == NULL || myData->yAxisTempData == NULL)
	{
		puts("Memory allocation error");
		return 0;
	}
	return 1;
}

void BuildTriDiag(HeatData *myData)
{
	//	Fill the matrix with zeros
	int i, j, count;
	for (i = 0; i < myData->n + 1; i++)
		for (j = 0; j < myData->n + 1; j++)
		{
			myData->matrixA[i][j] = 0;
			myData->matrixB[i][j] = 0;
		}
			

	//	Fill the diagonal and off diagonals
	for (i = 0; i < myData->n + 1; i++)
	{
		for (j = 0; j < myData->n + 1; j++)
		{
			if (i == j)
			{
				myData->matrixA[i][j] = 2+2 * myData->s;
				myData->matrixB[i][j] = 2-2 * myData->s;
			}
				
			if ((j == (i - 1)) || (j == (i + 1)))
			{
				myData->matrixA[i][j] = -1 * myData->s;
				myData->matrixB[i][j] = myData->s;
			}
				
		}
	}

	//	Print the contents of the matrix to the console if flag == 1
	if (myData->printFlag == 1)
	{
		count = 0;
		for (i = 0; i < myData->n + 1; i++)
			for (j = 0; j < myData->n + 1; j++)
			{
				count++;
				printf("%lf", myData->matrixA[i][j]);
				if (count % (myData->n + 1) == 0)
					printf("\n");
			}
		count = 0;
		for (i = 0; i < myData->n + 1; i++)
			for (j = 0; j < myData->n + 1; j++)
			{
				count++;
				printf("%lf", myData->matrixB[i][j]);
				if (count % (myData->n + 1) == 0)
					printf("\n");
			}
	}
}

double** InvertMatrix(double** inputMatrix)
{

	return NULL;
}

double ** MatrixOfMinors(double** inputMatrix, int n)
{
	return NULL;
}

double ** MatrixOfCofactors(double ** inputMatrix, int n)
{
	return NULL;
}

double Determinant(double** inputMatrix, int n)
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
	double **minor = (double **)malloc((n + 1) * sizeof(double*));
	double *cofactor = (double **)malloc(n * sizeof(double));
	for (i = 0; i <= n+1; i++)
	{
		minor[i] = (double **)malloc(n * sizeof(double));
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

void GarbageCollect(HeatData myData)
{
	int i;
	for (i = 0; i < myData.n + 1; i++)
	{
		free(myData.matrixA[i]);
		free(myData.matrixB[i]);
	}
	free(myData.matrixA);
	free(myData.matrixB);
	free(myData.xAxis);
	free(myData.yAxisTempData);
}
