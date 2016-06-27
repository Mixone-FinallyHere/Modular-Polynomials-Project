#include "polynomial.hpp"

Polynomial::Polynomial (void) {
 _base = 0;
 _coeff = EMPTY;
}

Polynomial::Polynomial (int base, Node* coeff) {
 _base = base;
 _coeff = copy(coeff);
}

Polynomial::Polynomial (const Polynomial& a) {
 _base = a._base;
 _coeff = copy(a._coeff);
}

Polynomial::~Polynomial (void) {
 freeAll(_coeff);
}

Polynomial&
Polynomial::operator= (const Polynomial& rhs) {
 if (this == &rhs)
   return *this;

 freeAll(this->_coeff);
 this->_base = rhs._base;
 this->_coeff = copy(rhs._coeff);
 return *this;
}

Polynomial&
Polynomial::operator+= (const Polynomial& rhs) {
 Node* temp_coeff_1;
 Node* temp_coeff_2;
 int result_base;
 if (rhs._base > this->_base) {
   result_base = this->_base;
   temp_coeff_1 = copy(rhs._coeff);
   for (int i = 0; i < (rhs._base - this->_base); i += 1) {
     temp_coeff_1 = prepend(temp_coeff_1, 0);
   }
   temp_coeff_2 = this->_coeff;
 } else {
   result_base = rhs._base;
   temp_coeff_1 = copy(this->_coeff);
   for (int i = 0; i < (this->_base - rhs._base); i += 1) {
     temp_coeff_1 = prepend(temp_coeff_1, 0);
   }
   temp_coeff_2 = rhs._coeff;
 }
 Node* result_coeff = add(temp_coeff_1, temp_coeff_2);
 freeAll(temp_coeff_1);
 freeAll(this->_coeff);
 this->_base = result_base;
 this->_coeff = result_coeff;
 return *this;
}


const Polynomial
Polynomial::operator+ (const Polynomial& other) const {
 Polynomial result = *this;
 result += other;
 return result;
}


const Polynomial
Polynomial::operator- (void) const {
 Polynomial result = *this;
 Node* coeff = scalar_multiply(this->_coeff, -1.0);
 freeAll(result._coeff);
 result._coeff = coeff;
 return result;
}

Polynomial &
Polynomial::operator-= (const Polynomial& rhs) {
 Polynomial result = *this + (-rhs);
 this->_base = result._base;
 freeAll(this->_coeff);
 this->_coeff = copy(result._coeff);
 return *this;
}

const Polynomial
Polynomial::operator- (const Polynomial& rhs) const {
 Polynomial result = *this;
 result -= rhs;
 return result;
}

Polynomial&
Polynomial::operator*= (const Polynomial& rhs) {
 this->_base = this->_base + rhs._base;
 Node* result_coeff = multiply(this->_coeff, rhs._coeff);
 freeAll(this->_coeff);
 this->_coeff = result_coeff;
 return *this;
}

const Polynomial
Polynomial::operator* (const Polynomial& other) const {
 Polynomial result = *this;
 result *= other;
 return result;
}

Polynomial&
Polynomial::operator^= (int power) {
 assert (power >= 1);
 Polynomial result = (*this);
 for (int i = 0; i < power-1; i += 1) {
   result *= (*this);
 }
 this->_base = result._base;
 freeAll(this->_coeff);
 this->_coeff = copy(result._coeff);
 return *this;
}

const Polynomial
Polynomial::operator^ (int power) const {
 Polynomial result = *this;
 result ^= power;
 return result;
}


void
Polynomial::show (void) {
 _show(_coeff, _base);
 std::cout << std::endl;
}

void
Polynomial::_show (Node* l, int level) {
 if (length(l) == 0) {
   return;
 }
 _show(tail(l), level+1);
 real coeff = head(l);
 if (coeff != 0) {
   std::stringstream coeff_str;
   std::stringstream level_str;

   if (coeff > 0 && (length(l) > 1)) {
     coeff_str << "+";
   } else if (coeff < 0) {
     coeff_str << "-";
     coeff = -coeff;
   }
   if (!(coeff == 1.0 && level != 0)) {
     coeff_str << coeff;
   }

   if (level == 0) {
     level_str << "";
   } else if (level == 1) {
     level_str << "x";
   } else if (level > 0) {
     level_str << "x^" << level;
   } else if (level < 0) {
     level_str << "x^(" << level << ")";
   }
   std::cout << coeff_str.str() << level_str.str();
 }
}

real
Polynomial::valueAt (real x) {
 return std::pow(x, _base) * _value0(_coeff, x);
}

real
Polynomial::_value0 (Node* l, int x) {
 if (length(l) == 0) return 0;
 return head(l) + x * _value0(tail(l), x);
}
