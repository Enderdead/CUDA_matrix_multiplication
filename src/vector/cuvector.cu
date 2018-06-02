#include "../../include/cuvector.h"
#include "../../include/CUDA_CONSTANT.h"



template<typename T> __global__ void cuda_copy(T* dest, T* src)
{
    int index = blockIdx.x * blockDim.x + threadIdx.x;
    dest[index] = src[index];
};

template<typename T> __global__ void cuda_shift(T* data, int offset)
{
    int index = blockIdx.x * blockDim.x + threadIdx.x;
    T temp = data[index];
    cudaDeviceSynchronize();
    data[index+offset] = temp;
}

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
void CuVector<T>::show() const
{
    T * local = (T*) malloc(sizeof(T)*this->m_size);
    cudaMemcpy(local, m_data, sizeof(T)*this->m_size, cudaMemcpyDeviceToHost);
    for(int i=0;i<this->m_size;i++) std::cout<<local[i]<<" ";
    std::cout<<std::endl;
    free(local);
}

template<typename T>
T CuVector<T>::get(int i)
{
    if(i>=m_size) throw std::runtime_error("Index doesn't exist");
    T result;
    cudaMemcpy(&result, m_data+i, sizeof(T), cudaMemcpyDeviceToHost);
    return result;
}


template<typename T>
T CuVector<T>::pop_back(void)
{
    if(this->empty()) throw std::runtime_error("CuVector empty !");
    T result;
    cudaMemcpy(&result, m_data+m_size-1, sizeof(T), cudaMemcpyDeviceToHost);
    return result;
}


template <typename T>
T CuVector<T>::pop_front(void)
{
    if(this->empty()) throw std::runtime_error("CuVector empty !");
    T result;
    cudaMemcpy(&result, m_data, sizeof(T), cudaMemcpyDeviceToHost);
    for(int i=0;i<getBocksSize(m_maxsize); i++)
    {
        if(i==0) cuda_shift<<<1,getThreadsSize(m_maxsize)-1>>>(m_data, i*getThreadsSize(m_maxsize), -1, -1, this->capacity()+1);
        else cuda_shift<<<1,getThreadsSize(m_maxsize)>>>(m_data, i*getThreadsSize(m_maxsize), -1, -1, this->capacity()+1);
        cudaDeviceSynchronize();
    }
    m_size--;
    return result;
}

template<typename T>
void CuVector<T>::push_back(const T element)
{
    if(this->full()) throw std::runtime_error("CuVector full !");
    cudaMemcpy(m_data + m_size, &element, sizeof(T), cudaMemcpyHostToDevice);
    m_size++;

}

template<typename T>
void CuVector<T>::push_front(const T element)
{
    if(this->full()) throw std::runtime_error("CuVector full !");
    //TODO optimisé le nb de boucle
    for(int i=0;i<getBocksSize(m_maxsize); i++)
    {
        if(i==getBocksSize(m_maxsize)-1) cuda_shift<<<1,getThreadsSize(m_maxsize)-1>>>(m_data, i*getThreadsSize(m_maxsize), 1, -1, this->capacity()+1);
        else cuda_shift<<<1,getThreadsSize(m_maxsize)>>>(m_data, i*getThreadsSize(m_maxsize), 1, -1, this->capacity()+1);
        cudaDeviceSynchronize();
    }

    cudaMemcpy(m_data, &element, sizeof(T), cudaMemcpyHostToDevice);

    m_size++;
}

template<typename T>
int CuVector<T>::sizeChecking(int size)
{
    while( size%(size/MAX_THREAD_BY_BLOCKS +1)!=0) size++;
    return size;
}


template <typename T>
int CuVector<T>::getBocksSize(int size)
{
    return ((int) (std::ceil(  ((float) size) / ((float) MAX_THREAD_BY_BLOCKS) )));
}

template <typename T>
int CuVector<T>::getThreadsSize(int size)
{
    // TODO may replace by (m_maxsize/MAX_THREAD_BY_BLOCKS)
    return size/((int) (std::ceil( ((float) size) / ((float) MAX_THREAD_BY_BLOCKS) )));
}


template <typename T>
T CuVector<T>::operator[](int i)
{
    return this->get(i);
}