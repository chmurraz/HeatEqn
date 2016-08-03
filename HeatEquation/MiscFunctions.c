#include "MiscFunctions.h"
#include <stdio.h>

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

int MallocMatrix(double ** matrix, int n)
{
	int i, j;
	for (i = 0; i < n + 2; i++)
		matrix[i] = (double *)malloc((n + 2) * sizeof(double));

	if (matrix == NULL)
	{
		puts("Memory allocation error");
		return 0;
	}
	return 1;
}

void BuildTriDiag(double ** matrix, int n, double diag, double offDiag, int printFlag)
{
	//	Fill the matrix with zeros
	int i, j, count;
	for (i = 0; i < n + 2; i++)
		for (j = 0; j < n + 2; j++)
			matrix[i][j] = 0;

	//	Fill the diagonal and off diagonals
	for (i = 0; i < n + 2; i++)
	{
		for (j = 0; j < n + 2; j++)
		{
			if (i == j)
				matrix[i][j] = diag;
			if ((j == (i - 1)) || (j == (i + 1)))
				matrix[i][j] = offDiag;
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
				printf("%lf ", matrix[i][j]);
				if (count % (n + 2) == 0)
					printf("\n");
			}
	}
}

