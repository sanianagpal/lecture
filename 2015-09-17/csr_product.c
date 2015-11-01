#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef struct csr_t {
    int  n;      /* Dimension of matrix (assume square) */
    double* pr;  /* Array of matrix nonzeros (row major order) */
    int* col;    /* Column indices of nonzeros */
    int* ptr;    /* Offsets of the start of each row in pr
                    (ptr[n] = number of nonzeros) */
} csr_t;


void sparse_multiply(csr_t* A, double* x, double* result)
{
  memset(result, 0, A->n * sizeof(double));
  for (int i = 0; i < A->n; i++) 
    for (int j = A->ptr[i]; j < A->ptr[i+1];j++)
      result[i] += A->pr[j]*x[A->col[j]];
} 


int main()
{
    int n = 4;
    double pr[7]  = { 1.,-1.,  1.,-1.,  1.,-1.,  1. };
    int col[7]    = { 0,  1,   1,  2,   2,  3,   3  };
    int ptr[5]    = { 0, 2, 4, 6, 7 };
    csr_t A = { n, pr, col, ptr };
    double x[4] = {1., 3., 8., 12.};
    double result[4];
    sparse_multiply(&A, x, result);

    /*
     * Should compute
     * [1,  -1,  0,  0 ]   [ 1  ]    [-2]
     * [ 0,  1, -1,  0 ] * [ 3  ]  = [-5]
     * [ 0,  0,  1, -1 ]   [ 8  ]    [-4]
     * [ 0,  0,  0,  1 ]   [ 12 ]    [12]
     */
    for (int i = 0; i < n; ++i)
        printf(" %g\n", result[i]);
}
