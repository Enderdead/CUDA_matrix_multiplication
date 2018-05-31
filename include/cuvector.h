//
// Created by francois on 29/05/18.
//

#ifndef _CUDA_MATRIX_LIB_CuVector_H_
#define _CUDA_MATRIX_LIB_CuVector_H_
#include <cuda.h>
#include <iostream>
#include <vector>


template <typename T>
class CuVector
{
public:

    // Constructor
    CuVector<T>(int size);
    CuVector<T>(std::vector<T> data);
    CuVector<T>(CuVector<T> const& copy);

    // Destructor
    ~CuVector<T>();

    // Converting
    template <typename A> CuVector<A> asType() const; //TODO
    template <typename A> CuVector<A> apply(A (*function)(T)); //TODO
    CuVector<T> filtre(bool (*function)(T)); //TODO


    // Modifier
    T pop_back(void); //TODO
    T pop_front(void); //TODO
    void push_back(T const element); //TODO
    void push_front(T const element); //TODO
    void insert(int i, T const element); //TODO
    void erase(int i); //TODO
    void clear(void); //TODO

    // Capacity
    int size(void); //TODO
    static int max_size(void); //TODO
    int capacity(void); //TODO
    bool empty(void); //TODO

    // Operator
    T&          operator[] (int i); //TODO
    CuVector<T> operator+  (CuVector<T> const& vect); //TODO
    void        operator=  (CuVector<T> const& vect); //TODO

private:
    int sizeChecking(int size);

    int m_maxsize;
    int m_size;
    T*  m_data;
};

#include "../src/vector/cuvector.cu"
#endif //_CUDA_MATRIX_LIB_CUDAVECTOR_H_
