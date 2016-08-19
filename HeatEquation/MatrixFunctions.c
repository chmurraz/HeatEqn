#include "MatrixFunctions.h"

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

void MatrixFree(Matrix * m)
{
	free(m->rows);
	free(m->cols);
	free(m);
}

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


}

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

void Invert(Matrix *m, Matrix *T, int n)
{
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= n; j++)
		{
			if (i < j)
			{
				T->rows[i-1][j-1] = (pow(-1, i+j));

				//	Multiply this by the product of the b's (the superior diagonal where bi = m[i-1][i])
				for (int b = i; b <= j - 1; b++)
				{
					T->rows[i-1][j-1] *= m->rows[b-1][b];
				}

				//	Multiply this by the theta and phi
				T->rows[i-1][j-1] *= Theta(m,i-1)*Phi(m,j+1)/Theta(m,n);				
			}
			if (i == j)
			{
				T->rows[i-1][j-1] = 1;
				T->rows[i-1][j-1] *= Theta(m, i - 1);
				T->rows[i-1][j-1] *= Phi(m, j + 1);
				T->rows[i-1][j-1] *= 1 / Theta(m, n);
			}
			if (i > j)
			{
				T->rows[i-1][j-1] = (pow(-1, i + j));

				//	Multiply this by the product of the c's (the inferior diagonal where cj = m[i][i-1])
				for (int c = j; c <= i - 1; c++)
				{
					T->rows[i-1][j-1] *= m->rows[c][c - 1];
				}

				//	Multiply this by the theta and phi
				T->rows[i-1][j-1] *= Theta(m, j - 1)*Phi(m, i + 1) / Theta(m, n);
			}
		}
}

long double Theta(Matrix * m, int n)
{
	if (n == 0)
		return 1;
	if (n == 1)
		return m->rows[0][0];
	else
	{
		//	Extract the diagonal element
		long double aN = m->rows[n - 1][n - 1];

		//	Extract the superior and inferior diagonals only if n>=2
		//	Otherwise, set them to one.  They are not needed since theta0 = 1
		long double bN = 1;
		long double cN = 1;
		if (n >= 2)
		{
			bN = m->rows[n - 2][n - 1];
			cN = m->rows[n - 1][n - 2];
		}

		return aN * Theta(m, n - 1) - cN*aN*Theta(m, n - 2);

	}
}

long double Phi(Matrix * m, int n)
{
	if (n == m->n+1)
		return 1;
	if (n == m->n)
		return m->rows[n-1][n-1];
	else
	{
		//	Extract the diagonal element
		long double aN = m->rows[n - 1][n - 1];

		//	Extract the superior and inferior diagonals only if n < the size of the matrix
		//	Otherwise, set them to one.  They are not needed since phi(N+1) = 1
		long double bN = 1;
		long double cN = 1;
		if (n < m->n)
		{
			bN = m->rows[n - 1][n];
			cN = m->rows[n][n - 1];
		}

		return aN * Phi(m, n + 1) - cN*aN*Phi(m, n + 2);

	}
}

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
