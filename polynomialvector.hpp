#ifndef VECTPOLY_H
#define VECTPOLY_H

#include <cstddef>
#include <stdexcept>

#include "vector.hpp"


template <typename Elem>
class VectPoly: virtual public Vector<Elem>
{
	protected:
		using Vector<Elem>::_dim;
		using Vector<Elem>::_values;

		int _degree;
		void evalDeg() const;


	public:
		/**Constructeurs (protected car classe abstraite)**/
        VectPoly();							// trivial
        VectPoly(const Elem&, std::size_t);	// init: valeur + taille
        VectPoly(const VectPoly<Elem>&);	// de copie
        VectPoly(VectPoly<Elem>&&);			// de transfert
        VectPoly(const Vector<Elem>&);		// de conversion

        /**Destructeur**/
        //Pas besoin de destructeur autre que celui de classe de base

		/**Operateurs**/
		using Vector<Elem>::operator[]; //Accès (evite de cacher)
		virtual inline Elem& operator[] (std::ptrdiff_t) override; //Redefinit modification

        virtual VectPoly<Elem>& operator=(const Vector<Elem>&) override =0; //Assignation a vecteur
        virtual VectPoly<Elem>& operator=(Vector<Elem>&&) override =0;		//Transfert d'un vecteur
		virtual VectPoly<Elem>& operator=(const VectPoly<Elem>&) =0; //Assignation a polynome
		virtual VectPoly<Elem>& operator=(VectPoly<Elem>&&) =0; 	 //Transfert d'un polynome

        virtual void operator+=(const Vector<Elem>&) override =0;	//Addition d'un vecteur
        virtual void operator-=(const Vector<Elem>&) override =0;	//Soustraction d'un vecteur

		virtual void operator*=(const Elem&) override; 	//Multiplication par element
        virtual void operator*=(const VectPoly<Elem>&) =0; //Multiplication par vecteur polynome


		/**Autres methodes**/
		//Retourne le degre du polynome, reevalue si necessaire
        inline int deg() const { if (_degModified) this->evalDeg(); return _deg; };
        Elem operator()(const Elem&) const; //Retourne la valeur numerique du polynome pour x=parametre
        virtual std::ostream& print(std::ostream& ostr) const override;
        virtual std::istream& iread(std::istream& istr) override;
};


/**--------------------CONSTRUCTEURS**/

template<typename T>
void VectPoly<T>::evalDeg(){
     _degree=static_cast<int>(_dim)-1;
     while (_deg>=0 and _values[_deg]==0) --_deg;
}

/**initialisants**/
template <typename Elem>
VectPoly<Elem>::VectPoly():
	Vector<Elem>(), _deg(-1) {} //Ctr par defaut (trivial) : polynome nul

template <typename Elem>
VectPoly<Elem>::VectPoly(const Elem& element, std::size_t dim): //Ctr correspondant de Vector
    Vector<Elem>(element, dim), _deg(-1) { if (element!=0) _deg=static_cast<int>(dim)-1;}

template <typename Elem>
VectPoly<Elem>::VectPoly(const Elem* elemArray, std::size_t dim):
    Vector<Elem>(elemArray, dim), _deg(-1) { evalDeg(); } //Ctr correspondant de Vector

/**de copie**/
template <typename Elem>
VectPoly<Elem>::VectPoly(const VectPoly<Elem>& vect):
    Vector<Elem>(vect), _deg(vect.deg()) {} //Appelle ctr. copie

/**de transfert**/
template <typename Elem>
VectPoly<Elem>::VectPoly(VectPoly<Elem>&& vect):
    Vector<Elem>(std::forward<VectPoly<Elem>>(vect)), _deg(vect._deg) {} //Appelle ctr. transfert

/**de conversion**/
template <typename Elem>
VectPoly<Elem>::VectPoly(const  Vector<Elem>& vect):
    Vector<Elem>(vect), _deg(-1) { evalDeg(); } //Conversion: copie + evalue degre


/**--------------------OPERATEURS**/

/**modification element**/
template <typename Elem>
Elem& VectPoly<Elem>::operator[] (std::ptrdiff_t i)
{
    _degModified = true; //Le degre devra etre reevalue !
    return this->Vector<Elem>::operator[](i);
}

/**multiplication par element**/
template <typename Elem>
void VectPoly<Elem>::operator*=(const Elem& value)
{
    this->Vector<Elem>::operator*=(value); //Appelle op. *=
    if (value==0) { _deg=-1; _degModified=false; } //Ajuste degre si necessaire
}

/**--------------------AUTRES METHODES**/

/**ecriture sur ostream**/
template <typename Elem>
std::ostream& VectPoly<Elem>::print(std::ostream& ostr) const {
	int thisDeg = this->deg(); //Reevalue degre si necessaire
	if (thisDeg==-1) { ostr << 0; } //Polynome nul
	else {
		bool first = true;
		for (int i=thisDeg; i>=0; --i){
			if (first){
				first=false;
				ostr << _values[i]; //Pas de "+"
			}else{
				if (_values[i] < 0) ostr << " - " << -_values[i]; //Signe, valeur
				else ostr << " + " << _values[i];
			}
			if (i>1) { ostr<< "x^" << i; } //Degre
			else{
                if (i==1) { ostr << "x"; } //x^1
                //IF i==0, pas de x^0
			}
		}
	}
	return ostr;
}

/**lecture d'un istream**/
template <typename Elem>
std::istream& VectPoly<Elem>::iread(std::istream& istr)
{
    this->Vector<Elem>::iread(istr); //Methode de classe parente
    this->evalDeg(); //Reevalue le degre
    return istr;
}

/**evaluation**/
template <typename Elem>
Elem VectPoly<Elem>::operator()(const Elem& var_poly) const
{
	int thisDeg = this->deg(); //Reevalue si necessaire
	Elem result; //Resultat
	if (thisDeg==-1) { result=0; } //Elem doit etre assignable & comparable avec 0
	else
	{
		std::size_t i=_deg;
		result=_values[i];
		while (i>0) //METHODE DE HORNER (commence par plus haut degre)
		{
		 	--i;
             result *= var_poly; //Multiplie par x tous coeff precedents
             result += _values[i]; //Ajoute coeff suivant
		}
	}
    return result; //Retourne par valeur
}

#endif //VECTPOLY_H
