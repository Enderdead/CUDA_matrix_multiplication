//
// Created by francois gauthier-clerc on 25/05/18.
//

#include "ndarray.h"

template<typename T>
NdArray<T>::NdArray(int dim,...)
{
    m_dim = dim;
    m_sizing = (int * ) malloc(sizeof(int)*dim);

    va_list ap;
    va_start(ap,dim);
    for(int i=0;i<dim;i++)  m_sizing[i] = va_arg(ap,int);
    va_end(ap);
    int size = m_sizing[0]* sizeof(T);
    for(int i=1; i<dim; i++) size*=m_sizing[i];

    m_data = (T*) malloc(size);
}

template <typename T>
NdArray<T>::NdArray(NdArray<T> const& old)
{
    m_dim = old.m_dim;
    m_sizing = (T*) malloc(sizeof(int)*m_dim);
    for(int i=0;i<m_dim;i++) m_sizing[i] = old.m_sizing[i];
    int size = old.getSize();
    m_data = (T*) malloc(size*sizeof(T));
    for(int i=0; i<size; i++) m_data[i] = old.m_data[i];
}

template<typename T>
NdArray<T>::~NdArray()
{
    free(m_sizing);
    free(m_data);
}

template<typename T>
void NdArray<T>::show() const
{
    for(int i =0;i<m_sizing[0];i++)
    {
        for(int j= 0;j<m_sizing[1];j++)
        {
            std::cout<<m_data[i*m_sizing[1] + j];
        }
        std::cout<<std::endl;
    }
}

template<typename T>
T& NdArray<T>::operator()(int x, ...)
{
    va_list ap;
    va_start(ap,x);
    int temp = x, position = 0;
    for(int i=0; i<m_dim; i++)
    {
        for(int k=i+1; k<m_dim; k++)
        {
            temp*=m_sizing[k];
        }
        position+= temp;
        temp = va_arg(ap,int);
    }
    va_end(ap);
    return m_data[position];

}
template <typename T>
NdArray<T>& NdArray<T>::operator+ (NdArray<T>& n)
{
    if(n.m_dim!=m_dim) throw std::runtime_error("Incompatible dimention on + operator !");
    for(int i=0;i<m_dim; i++) if(n.m_sizing[i]!=this->m_sizing[i]) throw std::runtime_error("Incompatible " +std::to_string(i) + " dimention on + operator !");

    NdArray<T>* result = new NdArray<T>(n);
    for(int i=0;i<result->getSize(); i++) result->m_data[i] += m_data[i];

    return *result;
}

template <typename T>
NdArray<T>& NdArray<T>::operator- (NdArray<T>& n)
{
    if(n.m_dim!=m_dim) throw std::runtime_error("Incompatible dimention on + operator !");
    for(int i=0;i<m_dim; i++) if(n.m_sizing[i]!=this->m_sizing[i]) throw std::runtime_error("Incompatible " +std::to_string(i) + " dimention on + operator !");

    NdArray<T>* result = new NdArray<T>(*this);
    for(int i=0;i<result->getSize(); i++) result->m_data[i] -= n.m_data[i];

    return *result;
}


template<typename T>
int NdArray<T>::getSize() const
{
    int size=1;
    for(int i=0;i<m_dim;i++) size*=m_sizing[i];
    return size;
}