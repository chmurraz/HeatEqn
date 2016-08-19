#include "MatrixFunctions.h"

Matrix * MatrixBuilder(int n)
{
	//	Allocate the matrix memory
	Matrix *m = malloc(sizeof(Matrix));
	m->n = n;

	//	Allocate the matrix data
	m->cols = malloc(n * n * sizeof(double));

	//	Allocate and fill the m->rows
	m->rows = malloc(n * sizeof(double*));
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

void BuildTriDiag(Matrix * m, double inferior, double main, double superior)
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
