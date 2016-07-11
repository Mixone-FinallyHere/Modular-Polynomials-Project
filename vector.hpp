#ifndef VECTOR_HPP
#define VECTOR_HPP

#include <assert.h>
#include "stack.hpp"

using namespace std;

template <class T>
class Vector
{
private:
    int _size;
protected:
    Stack<T> contents;
    // Tiene que ser pasado a template aun, allocation statica ya definida por un
    // tamanio concreto
public:
    Vector() {};
    virtual ~Vector() {};
	virtual int getSize() const;
	virtual void setSize(int i);
	//virtual void input();
	virtual T& operator[](const int)=0;
	virtual const T& operator[](const int) const=0;
	virtual Vector& operator*(const T&)=0;
	friend Vector& operator+(const Vector&) {

	}
	//virtual Vector& operator-(const Vector&)=0;
	//virtual friend Vector operator=+(const Vector&)=0;
	//virtual friend Vector operator=-(const Vector&)=0;

};

template<class T>
ostream& operator<<(ostream& output, const Vector<T>& gimme)  {
    output << "Vector of size " << gimme.getSize() << " contains:" << endl;
    for(int i=0; i < gimme.getSize(); i++) {
        output << gimme[i] << " ";
    }
    output << endl;
    return output;
}

template<class T>
int Vector<T>::getSize() const{
    return this->_size;
}

template<class T>
void Vector<T>::setSize(int i){
    this->_size = i;
}

template<class T>
T& Vector<T>::operator[](const int i) {
    assert(i >=0 && i < this->_size);
    return this->contents[i];
}

template<class T>
const T& Vector<T>::operator[](const int i) const {
    assert(i >=0 && i < this->_size);
    return this->contents[i];
}

#endif

