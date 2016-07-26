#ifndef _VECTOR_H_
#define _VECTOR_H_

#include <iostream>

template< typename T >
class Vector
{
public:
	Vector();
	Vector(const T&, unsigned int);		// Repeat same value across whole vector
    Vector(const T*, unsigned int);		// Build from an array of the element
    Vector(const Vector<T>&);           // Copy constructor
    Vector(Vector<T>&&);             // Transfer constructor
	virtual ~Vector();

	virtual unsigned int getSize() const;
	virtual void setSize( unsigned int size );

	virtual const T & operator[]( unsigned int index ) const;
	virtual T & operator[]( unsigned int index );

	virtual Vector<T>& operator= (const Vector<T>&);
	virtual Vector<T>& operator= (Vector<T>&&);

	virtual void operator+= (const Vector<T>&);
	virtual void operator-= (const Vector<T>&);

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
Vector<T>::Vector(const T& element, unsigned int dim):	m_size(dim), m_content(new T[dim]) {
	for (unsigned int i=0; i<dim; ++i) {
		m_content[i] = element;
	}
}

// From array
template <typename T>
Vector<T>::Vector(const T* elemArray, unsigned int dim):
    m_size(dim), m_content(new T[dim]){
    for (unsigned int i=0; i<m_size; ++i) {
		m_content[i] = elemArray[i];
    }
}

// Copy
template <typename T>
Vector<T>::Vector(const Vector<T>& vect): m_size(vect.m_size), m_content(new T[vect.m_size]) {
    for (unsigned int i=0; i<vect.m_size; ++i) {
		m_content[i] = vect.m_content[i];
    }
}

// Transfer
template <typename T>
Vector<T>::Vector(Vector<T>&& vect): m_size(vect.m_size), m_content(vect.m_content) {
    vect.m_size = 0;
    vect.m_content = nullptr;
}

// Destructor
template< typename T >
Vector< T >::~Vector() {
    delete[] m_content;
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

// Operators
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

template <typename T>
void Vector<T>::operator+= (const Vector<T>& vect) {
    for (unsigned int i=0; i<vect.m_size; ++i) {
		m_content[i] += vect.m_content[i];
    }
}

template <typename T>
void Vector<T>::operator-= (const Vector<T>& vect) {
    for (unsigned int i=0; i < vect.m_size; ++i) {
		m_content[i] -= vect.m_content[i];
    }
}
// Clear
template< typename T >
void Vector< T >::clear() {
	for ( int i = 0; i < m_size; i++ ) {
		this->operator[]( i ) = 0;
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

// Out of class
template< typename T >
std::ostream & operator<<( std::ostream & flow, const Vector< T > & vector )
{
	flow << "[ ";
	for ( int i = 0; i < vector.getSize(); i++ )
	{
		flow << vector[i] << " ";
	}
	flow << "]";

	return flow;
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

