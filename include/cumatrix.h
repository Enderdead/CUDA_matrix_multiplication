//
// Created by francois gauthier-clerc on 25/05/18.
//

#ifndef _CUDA_MATRIX_LIB_CUMATRIX_H_
#define _CUDA_MATRIX_LIB_CUMATRIX_H_

#include <stdarg.h>
#include <cstdlib>
#include <iostream>
#include <stdexcept>

template <typename T>
class CuMatrix
{
public:
    CuMatrix<T>(int dim, ...); //TODO
    CuMatrix<T>(CuMatrix<T> const& old); //TODO

    ~CuMatrix<T>();//TODO

    int * getSizing() const {return m_sizing;}; //TODO

    CuMatrix<T>& transpose() const; //TODO
    void transposeInPlace(); //TODO

    CuMatrix<T> argmax(int axis); //TODO
    CuMatrix<T> argmin(int axis); //TODO
    CuMatrix<T> std(int axis); //TODO

    CuMatrix<T> inverse() const; //TODO
    void inverseInPlace(); //TODO

    CuMatrix<T> pow() const; //TODO
    void powInPlace(); //TODO

    T trace(); //TODO

    T& operator() (int x, ...); //TODO
    CuMatrix<T>& operator+ (CuMatrix<T>& n);//TODO
    CuMatrix<T>& operator- (CuMatrix<T>& n);//TODO
    CuMatrix<T>& operator+= (CuMatrix<T>& n); //TODO
    CuMatrix<T>& operator-= (CuMatrix<T>& n); //TODO
    CuMatrix<T>& operator* (CuMatrix<T>& n);  //TODO



    void show() const; //TODO

private:

    int getSize() const; //TODO

    int m_dim;
    int * m_sizing;
    T * m_data;
};



#include "../src/matrix/cumatrix.cu"
#endif //_CUDA_MATRIX_LIB_CUMATRIX_H_
