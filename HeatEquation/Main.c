#include <stdlib.h>
#include <string.h>
#include "MiscFunctions.h"

int main()
{
	HeatData myData;

	//puts("I have not currently implemented the linear algebra routines.");
	//puts("I have functions declared to computer minors, cofactors and determinants of the nxn matrix but they are not yet implemented.");
	//puts("More work is needed before this code really does anything beyond prompt for inputs.\n");

	//	Prompt the user for inputs and allocate memory for matrices
	InputPrompter(&myData);

	//	Build the tridiagonal matrix
	long double s = myData.s;
	BuildTriDiag(myData.A, -1 * s, 2 + 2*s, -s);
	BuildTriDiag(myData.B, s, 2 - 2 * s, s);

	//	Print stuff
	//if (myData.printFlag == 1)
	//{
	//	PrintMatrix(myData.A);
	//	printf("\n");
	//	PrintMatrix(myData.B);
	//}
	
	//	Calculate the determinant of the tridiagonal matrix
	//long double det = Determinant(myData.A,myData.A->n);

	//	Calculate the inverse of the matrix A
	Invert(myData.A, myData.Ainv, myData.A->n);

	//	Calculate the product of Ainv and B
	MatrixProduct(myData.Ainv, myData.B, myData.AinvB);

	//printf("\n");
	//PrintMatrix(myData.Ainv);

	//printf("\n");
	//PrintMatrix(myData.AinvB);

	//	Iteratively multiply the temp condition by the matrix product

	//	Write temp data to a file
	FILE *pFile;

	pFile = fopen("test.txt", "w");

	if (pFile != NULL)
	{
		for (int i = 0; i < myData.n + 2; i++)
		{
			fprintf(pFile, "%lf", myData.xAxis[i]);
			if (i < myData.n + 1)
				fprintf(pFile, ", ");
		}

		fprintf(pFile, "\n");

		for (int i = 0; i < myData.n + 2; i++)
		{
			fprintf(pFile, "%lf", myData.yAxisTempData[i]);
			if (i < myData.n + 1)
				fprintf(pFile, ", ");
		}
		fclose(pFile);
	}

	//	Clean up the garbage
	GarbageCollect(&myData);
	return 0;
}