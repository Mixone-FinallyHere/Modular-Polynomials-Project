#ifndef VECTPOLY_H
#define VECTPOLY_H

#include <cstddef>
#include <stdexcept>

#include "vector.hpp"


template <typename T>
class Polynomial: virtual public Vector<T>
{
 protected:
  using Vector<T>::_dim;
  using Vector<T>::_values;

  int _degree;
  void evalDeg() const;


 public:

        Polynomial();
        Polynomial(const T&, unsigned int);
        Polynomial(const Polynomial<T>&);
        Polynomial(Polynomial<T>&&);
        Polynomial(const Vector<T>&);





  using Vector<T>::operator[];
  virtual inline T& operator[] (std::ptrdiff_t) override;

        virtual Polynomial<T>& operator=(const Vector<T>&) override =0;
        virtual Polynomial<T>& operator=(Vector<T>&&) override =0;
  virtual Polynomial<T>& operator=(const Polynomial<T>&) =0;
  virtual Polynomial<T>& operator=(Polynomial<T>&&) =0;

        virtual void operator+=(const Vector<T>&) override =0;
        virtual void operator-=(const Vector<T>&) override =0;

  virtual void operator*=(const T&) override;
        virtual void operator*=(const Polynomial<T>&) =0;




        inline int deg() const { if (_degModified) this->evalDeg(); return _deg; };
        T operator()(const T&) const;
        virtual std::ostream& print(std::ostream& ostr) const override;
        virtual std::istream& iread(std::istream& istr) override;
};




template<typename T>
void Polynomial<T>::evalDeg(){
     _degree=static_cast<int>(_dim)-1;
     while (_deg>=0 and _values[_deg]==0) --_deg;
}


template <typename T>
Polynomial<T>::Polynomial():
 Vector<T>(), _deg(-1) {}

template <typename T>
Polynomial<T>::Polynomial(const T& element, unsigned int dim):
    Vector<T>(element, dim), _deg(-1) { if (element!=0) _deg=static_cast<int>(dim)-1;}

template <typename T>
Polynomial<T>::Polynomial(const T* elemArray, unsigned int dim):
    Vector<T>(elemArray, dim), _deg(-1) { evalDeg(); }


template <typename T>
Polynomial<T>::Polynomial(const Polynomial<T>& vect):
    Vector<T>(vect), _deg(vect.deg()) {}


template <typename T>
Polynomial<T>::Polynomial(Polynomial<T>&& vect):
    Vector<T>(std::forward<Polynomial<T>>(vect)), _deg(vect._deg) {}


template <typename T>
Polynomial<T>::Polynomial(const Vector<T>& vect):
    Vector<T>(vect), _deg(-1) { evalDeg(); }





template <typename T>
T& Polynomial<T>::operator[] (std::ptrdiff_t i)
{
    _degModified = true;
    return this->Vector<T>::operator[](i);
}


template <typename T>
void Polynomial<T>::operator*=(const T& value)
{
    this->Vector<T>::operator*=(value);
    if (value==0) { _deg=-1; _degModified=false; }
}




template <typename T>
std::ostream& Polynomial<T>::print(std::ostream& ostr) const {
 int thisDeg = this->deg();
 if (thisDeg==-1) { ostr << 0; }
 else {
  bool first = true;
  for (int i=thisDeg; i>=0; --i){
   if (first){
    first=false;
    ostr << _values[i];
   }else{
    if (_values[i] < 0) ostr << " - " << -_values[i];
    else ostr << " + " << _values[i];
   }
   if (i>1) { ostr<< "x^" << i; }
   else{
                if (i==1) { ostr << "x"; }

   }
  }
 }
 return ostr;
}


template <typename T>
std::istream& Polynomial<T>::iread(std::istream& istr)
{
    this->Vector<T>::iread(istr);
    this->evalDeg();
    return istr;
}


template <typename T>
T Polynomial<T>::operator()(const T& var_poly) const
{
 int thisDeg = this->deg();
 T result;
 if (thisDeg==-1) { result=0; }
 else
 {
  unsigned int i=_deg;
  result=_values[i];
  while (i>0)
  {
    --i;
             result *= var_poly;
             result += _values[i];
  }
 }
    return result;
}

#endif
