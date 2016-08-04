#ifndef MISCFUNCTIONS_H
#define MISCFUNCTIONS_H

void BuildTriDiag(double **matrix, double **matrixB, int n, double s, int printFlag);
void InputPrompter(double *alpha, double *k, double *L, int *M, int *n);
int MallocMatrix(double **matrixA, double **matrixB, double *xAxis, double *yAxis, int n, double h, double L);
double** InvertMatrix(double **matrixInput, double **matrixOutput);
double Determinant(double **matrixInput);
#endif