#ifndef POLYMOD_H
#define POLYMOD_H

#include <cstddef>
#include <stdexcept>

#include "polynomialvector.hpp"
#include "dynamipolynomial.hpp"
#include "staticvector.hpp"



template <typename T>
using PolyDiv = const PolyDyn<T>&;

template <typename T, unsigned int s, PolyDiv<T> DivNeg>
class ModularPolynomial: public Polynomial<T>, public StaticVector<T, s>
{
 protected:
  using Polynomial<T>::_dim;
  using Polynomial<T>::_deg;
  using Polynomial<T>::_values;
  using Polynomial<T>::_degModified;

 public:

        ModularPolynomial();
        explicit ModularPolynomial(const T&);
        explicit ModularPolynomial(const T*);
        ModularPolynomial(const ModularPolynomial<T, s, DivNeg>&);
        ModularPolynomial(ModularPolynomial<T, s, DivNeg>&&);
        explicit ModularPolynomial(const Polynomial<T>&);





  virtual ModularPolynomial<T, s, DivNeg>& operator=(const Vector<T>&) override;
  virtual ModularPolynomial<T, s, DivNeg>& operator=(Vector<T>&&) override;
  virtual ModularPolynomial<T, s, DivNeg>& operator=(const Polynomial<T>&) override;
  virtual ModularPolynomial<T, s, DivNeg>& operator=(Polynomial<T>&&) override;
  virtual ModularPolynomial<T, s, DivNeg>& operator=(const StaticVector<T, s>&) override;
  virtual ModularPolynomial<T, s, DivNeg>& operator=(StaticVector<T, s>&&) override;
  virtual ModularPolynomial<T, s, DivNeg>& operator=(const ModularPolynomial<T, s, DivNeg>&);
  virtual ModularPolynomial<T, s, DivNeg>& operator=(ModularPolynomial<T, s, DivNeg>&&);


  virtual void operator+=(const Vector<T>&) override;
        virtual void operator-=(const Vector<T>&) override;


  using Polynomial<T>::operator*=;
  void operator*=(const Polynomial<T>&) override;
};






template <typename T, unsigned int s, PolyDiv<T> DivNeg>
ModularPolynomial<T, s, DivNeg>::ModularPolynomial():
 Vector<T>(),
 Polynomial<T>(),
 StaticVector<T, s>() {}

template <typename T, unsigned int s, PolyDiv<T> DivNeg>
ModularPolynomial<T, s, DivNeg>::ModularPolynomial(const T& element):
    Vector<T>(element, s),
    Polynomial<T>(element, s),
    StaticVector<T, s>(element) {}

template <typename T, unsigned int s, PolyDiv<T> DivNeg>
ModularPolynomial<T, s, DivNeg>::ModularPolynomial(const T* elemArray):
    Vector<T>(elemArray, s),
    Polynomial<T>(elemArray, s),
    StaticVector<T, s>(elemArray) {}


template <typename T, unsigned int s, PolyDiv<T> DivNeg>
ModularPolynomial<T, s, DivNeg>::ModularPolynomial(const ModularPolynomial<T, s, DivNeg>& poly):
    Vector<T>(poly),
    Polynomial<T>(poly),
    StaticVector<T, s>(poly) {}


template <typename T, unsigned int s, PolyDiv<T> DivNeg>
ModularPolynomial<T, s, DivNeg>::ModularPolynomial(ModularPolynomial<T, s, DivNeg>&& poly):
    Vector<T>(std::forward<ModularPolynomial<T, s, DivNeg>>(poly)),
    Polynomial<T>(std::forward<ModularPolynomial<T, s, DivNeg>>(poly)),
    StaticVector<T, s>(std::forward<ModularPolynomial<T, s, DivNeg>>(poly)) {}


template <typename T, unsigned int s, PolyDiv<T> DivNeg>
ModularPolynomial<T, s, DivNeg>::ModularPolynomial(const Polynomial<T>& poly):
    Vector<T>(poly),
    Polynomial<T>(poly),
    StaticVector<T, s>(static_cast<StaticVector<T, s>>(poly)) {}





template <typename T, unsigned int s, PolyDiv<T> DivNeg>
ModularPolynomial<T, s, DivNeg>& ModularPolynomial<T, s, DivNeg>::operator=(const Vector<T>& vect)
{
    this->StaticVector<T, s>::operator=(vect);
    this->evalDeg();
    return *this;
}

template <typename T, unsigned int s, PolyDiv<T> DivNeg>
ModularPolynomial<T, s, DivNeg>& ModularPolynomial<T, s, DivNeg>::operator=(const Polynomial<T>& poly) {
    this->StaticVector<T, s>::operator=(poly);
    _deg = poly.deg();
    _degModified = false;
    return *this;
}

template <typename T, unsigned int s, PolyDiv<T> DivNeg>
ModularPolynomial<T, s, DivNeg>& ModularPolynomial<T, s, DivNeg>::operator=(const StaticVector<T, s>& vect)
{
    this->StaticVector<T, s>::operator=(vect);
    this->evalDeg();
    return *this;
}

template <typename T, unsigned int s, PolyDiv<T> DivNeg>
ModularPolynomial<T, s, DivNeg>& ModularPolynomial<T, s, DivNeg>::operator=(const ModularPolynomial<T, s, DivNeg>& poly)
{
    this->StaticVector<T, s>::operator=(poly);
    _deg = poly.deg();
    _degModified = false;
    return *this;
}


template <typename T, unsigned int s, PolyDiv<T> DivNeg>
ModularPolynomial<T, s, DivNeg>& ModularPolynomial<T, s, DivNeg>::operator=(Vector<T>&& vect)
{
    this->StaticVector<T, s>::operator=(vect);
    this->evalDeg();
    return *this;
}

template <typename T, unsigned int s, PolyDiv<T> DivNeg>
ModularPolynomial<T, s, DivNeg>& ModularPolynomial<T, s, DivNeg>::operator=(Polynomial<T>&& poly)
{
    this->StaticVector<T, s>::operator=(poly);
    _deg = poly.deg();
    _degModified = false;
    return *this;
}

template <typename T, unsigned int s, PolyDiv<T> DivNeg>
ModularPolynomial<T, s, DivNeg>& ModularPolynomial<T, s, DivNeg>::operator=(StaticVector<T, s>&& vect)
{
    this->StaticVector<T, s>::operator=(vect);
    this->evalDeg();
    return *this;
}

template <typename T, unsigned int s, PolyDiv<T> DivNeg>
ModularPolynomial<T, s, DivNeg>& ModularPolynomial<T, s, DivNeg>::operator=(ModularPolynomial<T, s, DivNeg>&& poly)
{
    this->StaticVector<T, s>::operator=(poly);
    _deg = poly.deg();
    _degModified = false;
    return *this;
}



template <typename T, unsigned int s, PolyDiv<T> DivNeg>
void ModularPolynomial<T, s, DivNeg>::operator+=(const Vector<T>& vect)
{
    this->StaticVector<T, s>::operator+=(vect);
    this->evalDeg();
}


template <typename T, unsigned int s, PolyDiv<T> DivNeg>
void ModularPolynomial<T, s, DivNeg>::operator-=(const Vector<T>& vect)
{
    this->StaticVector<T, s>::operator-=(vect);
    this->evalDeg();
}


template <typename T, unsigned int s, PolyDiv<T> DivNeg>
void ModularPolynomial<T, s, DivNeg>::operator*=(const Polynomial<T>& other)
{

 T* oldValues = _values;
 _values = new T[s];
 int otherDeg = other.deg();
 int thisDeg = this->deg();


    int newDeg = _deg < 0 || otherDeg < 0 ? -1 : thisDeg + otherDeg;
    int DimInt = static_cast<int>(s);


    for (int i=0; i<DimInt && i<=newDeg; ++i)
    {
        _values[i] = 0;

        for (int j=(i>otherDeg ? i-otherDeg : 0); j<=i && j<=_deg; j++)
        {

   _values[i] += oldValues[j] * other[i-j];
        }
    }


 PolyDyn<T> DivMod(DivNeg);
    for (int i=DimInt; i<=newDeg; ++i)
    {
        T mMultip=0;


        for (int j=i-otherDeg; j<= thisDeg; ++j) mMultip += oldValues[j] * other[i-j];


  for (int j=0; j<DimInt; j++) _values[j] += mMultip * DivMod[j];


  T greatestCoeff = DivMod[s-1];
        for (int j=DimInt-1; j>0; j--)
        {
   DivMod[j] = DivMod[j-1];
   DivMod[j] += greatestCoeff * DivNeg[j];
        }
        DivMod[0] = greatestCoeff * DivNeg[0];
    }
    if (newDeg < DimInt)
    {
  for (int i = newDeg+1; i<DimInt; ++i) _values[i] = 0;
  _deg = newDeg;
  _degModified = false;
    }
    else this->evalDeg();
    delete[] oldValues;
}





template <typename T, unsigned int s, PolyDiv<T> DivNeg>
ModularPolynomial<T, s, DivNeg> operator+(const ModularPolynomial<T, s, DivNeg>& polyA, const ModularPolynomial<T, s, DivNeg>& polyB)
{
 ModularPolynomial<T, s, DivNeg> resPoly(polyA);
    resPoly += polyB;
    return resPoly;
}


template <typename T, unsigned int s, PolyDiv<T> DivNeg>
ModularPolynomial<T, s, DivNeg> operator-(const ModularPolynomial<T, s, DivNeg>& polyA, const ModularPolynomial<T, s, DivNeg>& polyB)
{
    ModularPolynomial<T, s, DivNeg> resPoly(polyA);
    resPoly += polyB;
    return resPoly;
}


template <typename T, unsigned int s, PolyDiv<T> DivNeg>
ModularPolynomial<T, s, DivNeg> operator*(const ModularPolynomial<T, s, DivNeg>& polyA, const ModularPolynomial<T, s, DivNeg>& polyB)
{
    ModularPolynomial<T, s, DivNeg> resPoly(polyA);
    resPoly *= polyB;
    return resPoly;
}


template <typename T, unsigned int s, PolyDiv<T> DivNeg>
ModularPolynomial<T, s, DivNeg> operator+(const ModularPolynomial<T, s, DivNeg>& poly)
{
    ModularPolynomial<T, s, DivNeg> newPoly(poly);
    newPoly.unary_plus();
    return newPoly;
}


template <typename T, unsigned int s, PolyDiv<T> DivNeg>
ModularPolynomial<T, s, DivNeg> operator-(const ModularPolynomial<T, s, DivNeg>& poly)
{
    ModularPolynomial<T, s, DivNeg> newPoly(poly);
    newPoly.unary_minus();
    return newPoly;
}


#endif
