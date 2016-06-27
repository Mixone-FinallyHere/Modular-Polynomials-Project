#ifndef POLYNOMIAL_HPP
#define POLYNOMIAL_HPP

class Polynomial
{
private:
 int _base;
 Node* _coeff;

 void _show (Node* l, int level);
 real _value0 (Node* l, int x);
public:
 Polynomial (void);
 Polynomial (int base, Node* coeff);
 Polynomial (const Polynomial& a); // clone
 ~Polynomial (); // delete

 Polynomial& operator= (const Polynomial& rhs); // assignment

 Polynomial& operator+= (const Polynomial& rhs); // add
 const Polynomial operator+ (const Polynomial& other) const; //add

 const Polynomial operator- (void) const; //neg

 Polynomial& operator-= (const Polynomial& rhs); // subtract
 const Polynomial operator- (const Polynomial& other) const; //subtract

 Polynomial& operator*= (const Polynomial& rhs); // multiply
 const Polynomial operator* (const Polynomial& other) const; //multiply

 Polynomial& operator^= (int power); // power
 const Polynomial operator^ (int power) const; //power

 real valueAt (real x); // valueAt
 void show (void); // print
};

#endif
