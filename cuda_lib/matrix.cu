#include "matrix.h"


using namespace std;
/*
LIMITE 6144 double ou 49152 bytes 32 THREAD MAX
                                  64 block max
*/

__global__ void multiply(double * A, double * B, double * C,int local_size)
{
    extern __shared__ double shared[];

    double * intern_A = &shared[0];
    double * intern_B = &shared[local_size];
    
    int col =  blockIdx.x * blockDim.x + threadIdx.x;
    int row =  blockIdx.y * blockDim.y + threadIdx.y;

    intern_A[threadIdx.y*blockDim.x + threadIdx.x] = A[row*DIM + threadIdx.x+blockDim.x*blockIdx.z];
    intern_B[threadIdx.y*blockDim.x + threadIdx.x] = B[(threadIdx.y+blockDim.y*blockIdx.z)*DIM + col];

    double result = 0.0;
    for(int i=0; i<blockDim.x; i++)
    {
        result+= intern_A[threadIdx.y*blockDim.x + i]*intern_B[i*blockDim.x  + threadIdx.x];
    }

    C[blockIdx.z*DIM*DIM + row*DIM + col] = result;

}
__global__ void sum(double * C, int n)
{
    int col =  blockIdx.x * blockDim.x + threadIdx.x;
    int row =  blockIdx.y * blockDim.y + threadIdx.y;
    for(int i=1;i<n;i++) C[row*DIM + col] += C[DIM*DIM*i+row*DIM + col];
}

void matrix_multiplication(double * a, double * b, double * c, int dim)
{
    double * result = (double *) malloc(sizeof(double)*dim*dim);

    int blocksNb  = (int) dim/8;
    int threadsNb = (int) 8;
    int sharedMemory = threadsNb*threadsNb*sizeof(double)*2;

    double * d_a; cudaMalloc((void **) &d_a, sizeof(double)*dim*dim);
    double * d_b; cudaMalloc((void **) &d_b, sizeof(double)*dim*dim);
    double * d_c; cudaMalloc((void **) &d_c, sizeof(double)*dim*dim*blocksNb);

    cudaMemcpy(d_a, a, sizeof(double)*dim*dim, cudaMemcpyHostToDevice);
    cudaMemcpy(d_b, b, sizeof(double)*dim*dim, cudaMemcpyHostToDevice);

    dim3 multiply_threadsPerBlock(threadsNb, threadsNb);
    dim3 multiply_blocksPerGrid(blocksNb, blocksNb,blocksNb);
    dim3 sum_threadsPerBlock(threadsNb,threadsNb);
    dim3 sum_blocksPerGrid(blocksNb,blocksNb);

    multiply<<<multiply_blocksPerGrid, multiply_threadsPerBlock, sharedMemory>>>(d_a, d_b, d_c, threadsNb*threadsNb);
    sum<<<sum_blocksPerGrid, sum_threadsPerBlock>>>(d_c, blocksNb);

    cudaMemcpy(result, d_c, sizeof(double)*dim*dim, cudaMemcpyDeviceToHost);

    for(int i=0;i<dim;i++) for(int j=0;j<dim;j++) c[i*dim + j] = result[i*dim + j];

    free(result);
    cudaFree(d_a);
    cudaFree(d_b);
    cudaFree(d_c);
    
}


