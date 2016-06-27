#ifndef STATICVECTOR_HPP
#define STATICVECTOR_HPP

#include <iostream>
#include "vector.hpp"
#include <assert.h>

template<class T, int s>
class StaticVector : public Vector<T>
{
    public:
        StaticVector();
        virtual StaticVector operator=(StaticVector&);
        void setContent(T newVal, int index);
        virtual T& operator[](const int);
	    virtual const T& operator[](const int) const;
        virtual StaticVector& operator*(const T&);
        StaticVector& operator+(const StaticVector& other){
            StaticVector<T, s>* temp = new StaticVector<T, s>();
            for(int i=0; i<s; i++) {
                (*temp)[i] = (*this)[i] + other[i];
            }
            return (*temp);
        };
        virtual StaticVector& operator-(const StaticVector&);
    private:
        T contents[s];
};

// Constructor
template<class T, int s>
StaticVector<T, s>::StaticVector(){
    T test[s];
    this->contents = test;
    this->setSize(s);
    for(int i=0; i < s; i++) {
        setContent(0, i);
    }
}


template<class T, int s>
StaticVector<T, s> operator+(const StaticVector<T, s>&, const StaticVector<T, s>&);

template<class T, int s>
void StaticVector<T, s>::setContent(T newVal, int index) {
    this->contents[index] = newVal;
}

template<class T, int s>
StaticVector<T, s>& StaticVector<T, s>::operator*(const T& scalar) {
    StaticVector<T, s>* temp = new StaticVector<T, s>();
    for(int i=0; i<s; i++) {
        (*temp)[i] = (*this)[i] * scalar;
    }
    return (*temp);
}

//template<class T, int s>
//StaticVector<T, s>& StaticVector<T, s>::operator+(const StaticVector<T,s>& other)

template<class T, int s>
StaticVector<T, s>& StaticVector<T, s>::operator-(const StaticVector<T,s>& other) {
    StaticVector<T, s>* temp = new StaticVector<T, s>();
    for(int i=0; i<s; i++) {
        (*temp)[i] = (*this)[i] - other[i];
    }
    return (*temp);
}



template<class T, int s>
std::istream& operator>>(std::istream& input, StaticVector<T, s>& takeme) {
    std::cout<<"Filling static vector of size " << s << " :" << std::endl;
    for(int i=0; i<s; i++) {
        std::cout << "Value at position " << i << " : ";
        T value;
        input >> value;
        takeme[i] = value;
    }
    return input;
}

template<class T, int s>
StaticVector<T, s> StaticVector<T, s>::operator=(StaticVector<T, s>& other) {
    for(int i=0; i<s; i++) {
        setContent(other[i], i);
    }
    return *this;
}

template<class T, int s>
T& StaticVector<T, s>::operator[](const int i) {
    assert(i >=0 && i < this->_size);
    return this->contents[i];
}

template<class T, int s>
const T& StaticVector<T, s>::operator[](const int i) const {
    assert(i >=0 && i < this->_size);
    return this->contents[i];
}
#endif // STATICVECTOR_HPP
