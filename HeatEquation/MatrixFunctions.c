#include "MatrixFunctions.h"

//	This function allocates memory for a Matrix struct and populates it with zeros
Matrix * MatrixAlloc(int n)
{
	//	Allocate the matrix memory
	Matrix *m = malloc(sizeof(Matrix));
	m->n = n;

	//	Allocate the matrix data
	m->cols = malloc(n * n * sizeof(long double));

	//	Allocate and fill the m->rows
	m->rows = malloc(n * sizeof(long double*));
	for (int i = 0; i < n; i++)
	{
		m->rows[i] = &m->cols[i * n];
	}

	//	Set the matrix values to zero
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			m->rows[i][j] = 0.0;
		}
	}

	return m;
}

//	This function frees the memory
void MatrixFree(Matrix * m)
{
	free(m->rows);
	free(m->cols);
	free(m);
}

//	This function builds a tridiagonal matrix.  It fills the main diagonal with main, inferior diagonal with inferior, etc.
void BuildTriDiag(Matrix * m, long double inferior, long double main, long double superior)
{
	//	Set the matrix values to zero
	for (int i = 0; i < m->n; i++)
	{
		for (int j = 0; j < m->n; j++)
		{
			if (i == j)
				m->rows[i][j] = main;

			if (j == (i - 1))
				m->rows[i][j] = inferior;

			if (j == (i + 1))
				m->rows[i][j] = superior;
		}
	}
}

//	This function prints a matrix to the console for debugging
void PrintMatrix(Matrix * m)
{
	int count = 0;
	for (int i = 0; i < m->n; i++)
		for (int j = 0; j < m->n; j++)
		{
			count++;
			printf("%lf  ", m->rows[i][j]);
			if (count % (m->n) == 0)
				printf("\n");
		}
	printf("\n");
}

//	This function returns the determinant of a matrix.  It is recursive and VERY inefficient.
long double Determinant(Matrix * m, int n)
{
	//	NOTE:  This algorithm is expecting n to be the mathematical size of the matrix
	//			and not the C size of the array.  In other words, send 5 for a the size
	//			of an array indexed from a[0], a[1], a[2], a[3] and a[4]
	if (n == 0)
		return 1.0;
	if (n == -1)
		return 0.0;
	else
	{
		//	Extract the diagonal element
		long double aN = m->rows[n - 1][n - 1];

		//	Extract the superior and inferior diagonals only if n>=2
		//	Otherwise, set them to zero.  They are not needed since fN = 0
		long double bN = 0;
		long double cN = 0;
		if (n >= 2)
		{
			bN = m->rows[n - 2][n - 1];
			cN = m->rows[n - 1][n - 2];
		}

		return aN * Determinant(m, n - 1) - cN*aN*Determinant(m, n - 2);
	}
}

//	This function inverts a matrix using Gauss-Jordan row reduction
void Invert(Matrix *m, Matrix *T)
{
	int n = m->n;

	//	Step 0:  Create a temporary matrix that is a copy of the original matrix m
	Matrix *temp = MatrixAlloc(n);
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
			temp->rows[i][j] = m->rows[i][j];

	//	Step 1:  Populate the target matrix with an identy matrix
	for (int i = 0; i < n; i++)
		T->rows[i][i] = 1.0;

	//	Step 2:  Starting with the [0][0] entry as the pivot, zero out the lower triangle
	long double scale;
	long double scale2;
	for (int i = 0; i < n; i++)
	{
		scale = temp->rows[i][i];
		for (int j = 0; j < n; j++)
		{
			temp->rows[i][j] *= 1 / scale;
			T->rows[i][j] *= 1 / scale;
		}

		//	Next, do row operations as long as we're not on the last row
		for (int i2 = i + 1; i2 < n; i2++)
		{
			//	If the leading entry in this row is not zero, eliminate it
			if (temp->rows[i2][i] != 0.0)
			{
				scale2 = temp->rows[i2][i];
				for (int j = 0; j < n; j++)
				{
					temp->rows[i2][j] -= scale2 * temp->rows[i][j];
					T->rows[i2][j] -= scale2 * T->rows[i][j];
				}
			}

		}		
	}

	//	At this point, the matrix should be upper triangular with 1s on the diagonals.

	//	Step 3:  Starting with the [n-1][n-1] entry as the pivot, zero out the upper triangle
	for (int i = n - 1; i >= 0; i--)
	{

		//	Next, do row operations as long as we're not on the last row
		for (int i2 = i - 1; i2 >= 0; i2--)
		{
			//	If the leading entry in this row is not zero, eliminate it
			if (temp->rows[i2][i] != 0.0)
			{
				scale2 = temp->rows[i2][i];
				for (int j = 0; j < n; j++)
				{
					temp->rows[i2][j] -= scale2 * temp->rows[i][j];
					T->rows[i2][j] -= scale2 * T->rows[i][j];
				}
			}
		}
	}
	MatrixFree(temp);
}

//	This function calculates the product of two matrices a and b and stores the result in target T
void MatrixProduct(Matrix * a, Matrix * b, Matrix *T)
{
	int n = a->n;
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
		{
			for (int x = 0; x < n; x++)
					T->rows[i][j] += a->rows[i][x] * b->rows[x][j];
		}
}

//	This function stores the product of a matrix a with a vector v and OVERWRITES the original vector v
void MatrixVectorProduct(Matrix * a, long double * v)
{
	int n = a->n;

	//	Allocate a temporary array
	long double *temp = (long double *)malloc(n * sizeof(long double));
	for (int i = 0; i < n; i++)
		temp[i] = 0;

	for(int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
		{
			temp[i] += a->rows[i][j] * v[j];
		}

	for (int i = 0; i < n; i++)
		v[i] = temp[i];
	free(temp);
}