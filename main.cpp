#include "matrix.h"


void showMatrix(double *matrix,int n, int m)
{
    for(int a = 0;a< n;a++)
        {
        for(int j = 0;j<m;j++)
            {
                printf(" %.2f ",matrix[m*a+j]);
            }
            printf("\n");
        } 
}

void gen_initial_matrix(double * matrix)
{
    for(int i=0;i<DIM;i++)  for(int k=0;k<DIM;k++)  matrix[i*DIM +k] = rand()%10000*0.0001;


}

int main(void)
{
    double * matrix_A = (double *) malloc(sizeof(double)*DIM*DIM);
    double * matrix_B = (double *) malloc(sizeof(double)*DIM*DIM);
    double * matrix_C = (double *) malloc(sizeof(double)*DIM*DIM);
    double * matrix_C_bis = (double *) malloc(sizeof(double)*DIM*DIM);
    gen_initial_matrix(matrix_A);
    gen_initial_matrix(matrix_B);

    matrix_multiplication( matrix_A, matrix_B, matrix_C,DIM );
    showMatrix(matrix_C,12,12);
    double * matrix_B_T = (double *) malloc(sizeof(double)*DIM*DIM);

    
    return 0;
}