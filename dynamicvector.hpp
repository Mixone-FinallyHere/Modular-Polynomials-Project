#ifndef _DYNAMICVECTOR_H_
#define _DYNAMICVECTOR_H_

#include "vector.hpp"

// Miguel Terol Espino
// 000356914
// mteroles@ulb.ac.be

template< typename T >
class DynamicVector : public virtual Vector<T> {
protected:
    using Vector<T>::m_size;
    using Vector<T>::m_content;
public:
	DynamicVector( int size );
	DynamicVector(const T&, unsigned int);
    DynamicVector(const DynamicVector<T>&);
	virtual ~DynamicVector();
    virtual DynamicVector<T>& operator=(const DynamicVector<T>&);
    virtual void operator+=(const Vector<T>&);
    virtual void operator-=(const Vector<T>&);

	virtual void setSize( unsigned int size ) override;
};

// Destructor
template< typename T >
DynamicVector< T >::~DynamicVector() {
	delete this->m_content;
}

// Constructors
template< typename T >
DynamicVector< T >::DynamicVector( int size ) {
	setSize(size);
}

template< typename T >
DynamicVector< T >::DynamicVector( const T& element, unsigned int size ) {
    std::cout << "Element to repeat: " << element << std::endl;
	this->m_size=size;
	this->m_content = new T[size];
	for (unsigned int i=0; i<size; ++i) {
		this->m_content[i] = element;
	}
}

template <typename T>
DynamicVector<T>::DynamicVector(const DynamicVector<T>& vect): Vector<T>(vect) {}


// Set Size override
template< typename T >
void DynamicVector< T >::setSize( unsigned int size ) {
	if ( Vector<T>::m_size == size ) {
            return;
	}
	T * old_vector = Vector<T>::m_content;
	unsigned int old_size = Vector<T>::m_size;

	Vector<T>::m_content = new T[size];
	Vector<T>::m_size  = size;

	Vector<T>::clear();

	for ( int i = 0; i < ((Vector<T>::m_size < old_size )?Vector<T>::m_size:old_size); i++ ) {
		Vector<T>::operator[]( i ) = old_vector[ i ];
	}
	delete old_vector;
}


// Operators
template <typename T>
DynamicVector<T>& DynamicVector<T>::operator=(const DynamicVector<T>& vect) {
    if (m_size != vect.getSize()) {
		m_size = vect.getSize();
		T* oldValues = m_content;
		m_content = new T[m_size];
		delete[] oldValues;
    }
    this->Vector<T>::operator=(vect);
	return *this;
}

template <typename T>
void DynamicVector<T>::operator+=(const Vector<T>& vect) {
    if (vect.getSize() > m_size) {
        T* oldValues = m_content;
        m_size = vect.getSize();
        m_content = new T[m_size];
        for (unsigned int i=0; i<m_size; ++i) {
                m_content[i] = oldValues[i];
        }
        delete[] oldValues;
    }
    for (unsigned int i=0; i<vect.getSize(); ++i) {
		this->m_content[i] += vect[i];
    }
}

template <typename T>
void DynamicVector<T>::operator-=(const Vector<T>& vect) {
    if (vect.getSize() > m_size) {
        T* oldValues = m_content;
        m_size = vect.getSize();
        m_content = new T[m_size];
        for (unsigned int i=0; i<m_size; ++i) {
                m_content[i] = oldValues[i];
        }
        delete[] oldValues;
    }
    for (unsigned int i=0; i<vect.getSize(); ++i) {
		this->m_content[i] -= vect[i];
    }
}

// Out of class operators
template <typename T>
DynamicVector<T> operator+(const Vector<T>& vectA, const Vector<T>& vectB) {
    DynamicVector<T> resVect(vectA);
    resVect += vectB;
    return resVect;
}

template <typename T>
DynamicVector<T> operator-(const Vector<T>& vectA, const Vector<T>& vectB) {
    DynamicVector<T> resVect(vectA);
    resVect -= vectB;
    return resVect;
}

template <typename T>
DynamicVector<T> operator*(const DynamicVector<T>& vect, const T& element) {
    DynamicVector<T> newVect(vect);
    newVect *= element;
    return newVect;
}
template <typename T>
DynamicVector<T> operator*(const T& element, const DynamicVector<T>& vect) {
	return vect * element;
}

template <typename T>
DynamicVector<T> operator+(const DynamicVector<T>& vect) {
    DynamicVector<T> newVect(vect);
    newVect.unary_plus();
    return newVect;
}

template <typename T>
DynamicVector<T> operator-(const DynamicVector<T>& vect) {
    DynamicVector<T> newVect(vect);
    newVect.unary_minus();
    return newVect;
}


#endif // _STATICVECTOR_H_
