#include <stdlib.h>
#include "MiscFunctions.h"

int main()
{
	HeatData myData;

	puts("I have not currently implemented the linear algebra routines.");
	puts("I have functions declared to computer minors, cofactors and determinants of the nxn matrix but they are not yet implemented.");
	puts("More work is needed before this code really does anything beyond prompt for inputs.\n");

	//	Prompt the user for inputs and allocate memory for matrices
	InputPrompter(&myData);

	//	Allocate the matrix and x-axis values
	int memoryAllocatedFlag = MallocMatrix(&myData);
	
	//	Build the matrices
	BuildTriDiag(&myData);

	//	Clean up the garbage
	GarbageCollect(&myData);
	return 0;
}