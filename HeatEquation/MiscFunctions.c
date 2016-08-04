#include "MiscFunctions.h"
#include <stdio.h>
#include <math.h>

void InputPrompter(double *alpha, double *k, double *L, int *M, int *n)
{
	printf("Enter 'M' the number of time steps\n");
	scanf_s("%d", M);
	printf("Enter 'n' the number of internal spacial mesh points.\nNote, the code will use (n+2) mesh points.\nThis includes the n internal mesh points and two additional boundary points: x0 and xn.\n");
	scanf_s("%d", n);
	printf("Enter 'k' the time step.");
	scanf_s("%lf", k);
	printf("Enter 'L' the rod length.");
	scanf_s("%lf", L);
	printf("Enter 'alpha' the thermal diffusivity.");
	scanf_s("%lf", alpha);
}

int MallocMatrix(double ** matrixA, double ** matrixB, double *xAxis, double *yAxis, int n, double h, double L)
{
	int i, j;
	double pi = 3.14159;
	for (i = 0; i < n + 2; i++)
	{
		matrixA[i] = (double *)malloc((n + 2) * sizeof(double));
		matrixB[i] = (double *)malloc((n + 2) * sizeof(double));
		xAxis[i] = h*i;
		yAxis[i] = 50 * h*i * sin(2 * pi*h*i / L) + 15;
	}

	if (matrixA == NULL || matrixB == NULL || xAxis == NULL)
	{
		puts("Memory allocation error");
		return 0;
	}
	return 1;
}

void BuildTriDiag(double ** matrixA, double **matrixB, int n, double s, int printFlag)
{
	//	Fill the matrix with zeros
	int i, j, count;
	for (i = 0; i < n + 2; i++)
		for (j = 0; j < n + 2; j++)
		{
			matrixA[i][j] = 0;
			matrixB[i][j] = 0;
		}
			

	//	Fill the diagonal and off diagonals
	for (i = 0; i < n + 2; i++)
	{
		for (j = 0; j < n + 2; j++)
		{
			if (i == j)
			{
				matrixA[i][j] = 2+2*s;
				matrixB[i][j] = 2-2*s;
			}
				
			if ((j == (i - 1)) || (j == (i + 1)))
			{
				matrixA[i][j] = -1*s;
				matrixB[i][j] = s;
			}
				
		}
	}

	//	Print the contents of the matrix to the console if flag == 1
	if (printFlag == 1)
	{
		count = 0;
		for (i = 0; i < n + 2; i++)
			for (j = 0; j < n + 2; j++)
			{
				count++;
				printf("%lf", matrixA[i][j]);
				if (count % (n + 2) == 0)
					printf("\n");
			}
	}

	if (printFlag == 1)
	{
		count = 0;
		for (i = 0; i < n + 2; i++)
			for (j = 0; j < n + 2; j++)
			{
				count++;
				printf("%lf", matrixB[i][j]);
				if (count % (n + 2) == 0)
					printf("\n");
			}
	}
}

double** InvertMatrix(double ** matrixInput, double ** matrixOutput)
{

	return NULL;
}

double Determinant(double ** matrixInput)
{
	return 0.0;
}
