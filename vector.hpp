#ifndef _VECTOR_H_
#define _VECTOR_H_

#include <iostream>
#include <string>
#include <typeinfo>

// Default clear of Vector value
#define CLEAR_VALUE 0

// Miguel Terol Espino
// 000356914
// mteroles@ulb.ac.be

template< typename T >
class Vector {
public:
	Vector();
	Vector(const T&, unsigned int);		// Repeat same value across whole vector
    Vector(const Vector<T>&);           // Copy constructor
	virtual ~Vector() {};

	virtual unsigned int getSize() const;
	virtual void setSize( unsigned int size );

	virtual const T & operator[]( unsigned int index ) const;
	virtual T & operator[]( unsigned int index );

	virtual Vector<T>& operator= (const Vector<T>&);
	virtual Vector<T>& operator= (Vector<T>&&);

	virtual void operator+= (const Vector<T>&)=0;
	virtual void operator-= (const Vector<T>&)=0;

	virtual void operator*= (const T& value);

	virtual void clear();

	virtual void unary_plus ();
	virtual void unary_minus ();
protected:
	unsigned int m_size;
	T * m_content;
};

// ================= Constructors =================
// Trivial
template< typename T >
Vector< T >::Vector(): m_size( 0 ), m_content(NULL){}

// Repeat same element
template <typename T>
Vector<T>::Vector(const T& element, unsigned int dim) {
	std::cout << "Element to repeat: " << element << std::endl;
	this->m_size=dim;
	this->m_content = new T[dim];
	for (unsigned int i=0; i<dim; ++i) {
		this->m_content[i] = element;
	}
}

// Copy
template <typename T>
Vector<T>::Vector(const Vector<T>& vect): m_size(vect.m_size), m_content(new T[vect.m_size]) {
    for (unsigned int i=0; i<vect.m_size; ++i) {
		m_content[i] = vect.m_content[i];
    }
}

// Setters and getters
template< typename T >
unsigned int Vector< T >::getSize() const {
	return m_size;
}

template< typename T >
void Vector< T >::setSize( unsigned int size ) {
	m_size = size;
}

// Operators inside of class
template< typename T >
const T & Vector< T >::operator[]( unsigned int index ) const {
	return *(m_content + index);
}

template< typename T >
T & Vector< T >::operator[]( unsigned int index ) {
	return *(m_content + index);
}

template<typename T>
void Vector<T>::operator*=(const T& value) {
	for (unsigned int i=0; i<m_size; ++i) {
		m_content[i] *= value;
	}
}

template <typename T>
Vector<T>& Vector<T>::operator= (const Vector<T>& vect) {
	for (unsigned int i=0; i < vect.getSize(); ++i) {
		m_content[i] = vect.m_content[i];
	}
	return *this;
}

template <typename T>
Vector<T>& Vector<T>::operator= (Vector<T>&& vect) {
	m_content = vect.m_content;
	vect.m_content = nullptr;
	m_size = vect.m_size;
	vect.m_size = 0;
	return *this;
}

// Clear
template< typename T >
void Vector< T >::clear() {
	for ( int i = 0; i < m_size; i++ ) {
		m_content[i] = CLEAR_VALUE;
	}
}

// Unary plus
template <typename T>
void Vector<T>::unary_plus () {
    for (unsigned int i(0); i<m_size; ++i) {
		m_content[i] += m_content[i];
    }
}

// Unary minus
template <typename T>
void Vector<T>::unary_minus () {
    for (unsigned int i=0; i<m_size; ++i) {
		m_content[i] -= m_content[i];
    }
}

// Out of class operators
template< typename T >
std::ostream & operator<<( std::ostream & ostr, const Vector< T > & vector ) {
    // Get name of derived class calling output
	ostr <<  typeid(vector).name() << " vector contains => [ "; // Long live typeinfo
	for ( int i = 0; i < vector.getSize(); i++ ) {
        ostr << vector[i];
        if (i < vector.getSize()-1)	ostr << ", ";
	}
	ostr << " ]";
	return ostr;
}

template< typename T >
std::istream& operator>>( std::istream & input, Vector< T > & vector ) {
    // Get name of derived class calling output
	std::cout <<  typeid(vector).name() << " vector of size " << vector.getSize() << " input:" << std::endl;
	for ( int i = 0; i < vector.getSize(); i++ ) {
        std::cout << i << " => ";
        T buffer;
        std::cin >> buffer;
        vector[i] = buffer;
	}
	std::cout << "Done." << std::endl;
	return input;
}

template <typename T>
void operator+(Vector<T>& vect) {
	vect.unary_plus();
}

template <typename T>
void operator-(Vector<T>& vect) {
	vect.unary_minus();
}


#endif // _VECTOR_H

