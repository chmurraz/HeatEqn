#ifndef MATRIXFUNCTIONS_H
#define MATRIXFUNCTIONS_H

typedef struct
{
	int n;
	double **rows;
	double *cols;
} Matrix;

Matrix* MatrixBuilder(int n);
void MatrixFree(Matrix *m);
void BuildTriDiag(Matrix *m, double inferior, double main, double superior);

#endif
