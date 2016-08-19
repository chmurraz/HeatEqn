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
	myData->h = myData->L / (myData->n + 2);
	myData->s = myData->k*myData->alpha / (pow(myData->h, 2));

	//	Allocate memory for the dynamic variables
	myData->matrixA = (double **)malloc((myData->n + 2) * sizeof(double*));
	myData->matrixB = (double **)malloc((myData->n + 2) * sizeof(double*));
	myData->xAxis = (double *)malloc((myData->n + 2) * sizeof(double));
	myData->yAxisTempData = (double *)malloc((myData->n + 2) * sizeof(double));

	//	Set matrix print flag to 1 (true) by default
	myData->printFlag = 1;
}

int MallocMatrix(HeatData *myData)
{
	int i, j;
	double pi = 3.14159;
	for (i = 0; i < myData->n + 2; i++)
	{
		myData->matrixA[i] = (double *)malloc((myData->n + 2) * sizeof(double));
		myData->matrixB[i] = (double *)malloc((myData->n + 2) * sizeof(double));
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
	for (i = 0; i < myData->n + 2; i++)
		for (j = 0; j < myData->n + 2; j++)
		{
			myData->matrixA[i][j] = 0;
			myData->matrixB[i][j] = 0;
		}
			

	//	Fill the diagonal and off diagonals
	for (i = 0; i < myData->n + 2; i++)
	{
		for (j = 0; j < myData->n + 2; j++)
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
		puts("\nMatrixA:\n");
		for (i = 0; i < myData->n + 2; i++)
			for (j = 0; j < myData->n + 2; j++)
			{
				count++;
				printf("%lf  ", myData->matrixA[i][j]);
				if (count % (myData->n + 2) == 0)
					printf("\n");
			}

		count = 0;
		puts("\nMatrixB:\n");
		for (i = 0; i < myData->n + 2; i++)
			for (j = 0; j < myData->n + 2; j++)
			{
				count++;
				printf("%lf  ", myData->matrixB[i][j]);
				if (count % (myData->n + 2) == 0)
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
	//	This is recursive definition of the determinant SPECIFICALLY
	//	for tridiagonal matrices

	if (n == 0)
		return 1.0;
	if (n == -1)
		return 0.0;
	else
	{
		//	The formula is fN = aN*f(N-1) - c(N-1)*b(N-1)*f(N-2)
		//	where a is the main diagonal
		//	where b is the superior off diagonal
		//	where c is the inferior off diagonal
		//	and the terminal recursion relation is f(0) = 1 and f(-1) = 0

		double termOne = Determinant(inputMatrix, n - 1) * inputMatrix[n][n];
		double termTwo = -1 * inputMatrix[n][n - 1] * inputMatrix[n - 1][n] * Determinant(inputMatrix, n - 2);
		return  termOne + termTwo;
	}
	return 0.0;
}

void GarbageCollect(HeatData myData)
{
	int i;
	for (i = 0; i < myData.n + 2; i++)
	{
		free(myData.matrixA[i]);
		free(myData.matrixB[i]);
	}
	free(myData.matrixA);
	free(myData.matrixB);
	free(myData.xAxis);
	free(myData.yAxisTempData);
}
