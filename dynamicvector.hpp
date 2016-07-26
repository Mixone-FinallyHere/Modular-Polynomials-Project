#ifndef _DYNAMICVECTOR_H_
#define _DYNAMICVECTOR_H_

#include "Vector.hpp"

template< typename T >
class DynamicVector : public virtual Vector< T >
{
protected:
    using Vector<T>::m_size;
    using Vector<T>::m_contents;
public:
	DynamicVector( int size );
	DynamicVector(const T&, unsigned int);
    DynamicVector(const T*, unsigned int);
    DynamicVector(const DynamicVector<T>&);
    DynamicVector(DynamicVector<T>&&);
    DynamicVector(const Vector<T>&);
	virtual ~DynamicVector();

    virtual DynamicVector<T>& operator=(const Vector<T>&) override;
    virtual DynamicVector<T>& operator=(Vector<T>&&) override;
    virtual DynamicVector<T>& operator=(const DynamicVector<T>&);
    virtual DynamicVector<T>& operator=(DynamicVector<T>&&);

    virtual void operator+=(const Vector<T>&) override;
    virtual void operator-=(const Vector<T>&) override;

	virtual void setSize( unsigned int size );
};

template< typename T >
DynamicVector< T >::DynamicVector( int size )
{
	setSize( size );
}

template< typename T >
DynamicVector< T >::~DynamicVector()
{
	delete Vector<T>::m_content;
}

// Constructors
template <typename T>
DynamicVector<T>::DynamicVector(const T& element, unsigned int dim):
    Vector<T>(element, dim) {}

template <typename T>
DynamicVector<T>::DynamicVector(const T* elemArray, unsigned int dim):
    Vector<T>(elemArray, dim) {}


template <typename T>
DynamicVector<T>::DynamicVector(const DynamicVector<T>& vect):
    Vector<T>(vect) {}

template <typename T>
DynamicVector<T>::DynamicVector(DynamicVector<T>&& vect):
    Vector<T>(std::forward<DynamicVector<T>>(vect)) {}

template <typename T>
DynamicVector<T>::DynamicVector(const Vector<T>& vect):
    Vector<T>(vect) {}


// Operators
template <typename T>
DynamicVector<T>& DynamicVector<T>::operator=(const Vector<T>& vect)
{
    if (m_size != vect.siz())
    {
		m_size = vect.siz();
		T* oldValues = m_contents;
		m_contents = new T[m_size];
		delete[] oldValues;
    }
    this->Vector<T>::operator=(vect);
	return *this;
}

template <typename T>
DynamicVector<T>& DynamicVector<T>::operator=(const DynamicVector<T>& vect)
{
    if (m_size != vect.siz()) {
		m_size = vect.siz();
		T* oldValues = m_contents;
		m_contents = new T[m_size];
		delete[] oldValues;
    }
    this->Vector<T>::operator=(vect);
	return *this;
}

template <typename T>
DynamicVector<T>& DynamicVector<T>::operator=(Vector<T>&& vect)
{
	this->Vector<T>::operator=(std::forward<Vector<T>>(vect));
	return *this;
}

template <typename T>
DynamicVector<T>& DynamicVector<T>::operator=(DynamicVector<T>&& vect)
{
	this->Vector<T>::operator=(std::forward<Vector<T>>(vect));
	return *this;
}

template <typename T>
void DynamicVector<T>::operator+=(const Vector<T>& vect)
{
    if (vect.siz() > m_size)
    {
        T* oldValues = m_contents;
        m_size = vect.siz();
        m_contents = new T[m_size];
        for (unsigned int i=0; i<m_size; ++i) { m_contents[i] = oldValues[i]; }
        delete[] oldValues;
    }
    this->Vector<T>::operator+=(vect);
}

template <typename T>
void DynamicVector<T>::operator-=(const Vector<T>& vect)
{
    if (vect.siz() > m_size)
    {
        T* oldValues = m_contents;
        m_size = vect.siz();
        m_contents = new T[m_size];
        for (unsigned int i=0; i<m_size; ++i) { m_contents[i] = oldValues[i]; }
        delete[] oldValues;
    }
    this->Vector<T>::operator-=(vect);
}



template <typename T>
DynamicVector<T> operator+(const Vector<T>& vectA, const Vector<T>& vectB)
{
    DynamicVector<T> resVect(vectA);
    resVect += vectB;
    return resVect;
}

template <typename T>
DynamicVector<T> operator-(const Vector<T>& vectA, const Vector<T>& vectB)
{
    DynamicVector<T> resVect(vectA);
    resVect -= vectB;
    return resVect;
}

template <typename T>
DynamicVector<T> operator*(const DynamicVector<T>& vect, const T& element)
{
    DynamicVector<T> newVect(vect);
    newVect *= element;
    return newVect;
}
template <typename T>
DynamicVector<T> operator*(const T& element, const DynamicVector<T>& vect)
{
	return vect * element;
}

template <typename T>
DynamicVector<T> operator+(const DynamicVector<T>& vect)
{
    DynamicVector<T> newVect(vect);
    newVect.unary_plus();
    return newVect;
}

template <typename T>
DynamicVector<T> operator-(const DynamicVector<T>& vect)
{
    DynamicVector<T> newVect(vect);
    newVect.unary_minus();
    return newVect;
}


template< typename T >
void DynamicVector< T >::setSize( unsigned int size )
{
	if ( Vector<T>::m_size == size )
		return;

	T * old_vector = Vector<T>::m_content;
	unsigned int old_size = Vector<T>::m_size;

	Vector<T>::m_content = new T[size];
	Vector<T>::m_size  = size;

	Vector<T>::clear();

	for ( int i = 0; i < ((Vector<T>::m_size < old_size )?Vector<T>::m_size:old_size); i++ )
	{
		Vector<T>::operator[]( i ) = old_vector[ i ];
	}

	delete old_vector;
}

#endif // _STATICVECTOR_H_
