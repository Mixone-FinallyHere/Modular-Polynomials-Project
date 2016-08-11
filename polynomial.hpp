#ifndef _POLYNOMIAL_HPP_
#define _POLYNOMIAL_HPP_

#include "dynamicvector.hpp"

// Miguel Terol Espino
// 000356914
// mteroles@ulb.ac.be

template <typename T>
class Polynomial: public DynamicVector<T> {
protected:
    using DynamicVector<T>::m_size;
    using DynamicVector<T>::m_content;
    int _degree;
public:
    Polynomial(unsigned int size);
    Polynomial(const T&, unsigned int);
    Polynomial(const Polynomial<T>&);
    Polynomial(const DynamicVector<T>&);
    using DynamicVector<T>::operator[];

    virtual Polynomial<T>& operator=(const DynamicVector<T>&) override;
    virtual Polynomial<T>& operator=(const Polynomial<T>&);

    virtual void operator+=(const DynamicVector<T>&);
    virtual void operator-=(const DynamicVector<T>&);

    virtual void operator*=(const T&) override;
    virtual void operator*=(const Polynomial<T>&);

    T operator()(const T&) const;

    void evalDeg();
    int getDeg();
    int getDeg() const;
};


// Constructors
template <typename T>
Polynomial<T>::Polynomial(unsigned int size): DynamicVector<T>(size), _degree(size) {}

template <typename T>
Polynomial<T>::Polynomial(const T& element, unsigned int size): DynamicVector<T>(element, size) {
    this->evalDeg();
}

template <typename T>
Polynomial<T>::Polynomial(const DynamicVector<T>& vect): DynamicVector<T>(vect) {
    this->evalDeg();
}

template <typename T>
Polynomial<T>::Polynomial(const Polynomial<T>& vect): DynamicVector<T>(vect) {
    this->evalDeg();
}


//Operators
template <typename T>
Polynomial<T>& Polynomial<T>::operator=(const DynamicVector<T>& vect) {
    this->DynamicVector<T>::operator=(vect);
    this->evalDeg();
    return *this;
}

template <typename T> // Will only be necessary for Polynomial = ModularPolynomial really
Polynomial<T>& Polynomial<T>::operator=(const Polynomial<T>& poly) {
    this->DynamicVector<T>::operator=(poly);
    this->evalDeg();
    return *this;
}

template <typename T>
void Polynomial<T>::operator+=(const DynamicVector<T>& vect) {
    this->DynamicVector<T>::operator+=(vect);
    this->evalDeg();
}


template <typename T>
void Polynomial<T>::operator-=(const DynamicVector<T>& vect) {
    this->DynamicVector<T>::operator-=(vect);
    this->evalDeg();
}


template <typename T>
void Polynomial<T>::operator*=(const T& value) {
    this->DynamicVector<T>::operator*=(value);
    this->evalDeg();
}

template <typename T> // From project set up by profesor
void Polynomial<T>::operator*=(const Polynomial<T>& other) {
    int otherDeg = other.getDeg();
    int myDeg = this->getDeg();
    if (myDeg==-1 or otherDeg==-1) {
        T* oldValues = m_content;
        m_content = new T[0];
        m_size = 0;
        _degree = -1;
        delete[] oldValues;
    } else {
        if (otherDeg>0) {
            T* oldValues = m_content;
            m_content = new T[myDeg + otherDeg + 1];
            for (int j=0; j<=otherDeg; ++j) {
                m_content[j] = oldValues[0] * other[j];
            }
            for (int i=1; i<=myDeg; ++i) {
                for (int j=0; j<otherDeg; ++j) {
                    m_content[i+j] += oldValues[i] * other[j];
                }
                m_content[i+otherDeg] = oldValues[i] * other[otherDeg];
            }
            _degree = myDeg + otherDeg;
            m_size = _degree+1;
            delete[] oldValues;
        } else {
            for (int i=0; i<=_degree; ++i) {
                m_content[i] *= other[0];
            }
        }
    }
    this->evalDeg();
}

// Evaluation methods
template <typename T>
T Polynomial<T>::operator()(const T& x_value) const {
    int myDeg = this->getDeg();
    T result;
    if (myDeg==-1) {
        result=0;
    } else {
        unsigned int i=_degree;
        result=m_content[i];
        while (i>0) {
            --i;
            result *= x_value;
            result += m_content[i];
        }
    }
    return result;
}

template<typename T>
void Polynomial<T>::evalDeg() {
    this->_degree = static_cast<int>(this->m_size)-1;
    while (this->_degree >=0 and this->m_content[this->_degree] == 0 ) {
        --this->_degree;
    }
}

template<typename T>
int Polynomial<T>::getDeg() {
    return _degree;
}

template<typename T>
int Polynomial<T>::getDeg() const{
    return _degree;
}

// Out of class operators
template <typename T>
std::ostream& operator<<(std::ostream& ostr, const Polynomial<T>& poly) {
    int myDeg = poly.getDeg();
    if (myDeg==-1) {
        ostr << 0;
    } else {
        bool first = true;
        for (int i=myDeg; i>=0; --i) {
            if (first) {
                first=false;
                ostr << poly[i];
            } else {
                if (poly[i] < 0) ostr << " - " << poly[i];
                else ostr << " + " << poly[i];
            }
            if (i>1) {
                ostr<< "x^" << i;
            } else {
                if (i==1) {
                    ostr << "x";
                }
            }
        }
    }
    return ostr;
}

template <typename T> // Very ugly done should be done using friend maybe?
std::istream& operator>>(std::istream& input, Polynomial<T>& poly) {
    DynamicVector<T> temp = poly;
    std::cin >> temp;
    poly = temp;
    poly.evalDeg();
    return input; // Works like a charm though
}

template <typename T>
Polynomial<T> operator+(const Polynomial<T>& polyA, const Polynomial<T>& polyB) {
    Polynomial<T> polyC(polyA);
    polyC += polyB;
    return polyC;
}


template <typename T>
Polynomial<T> operator-(const Polynomial<T>& polyA, const Polynomial<T>& polyB) {
    Polynomial<T> polyC(polyA);
    polyC -= polyB;
    return polyC;
}

template <typename T>
Polynomial<T> operator*(const Polynomial<T>& polyA, const Polynomial<T>& polyB) {
    Polynomial<T> polyC = Polynomial<T>(polyA);
    polyC *= polyB;
    return polyC;
}


template <typename T>
Polynomial<T> operator+(const Polynomial<T>& poly) {
    Polynomial<T> newPoly(poly);
    newPoly.unary_plus();
    return newPoly;
}

template <typename T>
Polynomial<T> operator-(const Polynomial<T>& poly) {
    Polynomial<T> newPoly(poly);
    newPoly.unary_minus();
    return newPoly;
}


#endif
