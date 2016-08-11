#ifndef _STATICVECTOR_HPP_
#define _STATICVECTOR_HPP_

#include "vector.hpp"

// Miguel Terol Espino
// 000356914
// mteroles@ulb.ac.be

template< typename T, unsigned int s >
class StaticVector : public virtual Vector<T> {
public:
	StaticVector();
	explicit StaticVector(const T&);
    StaticVector(const StaticVector<T, s>&);
	virtual ~StaticVector();
    virtual StaticVector<T, s>& operator=(const StaticVector<T, s>&);
    virtual void operator+=(const Vector<T>&);
    virtual void operator-=(const Vector<T>&);

private:
	static const unsigned int m_allocated_size = s;
	T m_static_vector[s];
};

// Constructors
template< typename T, unsigned int s >
StaticVector< T, s >::StaticVector() {
	this->m_content = m_static_vector;
	this->m_size  = s;
	this->clear();
}

template <typename T, unsigned int s>
StaticVector<T, s>::StaticVector(const T& element): Vector<T>(element, s) {}

template <typename T, unsigned int s>
StaticVector<T, s>::StaticVector(const StaticVector<T, s>& vect): Vector<T>(vect) {}

// Destructor
template< typename T, unsigned int s >
StaticVector< T, s >::~StaticVector() {
    delete this->m_content;
}

// Operators
template <typename T, unsigned int s>
StaticVector<T, s>& StaticVector<T, s>::operator=(const StaticVector<T, s>& vect)
{
    this->Vector<T>::operator=(vect);
    return *this;
}

template <typename T, unsigned int s>
void StaticVector<T, s>::operator+=(const Vector<T>& vect) {
    for (unsigned int i=0; i<vect.getSize(); ++i) {
		this->m_content[i] += vect[i];
    }
}

template <typename T, unsigned int s>
void StaticVector<T, s>::operator-=(const Vector<T>& vect) {
    for (unsigned int i=0; i < vect.getSize(); ++i) {
		this->m_content[i] -= vect[i];
    }
}

// Out of class
template<typename T, unsigned int s> // StaticVector ++
StaticVector<T, s> operator+(const StaticVector<T, s>& vect) {
    StaticVector<T, s> newVect(vect);
    newVect.unary_plus();
    return newVect;
}

template<typename T, unsigned int s> // Static Vector --
StaticVector<T, s> operator-(const StaticVector<T, s>& vect) {
    StaticVector<T, s> newVect(vect);
    newVect.unary_minus();
    return newVect;
}

template <typename T, unsigned int s> // StaticVector + StaticVector
StaticVector<T, s> operator+(const StaticVector<T, s>& vectA, const StaticVector<T, s>& vectB) {
	StaticVector<T, s> resVect(vectA);
    resVect += vectB;
    return resVect;
}

template <typename T, unsigned int s> // StaticVector - StaticVector
StaticVector<T, s> operator-(const StaticVector<T, s>& vectA, const StaticVector<T, s>& vectB) {
	StaticVector<T, s> resVect(vectA);
    resVect -= vectB;
    return resVect;
}

template <typename T, unsigned int s> // StaticVector * T
StaticVector<T, s> operator*(const StaticVector<T, s>& vect, const T& element) {
    StaticVector<T, s> newVect(vect);
    newVect *= element;
    return newVect;
}
template <typename T, unsigned int s> // T * StaticVector
StaticVector<T, s> operator*(const T& element, const StaticVector<T, s>& vect) {
    return vect * element; // Switch around to use already defined operator*
}

#endif
