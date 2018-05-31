#include "../../include/cuvector.h"
#include "../../include/CUDA_CONSTANT.h"
#include <iostream>


template<typename T> __global__ void cuda_copy(T* dest, T* src)
{
    int index = blockIdx.x * blockDim.x + threadIdx.x;
    dest[index] = src[index];
};


template<typename T>
CuVector<T>::CuVector(int size)
{
    m_maxsize = sizeChecking(size);
    m_size = 0;
    cudaMalloc((void **) &m_data, sizeof(T)*size);
}

template<typename T>
CuVector<T>::CuVector(std::vector <T> data)
{
    m_maxsize = sizeChecking(data.capacity());
    m_size = data.size();
    cudaMalloc((void **) &m_data, sizeof(T)*m_maxsize);
    cudaMemcpy(m_data, data.data(), sizeof(T)*data.size(), cudaMemcpyHostToDevice);
}

template<typename T>
CuVector<T>::CuVector(CuVector<T> const& copy)
{
    m_maxsize = sizeChecking(copy.m_maxsize);
    m_size = copy.m_size;
    cudaMalloc((void **) &m_data, sizeof(T)*m_maxsize);
    dim3 blocksPerGrid((m_maxsize/MAX_THREAD_BY_BLOCKS)+1,0,0);
    dim3 threadsPerBlocks(m_maxsize/(blocksPerGrid.x),0,0);
    cuda_copy<T><<<blocksPerGrid,threadsPerBlocks>>>(m_data,copy.m_data);
}

template<typename T>
CuVector<T>::~CuVector()
{
    cudaFree(m_data);
}



template<typename T>
int CuVector<T>::sizeChecking(int size)
{
    while( size%(size/MAX_THREAD_BY_BLOCKS +1)!=0) size++;
    return size;
}