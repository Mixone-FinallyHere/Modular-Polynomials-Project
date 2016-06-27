#ifndef DYNAMICVECTOR_HPP
#define DYNAMICVECTOR_HPP

#include <iostream>
#include <assert.h>
#include "vector.hpp"

template<class T>
class DynamicVector : public Vector<T>
{
    public:
        DynamicVector();
        virtual DynamicVector operator=(DynamicVector&);
        virtual DynamicVector& operator*(const T&);
        DynamicVector& operator+(const DynamicVector& other) {
            DynamicVector<T>* temp = new DynamicVector<T>();
            if(other.getSize() > this->getSize()) {
                temp->_size = other.getSize();
                for(int i = 0; i < this->getSize(); ++i) {
                    temp[i] = (*this)[i] + other[i];
                }
                for(int j = this->getSize(); j < other.getSize(); ++j) {
                    temp[j] = other[j];
                }
            }
            else {
                temp->_size = this->_size;
                for(int i = 0; i < other.getSize(); ++i) {
                    temp[i] = (*this)[i] + other[i];
                }
                for(int j = other.getSize(); j < this->getSize(); ++j) {
                    temp[j] = (*this)[j];
                }
            }
            return (*temp);
        };
        virtual DynamicVector& operator-(const DynamicVector&);
        template<class S>
        friend std::ostream& operator<<(std::ostream&, const DynamicVector<S>&);
        template<class S>
        friend std::istream& operator>>(std::istream&, const DynamicVector<S>&);
    protected:
    private:
};


template<class T>
std::ostream& operator<<(std::ostream& output, DynamicVector<T>& gimme) {
    output << "Dynamic Vector of size "<< gimme.getSize() << " contains:" << endl;
    for(int i=0; i<gimme.getSize(); ++i) {
        output << gimme[i] << std::endl;
    }
    return output;
}

template<class T>
std::istream& operator>>(std::istream& input, DynamicVector<T>& takeme) {
    int sizeN = 0;
    cout << "Size that the dynamic vector will have: ";
    cin >> sizeN;
}



template<class T>
DynamicVector<T>::DynamicVector()
{
    this->_size = 0;
}

template<class T>
DynamicVector<T>& DynamicVector<T>::operator-(const DynamicVector<T>& other) {
    DynamicVector<T>* temp = new DynamicVector<T>();
    for(int i=0; i<s; i++) {
        (*temp)[i] = (*this)[i] - other[i];
    }
    return (*temp);
}



template<class T>
std::istream& operator>>(std::istream& input, DynamicVector<T>& takeme) {
    std::cout<<"Filling static vector of size " << s << " :" << std::endl;
    for(int i=0; i<s; i++) {
        std::cout << "Value at position " << i << " : ";
        T value;
        input >> value;
        takeme[i] = value;
    }
    return input;
}

template<class T>
DynamicVector<T> DynamicVector<T>::operator=(DynamicVector<T>& other) {
    for(int i=0; i<s; i++) {
        setContent(other[i], i);
    }
    return *this;
}

template<class T>
T& DynamicVector<T>::operator[](const int i) {
    assert(i >=0 && i < this->_size);
    return this->contents[i];
}

template<class T>
const T& DynamicVector<T>::operator[](const int i) const {
    assert(i >=0 && i < this->_size);
    return this->contents[i];
}




#endif // DYNAMICVECTOR_HPP
