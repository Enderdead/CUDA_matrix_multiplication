//
// Created by francois on 27/05/18.
//

#ifndef CUDA_MATRIX_MULTIPLICATION_ARRAY_H
#define CUDA_MATRIX_MULTIPLICATION_ARRAY_H


#include <stdarg.h>
#include <cstdlib>
#include <iostream>
#include <stdexcept>

template <typename T>
class Array
{
public:


    Array<T>(int size); //TODO
    Array<T>(int size,T* data); //TODO

    ~Array<T>(); //TODO

    template <typename A> Array<A> astype<A>() const; //TODO



private:


};


template <typename T>
class Node
{

};
#include "array.tpp"
#endif //CUDA_MATRIX_MULTIPLICATION_ARRAY_H
