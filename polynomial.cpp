#include <iostream>
#include <sstream>
#include <stdexcept>
#include <cmath>
#include "polynomial.hpp"
using namespace std;


Polynomial::Polynomial()
{
    coeff = new double [DEFAULTPOLY];
    for (int i = 0; i < (int) DEFAULTPOLY; i++)
    {
        coeff[i] = 0.0;
    }
    maxPoly = DEFAULTPOLY;
}


Polynomial::Polynomial(size_t size)
{
    coeff = new double[size];
    for (int i = 0; i < (int) size; i++)
    {
        coeff[i] = 0.0;
    }
    maxPoly = size;
}


Polynomial::Polynomial(const Polynomial& aPoly)
{
    coeff = new double[aPoly.maxPoly];
    for (int i = 0; i < (int) aPoly.maxPoly; i++)
    {
        coeff[i] = aPoly.coeff[i];
    }
    maxPoly = aPoly.maxPoly;
}


Polynomial::~Polynomial()
{
    delete[] coeff;
}

const Polynomial& Polynomial::operator= (const Polynomial& rhs)
{
    if (this == &rhs){
        return *this;
    }
    Polynomial tmp(rhs);
    std::swap(maxPoly, tmp.maxPoly);
    std::swap(coeff, tmp.coeff);
    return *this;
}


size_t Polynomial::maxSize() const
{
    size_t maxSize = maxPoly;
    return maxSize;
}


void Polynomial::grow(size_t newSize)
{
    int arrSize = (int) maxPoly;
    if ((int) newSize > arrSize)
    {
        double* newArrPtr = new double[newSize];
        for (int i = 0; i < arrSize; i++)
        {
            newArrPtr[i] = coeff[i];
        }
        std::swap(newArrPtr, coeff);
        std::swap(newSize, maxPoly);
    }

}

size_t Polynomial::degree() const
{
    size_t degree = 0;
    for (int i = 0; i < (int)maxPoly; i++)
    {
        if (coeff[i] != 0)
        {
            degree = (size_t)i;
        }
    }
    return degree;
}


void Polynomial::setCoeff(double value, size_t i)
{
    if ((size_t)0 <= i && i <= maxPoly)
    {
        if (i > maxPoly)
        {
            grow(i);
        }
        coeff[i] = value;
    }
    else
    {
        throw std::out_of_range("Index out of range");
    }
}

double Polynomial::retrieveCoeff(size_t i) const
{
    if (0 <= (int)i)
    {
        return coeff[i];
    }
    else if (i >= (int)maxPoly)
    {
        return 0.0;
    }
    else
    {
        throw std::out_of_range("Index out of range");
    }
}

void Polynomial::incrementCoeff(double value, size_t i)
{
    if (0 <= (int)i)
    {
        if (i > (int)maxPoly)
        {
            grow(i);
        }
        coeff[i] *= value;
    }
    else
    {
        throw std::out_of_range("Index out of range");
    }

}

string Polynomial::toString() const
{
    ostringstream result;
    bool printedSomething = false;
    for (int i = (int)degree(); i >= 0; i--)
    {
        double c = retrieveCoeff(i);
        if (c != 0.0)
        {
            printedSomething = true;
            if (i == 0)
            {
                result.setf(ios::showpos);
                result << " " << c;
                result.unsetf(ios::showpos);
            }
            else
            {
                result.setf(ios::showpos);
                result << " " << c;
                result.unsetf(ios::showpos);
                result << "*X^" << i;
            }
        }
    }
    if (!printedSomething)
    {
        result.setf(ios::showpos);
        result << " " << 0;
        result.unsetf(ios::showpos);
    }
    return result.str();

}


size_t Polynomial::numOfTerms() const
{
    size_t numTerms = 0;
    for (int i = 0; i < (int)maxPoly; i++)
    {
        if (coeff[i] != 0)
        {
            numTerms++;
        }
    }
    return numTerms;
}

double Polynomial::evaluate(double x) const
{
    double polyTotal = 0.0;
    double coeff = 0.0;
    for (int i = 0; i < (int) maxPoly; i++)
    {
        coeff = retrieveCoeff((size_t) i);
        polyTotal += (coeff * pow(x, (double)i));
    }
    return polyTotal;
}

void Polynomial::add(const Polynomial& aPoly)
{
    if (aPoly.maxPoly > maxPoly)
    {
        grow(aPoly.maxPoly);
    }
    for (int i = 0; i < (int)maxPoly; i++)
    {
        coeff[i] += aPoly.coeff[i];
    }
}

void Polynomial::subtract(const Polynomial& aPoly)
{
    if (aPoly.maxPoly > maxPoly)
    {
        grow(aPoly.maxPoly);
    }
    for (int i = 0; i < (int) maxPoly; i++)
    {
        coeff[i] -= aPoly.coeff[i];
    }
}

Polynomial Polynomial::operator+ (const Polynomial& rhs) const
{
    Polynomial result;
    result.add(*this);
    result.add(rhs);
    return result;
}

Polynomial Polynomial::operator- (const Polynomial& rhs) const
{
    Polynomial result;
    result.subtract(*this);
    result.subtract(rhs);
    return result;
}

bool Polynomial::equals(const Polynomial& aPoly) const
{
    if (maxPoly != aPoly.maxPoly)
    {
        return(false);
    }
    for (int i = 0; i < (int) maxPoly; i++)
    {
        if (aPoly.coeff[i] != coeff[i])
        {
            return(false);
        }
    }
    return(true);
}


bool Polynomial::operator== (const Polynomial& rhs) const
{
    return equals(rhs);
}

bool Polynomial::operator!= (const Polynomial& rhs) const
{
    return !equals(rhs);
}


void Polynomial::negate()
{
    multByConst(-1.0);
}

void Polynomial::multByConst(double val)
{
    double* tmpArray = new double[maxPoly];
    for (int i = 0; i < (int)maxPoly; i++)
    {
        tmpArray[i] = retrieveCoeff((size_t)i) * val;
    }
    std::swap(tmpArray, coeff);
}

void Polynomial::derivative()
{
    size_t derivArrSize = maxPoly - 1;
    double* derivArrPtr = new double[derivArrSize];
    for (int i = 1; i < (int) maxPoly; i++)
    {
        double coeffOfDeriv = retrieveCoeff((size_t)i) * (double)i;
        i -= 1;
        derivArrPtr[i] = coeffOfDeriv;
    }
    std::swap(derivArrPtr, coeff);
    std::swap(derivArrSize, maxPoly);
}

ostream & operator << (ostream &out, const Polynomial& p)
{
    out << p.toString();
    return out;
}

