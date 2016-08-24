#include <stdlib.h>
#include <string.h>
#include "MiscFunctions.h"

/*
	THIS PROGRAM CALCULATES SOLUTIONS TO THE ONE DIMENSIONAL HEAT CONDUCTION EQUATION
	WITH DIRICHLET BOUNDARY CONDITIONS USING THE CRANK NICOLSON NUMERICAL METHOD

	THE USER IS PROMPTED FOR INPUTS:
		M:		The number of time steps
		n:		The number of internal spacial mesh points (not counting the end points of the rod)
		k:		The time step
		L:		The rod length
		alpha:	The thermal diffusivity

	DATA IS WRITTEN TO A TEXT FILE (HEATDATA.TXT) IN COMMA DELIMITED FORMAT

	THE FIRST ROW IS THE X-AXIS DATA
	THE SECOND ROW IS THE INITIAL TEMPERATURE DISTRIBUTION (AT TIME T = 0)
	THE NEXT ROWS ARE THE TEMPERATURE DISTRIBUTION (AT TIMES T = X * M WHERE X = 0.1, 0.2, ... 0.9, 1.0)

	NOTE:  TO CHANGE THE INITIAL TEMPERATURE DISTRIBUTION, EDIT THE FUNCTION 'InitialTemp' located in 'MiscFunctions.c'
*/

int main()
{
	HeatData myData;

	//	Prompt the user for inputs and allocate memory for matrices
	InputPrompter(&myData);

	//	Build the tridiagonal matrices used to solve for the temperature at each time step
	long double s = myData.s;
	BuildTriDiag(myData.A, -1 * s, 2 + 2*s, -1 * s);
	BuildTriDiag(myData.B, s, 2 - 2 * s, s);

	//	Calculate the inverse of the matrix A
	Invert(myData.A, myData.Ainv);

	//	Calculate the product of Ainv and B
	MatrixProduct(myData.Ainv, myData.B, myData.AinvB);

	//	Iteratively multiply the temp condition by the matrix product and write the data to a file
	WriteToFile(&myData);
	
	//	Clean up the garbage
	GarbageCollect(&myData);
	return 0;
}