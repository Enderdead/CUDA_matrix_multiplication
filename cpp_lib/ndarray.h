//
// Created by francois gauthier-clerc on 25/05/18.
//

#ifndef _NDARRAY_H_
#define _NDARRAY_H_

#include <stdarg.h>
#include <cstdlib>
#include <iostream>
#include <stdexcept>

template <typename T>
class NdArray
{
public:
    NdArray<T>(int dim, ...);
    NdArray<T>(NdArray<T> const& old);

    ~NdArray<T>();

    int * getSizing() const {return m_sizing;};

    NdArray<T>& transpose(); //TODO
    void transposeInPlace(); //TODO

    NdArray<T> argmax(); //TODO
    NdArray<T> argmin(); //TODO
    NdArray<T> std(); //TODO

    NdArray<T> inverse(); //TODO

    NdArray<T> trace(); //TODO

             T& operator() (int x, ...);
    NdArray<T>& operator+ (NdArray<T>& n);
    NdArray<T>& operator- (NdArray<T>& n);
    NdArray<T>& operator+= (NdArray<T>& n); //TODO
    NdArray<T>& operator-= (NdArray<T>& n); //TODO
    NdArray<T>& operator* (NdArray<T>& n);  //TODO



    void show() const;

private:

    int getSize() const;

    int m_dim;
    int * m_sizing;
    T * m_data;
};



#include "ndarray.tpp"
#endif //CUDA_MATRIX_MULTIPLICATION_VECTOR_H
