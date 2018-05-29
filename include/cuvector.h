//
// Created by francois on 29/05/18.
//

#ifndef _CUDA_MATRIX_LIB_CuVector_H_
#define _CUDA_MATRIX_LIB_CuVector_H_
// MAX Size 1024
template <typename T>
class CuVector
{
public:

    // Constructor
    CuVector<T>(int size); //TODO
    CuVector<T>(int size,T* data); //TODO

    // Destructor
    ~CuVector<T>(); //TODO

    // Converting
    template <typename A> CuVector<A> astype<A>() const; //TODO
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


};


template <typename T>
class Node
{

};
#include "../src/vector/cuvector.tpp"
#endif //_CUDA_MATRIX_LIB_CUDAVECTOR_H_
