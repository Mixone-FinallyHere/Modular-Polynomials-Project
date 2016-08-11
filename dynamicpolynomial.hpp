# 1 "dynamicpolynomial.hpp"
#ifndef POLYDYN_H
#define POLYDYN_H

#include <cstddef>
#include <stdexcept>

#include "polynomialvector.hpp"
#include "dynamicvector.hpp"

template <typename T>
class PolyDyn: public Polynomial<T>, public DynamicVector<T>
{
 protected:
  using Polynomial<T>::_dim;
  using Polynomial<T>::_deg;
  using Polynomial<T>::_values;
  using Polynomial<T>::_degModified;

 public:

        PolyDyn();
        PolyDyn(const T&, unsigned int);
        PolyDyn(const T*, unsigned int);
        PolyDyn(const PolyDyn<T>&);
        PolyDyn(PolyDyn<T>&&);
        PolyDyn(const Polynomial<T>&);
  virtual PolyDyn<T>& operator=(const Vector<T>&) override;
  virtual PolyDyn<T>& operator=(Vector<T>&&) override;
  virtual PolyDyn<T>& operator=(const Polynomial<T>&) override;
  virtual PolyDyn<T>& operator=(Polynomial<T>&&) override;
  virtual PolyDyn<T>& operator=(const DynamicVector<T>&) override;
  virtual PolyDyn<T>& operator=(DynamicVector<T>&&) override;
  virtual PolyDyn<T>& operator=(const PolyDyn<T>&);
  virtual PolyDyn<T>& operator=(PolyDyn<T>&&);

  virtual void operator+=(const Vector<T>&) override;
        virtual void operator-=(const Vector<T>&) override;

  using Polynomial<T>::operator*=;
  void operator*=(const Polynomial<T>&) override;
};





template <typename T>
PolyDyn<T>::PolyDyn():
 Vector<T>(),
 Polynomial<T>(),
 DynamicVector<T>() {}

template <typename T>
PolyDyn<T>::PolyDyn(const T& element, unsigned int dim):
    Vector<T>(element, dim),
    Polynomial<T>(element, dim),
    DynamicVector<T>(element, dim) {}

template <typename T>
PolyDyn<T>::PolyDyn(const T* elemArray, unsigned int dim):
    Vector<T>(elemArray, dim),
    Polynomial<T>(elemArray, dim),
    DynamicVector<T>(elemArray, dim) {}


template <typename T>
PolyDyn<T>::PolyDyn(const PolyDyn<T>& poly):
    Vector<T>(poly),
    Polynomial<T>(poly),
    DynamicVector<T>(poly) {}


template <typename T>
PolyDyn<T>::PolyDyn(PolyDyn<T>&& poly):
    Vector<T>(std::forward<Polynomial<T>>(poly)),
    Polynomial<T>(std::forward<Polynomial<T>>(poly)),
    DynamicVector<T>(std::forward<Polynomial<T>>(poly)) {}


template <typename T>
PolyDyn<T>::PolyDyn(const Polynomial<T>& vect):
 Vector<T>(vect), Polynomial<T>(vect), DynamicVector<T>(vect) {}






template <typename T>
PolyDyn<T>& PolyDyn<T>::operator=(const Vector<T>& vect)
{
    this->DynamicVector<T>::operator=(vect);
    this->evalDeg();
    return *this;
}

template <typename T>
PolyDyn<T>& PolyDyn<T>::operator=(const Polynomial<T>& poly)
{
    this->DynamicVector<T>::operator=(poly);
    _deg = poly.deg();
    _degModified = false;
 return *this;
}

template <typename T>
PolyDyn<T>& PolyDyn<T>::operator=(const DynamicVector<T>& vect)
{
    this->DynamicVector<T>::operator=(vect);
    this->evalDeg();
    return *this;
}

template <typename T>
PolyDyn<T>& PolyDyn<T>::operator=(const PolyDyn<T>& poly)
{
    this->DynamicVector<T>::operator=(poly);
    _deg = poly.deg();
    _degModified = false;
    return *this;
}



template <typename T>
PolyDyn<T>& PolyDyn<T>::operator=(Vector<T>&& vect)
{
    this->DynamicVector<T>::operator=(std::move(vect));
    this->evalDeg();
    return *this;
}

template <typename T>
PolyDyn<T>& PolyDyn<T>::operator=(Polynomial<T>&& poly)
{
    this->DynamicVector<T>::operator=(std::move(poly));
    _deg = poly.deg();
    _degModified = false;
 return *this;
}

template <typename T>
PolyDyn<T>& PolyDyn<T>::operator=(DynamicVector<T>&& vect)
{
    this->DynamicVector<T>::operator=(std::move(vect));
    this->evalDeg();
    return *this;
}

template <typename T>
PolyDyn<T>& PolyDyn<T>::operator=(PolyDyn<T>&& poly)
{
 this->DynamicVector<T>::operator=(std::move(poly));
 _deg = poly.deg();
 _degModified = false;
 return *this;
}



template <typename T>
void PolyDyn<T>::operator+=(const Vector<T>& vect)
{
    this->DynamicVector<T>::operator+=(vect);
    this->evalDeg();
}


template <typename T>
void PolyDyn<T>::operator-=(const Vector<T>& vect)
{
    this->DynamicVector<T>::operator-=(vect);
    this->evalDeg();
}



template <typename T>
void PolyDyn<T>::operator*=(const Polynomial<T>& other)
{
 int otherDeg = other.deg();
 int thisDeg = this->deg();
 if (thisDeg==-1 or otherDeg==-1)
 {
  T* oldValues = _values;
  _values = new T[0];
  _dim = 0;
  _deg = -1;
  delete[] oldValues;
 }
 else
 {
  if (otherDeg>0)
  {
   T* oldValues = _values;
   _values = new T[thisDeg + otherDeg + 1];


   for (int j=0; j<=otherDeg; ++j) {_values[j] = oldValues[0] * other[j];}
   for (int i=1; i<=thisDeg; ++i)
   {
    for (int j=0; j<otherDeg; ++j)
    {
     _values[i+j] += oldValues[i] * other[j];
    }
    _values[i+otherDeg] = oldValues[i] * other[otherDeg];
   }
   _degModified = false;
   _deg = thisDeg + otherDeg;
   _dim = _deg+1;
   delete[] oldValues;
  }
  else
  {
   for (int i=0; i<=_deg; ++i) { _values[i] *= other[0]; }
  }
    }
}





template <typename T>
PolyDyn<T> operator+(const Polynomial<T>& polyA, const Polynomial<T>& polyB)
{
    PolyDyn<T> resPoly(polyA);
    resPoly += polyB;
    return resPoly;
}


template <typename T>
PolyDyn<T> operator-(const Polynomial<T>& polyA, const Polynomial<T>& polyB)
{
    PolyDyn<T> resPoly(polyA);
    resPoly -= polyB;
    return resPoly;
}


template <typename T>
PolyDyn<T> operator*(const Polynomial<T>& polyA, const Polynomial<T>& polyB)
{
    PolyDyn<T> resPoly = PolyDyn<T>(polyA);
    resPoly *= polyB;
    return resPoly;
}


template <typename T>
PolyDyn<T> operator+(const PolyDyn<T>& poly)
{
    PolyDyn<T> newPoly(poly);
    newPoly.unary_plus();
    return newPoly;
}


template <typename T>
PolyDyn<T> operator-(const PolyDyn<T>& poly)
{
    PolyDyn<T> newPoly(poly);
    newPoly.unary_minus();
    return newPoly;
}


#endif
