#ifndef MISCFUNCTIONS_H
#define MISCFUNCTIONS_H

void BuildTriDiag(double **matrix, int n, double diag, double offDiag, int printFlag);
void InputPrompter(double *alpha, double *k, double *L, int *M, int *n);
int MallocMatrix(double **matrix, int n);

#endif