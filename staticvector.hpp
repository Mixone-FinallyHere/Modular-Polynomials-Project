#ifndef _STATICVECTOR_H_
#define _STATICVECTOR_H_

#include "vector.hpp"

template< typename T, unsigned int s >
class StaticVector : public virtual Vector< T >
{
public:
	StaticVector();
	explicit StaticVector(const T&);
    explicit StaticVector(const T*);
    StaticVector(const StaticVector<T, s>&);
    StaticVector(StaticVector<T, s>&&);
    explicit StaticVector(const Vector<T>&);
	virtual ~StaticVector();

	virtual StaticVector<T, s>& operator=(const Vector<T>&) override;
    virtual StaticVector<T, s>& operator=(Vector<T>&&) override;
    virtual StaticVector<T, s>& operator=(const StaticVector<T, s>&);
    virtual StaticVector<T, s>& operator=(StaticVector<T, s>&&);

    virtual void operator+=(const Vector<T>&) override;
    virtual void operator-=(const Vector<T>&) override;

	virtual void setSize( unsigned int size );
private:
	static const unsigned int m_allocated_size = s;
	T m_static_vector[ s ];
};

// Constructors
template< typename T, unsigned int s >
StaticVector< T, s >::StaticVector()
{
	this->m_content = m_static_vector;
	this->m_size  = s;

	this->clear();
}

template <typename T, unsigned int s>
StaticVector<T, s>::StaticVector(const T& element):
    Vector<T>(element, s) {}

template <typename T, unsigned int s>
StaticVector<T, s>::StaticVector(const T* elemArray):
    Vector<T>(elemArray, s) {}

template <typename T, unsigned int s>
StaticVector<T, s>::StaticVector(const StaticVector<T, s>& vect):
    Vector<T>(vect) {}

template <typename T, unsigned int s>
StaticVector<T, s>::StaticVector(StaticVector<T, s>&& vect):
    Vector<T>(std::forward<StaticVector<T, s>>(vect)) {}

template <typename T, unsigned int s>
StaticVector<T, s>::StaticVector(const Vector<T>& vect) {
    m_static_vector = new T[s];
    unsigned int temp = m_allocated_size;
    unsigned int minDim = s < vect.getSize() ? s : vect.getSize();
    while (temp < minDim) {
        m_static_vector[temp] = vect[temp];
        temp++;
    }
}

// Destructor
template< typename T, unsigned int s >
StaticVector< T, s >::~StaticVector()
{
}

// Operators
template <typename T, unsigned int s>
StaticVector<T, s>& StaticVector<T, s>::operator=(const Vector<T>& vect) {
	this->Vector<T>::operator=(vect);
	return *this;
}

template <typename T, unsigned int s>
StaticVector<T, s>& StaticVector<T, s>::operator=(const StaticVector<T, s>& vect)
{
    this->Vector<T>::operator=(vect);
    return *this;
}

template <typename T, unsigned int s>
StaticVector<T, s>& StaticVector<T, s>::operator=(Vector<T>&& vect)
{
    this->Vector<T>::operator=(std::forward<Vector<T>>(vect));
    return *this;

}

template <typename T, unsigned int s>
StaticVector<T, s>& StaticVector<T, s>::operator=(StaticVector<T, s>&& vect)
{
    this->Vector<T>::operator=(std::forward<Vector<T>>(vect));
    return *this;
}

template <typename T, unsigned int s>
void StaticVector<T, s>::operator+=(const Vector<T>& vect)
{
    this->Vector<T>::operator+=(vect);
}

template <typename T, unsigned int s>
void StaticVector<T, s>::operator-=(const Vector<T>& vect) {
    this->Vector<T>::operator-=(vect);
}

// Extras
template< typename T, unsigned int s >
void StaticVector< T, s >::setSize( unsigned int size )
{
	Vector< T >::setSize( size );
}

#endif // _STATICVECTOR_H_
