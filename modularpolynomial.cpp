#include "modularpolynomial.hpp"

ModularPolynomial::ModularPolynomial()
{
    //ctor
}

ModularPolynomial::~ModularPolynomial()
{
    _base = a._base;
   _coeff = copy(a._coeff);
}

ModularPolynomial::ModularPolynomial(const ModularPolynomial& other)
{
    //copy ctor
}

ModularPolynomial& ModularPolynomial::operator=(const ModularPolynomial& rhs)
{
    if (this == &rhs) return *this; // handle self assignment
    //assignment operator
    return *this;
}
