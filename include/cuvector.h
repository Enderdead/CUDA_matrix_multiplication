//
// Created by francois on 29/05/18.
//

#ifndef _CUDA_MATRIX_LIB_CuVector_H_
#define _CUDA_MATRIX_LIB_CuVector_H_
#include <cuda.h>
#include <iostream>
#include <vector>
#include <stdexcept>
#include <cstdlib>
#include <cmath>
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

    //Display
    void show(void) const;

    // Converting
    template <typename A> CuVector<A> asType() const; //TODO
    template <typename A> CuVector<A> apply(A (*function)(T)); //TODO
    CuVector<T> filtre(bool (*function)(T)); //TODO


    // Modifier
    T pop_back(void);
    T get(int i);
    T pop_front(void); //TODO
    void push_back(T const element);
    void push_front(T const element); //TODO
    void push(T * data,int size); //TODO
    void insert(int i, T const element); //TODO
    void erase(int i); //TODO
    void clear(void); //TODO

    // Capacity
    int size(void) const {return m_size;}
    int capacity(void) const {return m_maxsize;}
    bool empty(void) const {return m_size==0;}
    bool full(void) const {return m_maxsize==m_size;}

    // Operator
    T           operator[] (int i);
    CuVector<T> operator+  (CuVector<T> const& vect); //TODO
    void        operator=  (CuVector<T> const& vect); //TODO

private:
    static int sizeChecking(int size);
    static int getBocksSize(int size);
    static int getThreadsSize(int size);


    int m_maxsize;
    int m_size;
    T*  m_data;
};

#include "../src/vector/cuvector.cu"
#endif //_CUDA_MATRIX_LIB_CUDAVECTOR_H_
