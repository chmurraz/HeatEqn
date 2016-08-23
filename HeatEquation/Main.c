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

	Matrix *test = MatrixAlloc(3);
	Matrix *test2 = MatrixAlloc(3);
	test->rows[0][0] = 1;
	test->rows[0][1] = 4;
	test->rows[0][2] = -2;
	test->rows[1][0] = -1;
	test->rows[1][1] = 1;
	test->rows[1][2] = -1;
	test->rows[2][0] = 3;
	test->rows[2][2] = 1;

	long double *test3 = (long double *)malloc((3) * sizeof(long double));
	test3[0] = 1;
	test3[1] = 2;
	test3[2] = 5;

	//MatrixVectorProduct(test, test3);

	PrintMatrix(test);
	Invert(test, test2);
	PrintMatrix(test2);

	MatrixFree(test);
	MatrixFree(test2);

	//	Calculate the inverse of the matrix A
	Invert(myData.A, myData.Ainv);
	PrintMatrix(myData.A);
	PrintMatrix(myData.Ainv);

	MatrixProduct(myData.Ainv, myData.A, myData.AinvB);
	PrintMatrix(myData.AinvB);

	//	Calculate the product of Ainv and B
	MatrixProduct(myData.Ainv, myData.B, myData.AinvB);


	//	Iteratively multiply the temp condition by the matrix product
	WriteToFile(&myData);


	//	Clean up the garbage
	GarbageCollect(&myData);
	return 0;
}