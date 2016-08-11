#ifndef POLYMOD_H
#define POLYMOD_H

#include <cstddef>
#include <stdexcept>

#include "polynomialvector.hpp"
#include "staticvector.hpp"

// Miguel Terol Espino
// 000356914
// mteroles@ulb.ac.be

template<typename T>
using Divisor = const Polynomial<T>&;
// Template wont accept Polynomial as template param so we are setting it up as a typename
// as with std basically

template <typename T, unsigned int s, Divisor<T> model>
class ModularPolynomial: public Polynomial<T>, public StaticVector<T, s> {
protected:
    using Polynomial<T>::m_size;
    using Polynomial<T>::_degree;
    using Polynomial<T>::m_content;

public:
    explicit ModularPolynomial(const T&);
    ModularPolynomial(const ModularPolynomial<T, s, model>&);
    explicit ModularPolynomial(const Polynomial<T>&);

    virtual ModularPolynomial<T, s, model>& operator=(const Vector<T>&) override;
    virtual ModularPolynomial<T, s, model>& operator=(const Polynomial<T>&) override;
    virtual ModularPolynomial<T, s, model>& operator=(const StaticVector<T, s>&) override;
    virtual ModularPolynomial<T, s, model>& operator=(const ModularPolynomial<T, s, model>&);

    virtual void operator+=(const Vector<T>&) override;
    virtual void operator-=(const Vector<T>&) override;

    using Polynomial<T>::operator*=;
    void operator*=(const Polynomial<T>&) override;

    using Polynomial<T>::operator[];
};

// Constructors
template <typename T, unsigned int s, Divisor<T> model>
ModularPolynomial<T, s, model>::ModularPolynomial(const T& element): Vector<T>(element, s), Polynomial<T>(element, s), StaticVector<T, s>(element) {}

template <typename T, unsigned int s, Divisor<T> model>
ModularPolynomial<T, s, model>::ModularPolynomial(const ModularPolynomial<T, s, model>& poly): Vector<T>(poly), Polynomial<T>(poly), StaticVector<T, s>(poly) {}

template <typename T, unsigned int s, Divisor<T> model>
ModularPolynomial<T, s, model>::ModularPolynomial(const Polynomial<T>& poly): Vector<T>(poly), Polynomial<T>(poly), StaticVector<T, s>(static_cast<StaticVector<T, s>>(poly)) {}

// Operators
template <typename T, unsigned int s, Divisor<T> model>
ModularPolynomial<T, s, model>& ModularPolynomial<T, s, model>::operator=(const Vector<T>& vect) {
    this->Vector<T>::operator=(vect);
    this->evalDeg();
    return *this;
}

template <typename T, unsigned int s, Divisor<T> model>
ModularPolynomial<T, s, model>& ModularPolynomial<T, s, model>::operator=(const Polynomial<T>& poly) {
    this->Vector<T>::operator=(poly);
    _degree = poly.getDeg();
    return *this;
}

template <typename T, unsigned int s, Divisor<T> model>
ModularPolynomial<T, s, model>& ModularPolynomial<T, s, model>::operator=(const StaticVector<T, s>& vect) {
    this->StaticVector<T, s>::operator=(vect);
    this->evalDeg();
    return *this;
}

template <typename T, unsigned int s, Divisor<T> model>
ModularPolynomial<T, s, model>& ModularPolynomial<T, s, model>::operator=(const ModularPolynomial<T, s, model>& poly) {
    this->StaticVector<T, s>::operator=(poly);
    _degree = poly.getDeg();
    return *this;
}

template <typename T, unsigned int s, Divisor<T> model>
void ModularPolynomial<T, s, model>::operator+=(const Vector<T>& vect) {
    this->StaticVector<T, s>::operator+=(vect);
    this->evalDeg();
}


template <typename T, unsigned int s, Divisor<T> model>
void ModularPolynomial<T, s, model>::operator-=(const Vector<T>& vect) {
    this->StaticVector<T, s>::operator-=(vect);
    this->evalDeg();
}


template <typename T, unsigned int s, Divisor<T> model> // From project set up by profesor
void ModularPolynomial<T, s, model>::operator*=(const Polynomial<T>& other) {
    T* oldValues = m_content;
    m_content = new T[s];
    int otherDeg = other.getDeg();
    int myDeg = this->getDeg();
    int newDeg = _degree < 0 || otherDeg < 0 ? -1 : myDeg + otherDeg;
    int wantDimen = static_cast<int>(s);
    for (int i=0; i<wantDimen && i<=newDeg; ++i) {
        m_content[i] = 0;
        for (int j=(i>otherDeg ? i-otherDeg : 0); j<=i && j<=_degree; j++) {
            m_content[i] += oldValues[j] * other[i-j];
        }
    }
    Polynomial<T> modulator(model);
    for (int i=wantDimen; i<=newDeg; ++i) {
        T mMultip=0;
        for (int j=i-otherDeg; j<= myDeg; ++j) mMultip += oldValues[j] * other[i-j];
        for (int j=0; j<wantDimen; j++) m_content[j] += mMultip * modulator[j];
        T greatestCoeff = modulator[s-1];
        for (int j=wantDimen-1; j>0; j--) {
            modulator[j] = modulator[j-1];
            modulator[j] += greatestCoeff * model[j];
        }
        modulator[0] = greatestCoeff * model[0];
    }
    if (newDeg < wantDimen) {
        for (int i = newDeg+1; i<wantDimen; ++i) m_content[i] = 0;
        _degree = newDeg;
    } else this->evalDeg();
    delete[] oldValues;
}

// Out of class operators
// Most are exactly like Polynomial but have to be overriden to avoid clash with SaticVector methods

template <typename T, unsigned int s, Divisor<T> model>
ModularPolynomial<T, s, model> operator+(const ModularPolynomial<T, s, model>& polyA, const ModularPolynomial<T, s, model>& polyB) {
    ModularPolynomial<T, s, model> polyC(polyA);
    polyC += polyB;
    return polyC;
}


template <typename T, unsigned int s, Divisor<T> model>
ModularPolynomial<T, s, model> operator-(const ModularPolynomial<T, s, model>& polyA, const ModularPolynomial<T, s, model>& polyB) {
    ModularPolynomial<T, s, model> polyC(polyA);
    polyC += polyB;
    return polyC;
}


template <typename T, unsigned int s, Divisor<T> model>
ModularPolynomial<T, s, model> operator*(const ModularPolynomial<T, s, model>& polyA, const ModularPolynomial<T, s, model>& polyB) {
    ModularPolynomial<T, s, model> polyC(polyA);
    polyC *= polyB;
    return polyC;
}


template <typename T, unsigned int s, Divisor<T> model>
ModularPolynomial<T, s, model> operator+(const ModularPolynomial<T, s, model>& poly) {
    ModularPolynomial<T, s, model> newPoly(poly);
    newPoly.unary_plus();
    return newPoly;
}


template <typename T, unsigned int s, Divisor<T> model>
ModularPolynomial<T, s, model> operator-(const ModularPolynomial<T, s, model>& poly) {
    ModularPolynomial<T, s, model> newPoly(poly);
    newPoly.unary_minus();
    return newPoly;
}


#endif
