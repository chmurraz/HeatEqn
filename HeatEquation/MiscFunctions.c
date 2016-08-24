#include "MiscFunctions.h"

//	This function returns the intitial temperature data
long double InitialTemp(long double x, HeatData * myData)
{
	return 50 * x * sin(2 * PI*x / myData->L) + 50;
}

//	This function holds the boundary conditions constant to whatever they were intially, based on the initial temperature distribution
void BoundaryConditions(HeatData * myData)
{
	myData->yAxisTempData[0] = InitialTemp(0, myData);
	myData->yAxisTempData[myData->n] = InitialTemp(myData->n, myData);
}

//	This function prompts the user for physical parameters such as length of the rod, time steps, space steps, and thermal diffusivity
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

	myData->M = 40000;
	myData->n = 50;
	myData->L = 5;
	myData->k = 0.125;
	myData->alpha = 0.001;

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

	//	Populate the x-axis mesh point data and the INITIAL y-axis data
	for (int i = 0; i < myData->n + 2; i++)
	{
		long double x = i*myData->h;
		myData->xAxis[i] = x;
		myData->yAxisTempData[i] = InitialTemp(x,myData);
	}

	//	Set matrix print flag to 1 (true) by default
	myData->printFlag = 1;
}

//	This function cleans up all memory allocations
void GarbageCollect(HeatData *myData)
{
	MatrixFree(myData->A);
	MatrixFree(myData->Ainv);
	MatrixFree(myData->B);
	free(myData->xAxis);
	free(myData->yAxisTempData);
}

//	This function writes data to a file
void WriteToFile(HeatData * myData)
{
	//	Write temp data to a file
	FILE *pFile;

	pFile = fopen("heatdata.txt", "w");

	if (pFile != NULL)
	{
		//	Write the x-axis data
		for (int i = 0; i < myData->n + 2; i++)
		{
			fprintf(pFile, "%lf", myData->xAxis[i]);
			if (i < myData->n + 1)
				fprintf(pFile, ", ");
		}
		fprintf(pFile, "\n");

		//	Write the initial temperature data
		for (int i = 0; i < myData->n + 2; i++)
		{
			fprintf(pFile, "%lf", myData->yAxisTempData[i]);
			if (i < myData->n + 1)
				fprintf(pFile, ", ");
		}
		fprintf(pFile, "\n");

		//	Iterate temperature data to new time step
		for (int i = 1; i <= myData->M; i++)
		{
			//	Update the temp data
			MatrixVectorProduct(myData->AinvB, myData->yAxisTempData);

			//	Re-assert the boundary conditions
			BoundaryConditions(myData);

			//	Write to file... but only if at 10% intervals
			if (i % (int)(0.1*myData->M) == 1)
			{
				for (int j = 0; j < myData->n + 2; j++)
				{
					fprintf(pFile, "%lf", myData->yAxisTempData[j]);
					if (j < myData->n + 1)
						fprintf(pFile, ", ");
				}
				fprintf(pFile, "\n");
			}
		}
		fclose(pFile);
	}
}
