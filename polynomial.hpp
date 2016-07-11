#ifndef POLYNOMIAL_HPP
#define POLYNOMIAL_HPP

#include <string>
#include "dynamicvector.hpp"
using namespace std;


// default size of our dynamic coefficient array
const size_t DEFAULTPOLY = 50;

template<class T>
class Polynomial: friend DynamicVector<T>
{

private:

  size_t maxPoly;    // size of array
  double *coeff;     // dynamic array

public:

  Polynomial ();
  Polynomial (size_t size);
  Polynomial (const Polynomial& aPoly);
  ~Polynomial ();
  const Polynomial& operator= (const Polynomial& rhs);
  size_t maxSize() const;
  void grow (size_t newSize);
  size_t degree () const;
  void setCoeff (double value, size_t i);
  double retrieveCoeff (size_t i) const;
  void incrementCoeff (double value, size_t i);
  string toString () const;
  size_t numOfTerms () const;
  double evaluate (double x) const;
  void add (const Polynomial& aPoly);
  void subtract (const Polynomial& aPoly);
  Polynomial operator+ (const Polynomial& rhs) const;
  Polynomial operator- (const Polynomial& rhs) const;
  bool equals (const Polynomial& aPoly) const;
  bool operator== (const Polynomial& rhs) const;
  bool operator!= (const Polynomial& rhs) const;
  void negate ();
  void multByConst (double val);
  void derivative ();
  friend ostream& operator<< (ostream& os, const Polynomial &p);
};
#endif

