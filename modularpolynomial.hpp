#ifndef MODULARPOLYNOMIAL_HPP
#define MODULARPOLYNOMIAL_HPP

#include <polynomial.hpp>


class ModularPolynomial : public polynomial
{
    public:
        ModularPolynomial();
        virtual ~ModularPolynomial();
        ModularPolynomial(const ModularPolynomial& other);
        ModularPolynomial& operator=(const ModularPolynomial& other);
    protected:
    private:
};

#endif // MODULARPOLYNOMIAL_HPP
