#ifndef POLYMOD_H
#define POLYMOD_H

#include <cstddef>
#include <stdexcept>

#include "polynomialvector.hpp"
#include "dynamipolynomial.hpp"
#include "staticvector.hpp"



template <typename Elem>
using PolyDiv = const PolyDyn<Elem>&;//Typedef de PolyDiv "a la C++11" (alias template)

template <typename Elem, std::size_t Dimens, PolyDiv<Elem> DivNeg>
class PolyMod: public VectPoly<Elem>, public StaticVector<Elem, Dimens>
{
	protected:
		using VectPoly<Elem>::_dim;
		using VectPoly<Elem>::_deg;
		using VectPoly<Elem>::_values;
		using VectPoly<Elem>::_degModified;

	public:
		/**Constructeurs**/
        PolyMod();				//trivial
        explicit PolyMod(const Elem&);	// init: valeur (taille parametrique)
        explicit PolyMod(const Elem*);	// init: tableau valeurs (taille parametrique)
        PolyMod(const PolyMod<Elem, Dimens, DivNeg>&);	//de copie
        PolyMod(PolyMod<Elem, Dimens, DivNeg>&&);		//de transfert
        explicit PolyMod(const VectPoly<Elem>&);		//de conversion

        /**Destructeur**/
        //Pas besoin de destructeur autre que celui de classe de base

		/**Operateurs**/
		virtual PolyMod<Elem, Dimens, DivNeg>& operator=(const Vector<Elem>&) override;		//=Vector (redefini)
		virtual PolyMod<Elem, Dimens, DivNeg>& operator=(Vector<Elem>&&) override;
		virtual PolyMod<Elem, Dimens, DivNeg>& operator=(const VectPoly<Elem>&) override;	//=VectPoly (redefini)
		virtual PolyMod<Elem, Dimens, DivNeg>& operator=(VectPoly<Elem>&&) override;
		virtual PolyMod<Elem, Dimens, DivNeg>& operator=(const StaticVector<Elem, Dimens>&) override;	//=StaticVector (redefini)
		virtual PolyMod<Elem, Dimens, DivNeg>& operator=(StaticVector<Elem, Dimens>&&) override;
		virtual PolyMod<Elem, Dimens, DivNeg>& operator=(const PolyMod<Elem, Dimens, DivNeg>&);	//=PolyMod (copie)
		virtual PolyMod<Elem, Dimens, DivNeg>& operator=(PolyMod<Elem, Dimens, DivNeg>&&);


		virtual void operator+=(const Vector<Elem>&) override;	//Addition d'un vecteur (idem pour polynomes)
        virtual void operator-=(const Vector<Elem>&) override;	//Soustraction d'un vecteur


		using VectPoly<Elem>::operator*=; //Multiplication par element
		void operator*=(const VectPoly<Elem>&) override; //Multiplication par polynome
};



/**--------------------CONSTRUCTEURS**/

/**initialisants**/
template <typename Elem, std::size_t Dimens, PolyDiv<Elem> DivNeg>
PolyMod<Elem, Dimens, DivNeg>::PolyMod():
	Vector<Elem>(),
	VectPoly<Elem>(),
	StaticVector<Elem, Dimens>() {} //Ctr par defaut (trivial): polynome nul

template <typename Elem, std::size_t Dimens, PolyDiv<Elem> DivNeg>
PolyMod<Elem, Dimens, DivNeg>::PolyMod(const Elem& element):
    Vector<Elem>(element, Dimens),
    VectPoly<Elem>(element, Dimens),
    StaticVector<Elem, Dimens>(element) {} //Ctr correspondants de classes parentes

template <typename Elem, std::size_t Dimens, PolyDiv<Elem> DivNeg>
PolyMod<Elem, Dimens, DivNeg>::PolyMod(const Elem* elemArray):
    Vector<Elem>(elemArray, Dimens),
    VectPoly<Elem>(elemArray, Dimens),
    StaticVector<Elem, Dimens>(elemArray) {} //Ctr correspondants de classes parentes

/**de copie**/
template <typename Elem, std::size_t Dimens, PolyDiv<Elem> DivNeg>
PolyMod<Elem, Dimens, DivNeg>::PolyMod(const PolyMod<Elem, Dimens, DivNeg>& poly):
    Vector<Elem>(poly),
    VectPoly<Elem>(poly),
    StaticVector<Elem, Dimens>(poly) {} //Appelle ctrs. copie

/**de transfert**/
template <typename Elem, std::size_t Dimens, PolyDiv<Elem> DivNeg>
PolyMod<Elem, Dimens, DivNeg>::PolyMod(PolyMod<Elem, Dimens, DivNeg>&& poly):
    Vector<Elem>(std::forward<PolyMod<Elem, Dimens, DivNeg>>(poly)),
    VectPoly<Elem>(std::forward<PolyMod<Elem, Dimens, DivNeg>>(poly)),
    StaticVector<Elem, Dimens>(std::forward<PolyMod<Elem, Dimens, DivNeg>>(poly)) {} //Appelle ctrs. transfert

/**de conversion**/
template <typename Elem, std::size_t Dimens, PolyDiv<Elem> DivNeg>
PolyMod<Elem, Dimens, DivNeg>::PolyMod(const VectPoly<Elem>& poly):
    Vector<Elem>(poly),
    VectPoly<Elem>(poly),
    StaticVector<Elem, Dimens>(static_cast<StaticVector<Elem, Dimens>>(poly)) {}



/**--------------------OPERATEURS**/
/**assignation a vecteur**/
template <typename Elem, std::size_t Dimens, PolyDiv<Elem> DivNeg>
PolyMod<Elem, Dimens, DivNeg>& PolyMod<Elem, Dimens, DivNeg>::operator=(const Vector<Elem>& vect)
{
    this->StaticVector<Elem, Dimens>::operator=(vect);//Appel a la methode de StaticVector
    this->evalDeg(); //Met degre a jour
    return *this;
}
/**assignation a vecteur polynome**/
template <typename Elem, std::size_t Dimens, PolyDiv<Elem> DivNeg>
PolyMod<Elem, Dimens, DivNeg>& PolyMod<Elem, Dimens, DivNeg>::operator=(const VectPoly<Elem>& poly) {
    this->StaticVector<Elem, Dimens>::operator=(poly);//Appel a la methode de StaticVector
    _deg = poly.deg();
    _degModified = false; //Degre mis a jour
    return *this;
}
/**assignation a vecteur statique**/
template <typename Elem, std::size_t Dimens, PolyDiv<Elem> DivNeg>
PolyMod<Elem, Dimens, DivNeg>& PolyMod<Elem, Dimens, DivNeg>::operator=(const StaticVector<Elem, Dimens>& vect)
{
    this->StaticVector<Elem, Dimens>::operator=(vect);//Appel a la methode de StaticVector
    this->evalDeg(); //Met degre a jour
    return *this;
}
/**assignation a polynome modulaire**/
template <typename Elem, std::size_t Dimens, PolyDiv<Elem> DivNeg>
PolyMod<Elem, Dimens, DivNeg>& PolyMod<Elem, Dimens, DivNeg>::operator=(const PolyMod<Elem, Dimens, DivNeg>& poly)
{
    this->StaticVector<Elem, Dimens>::operator=(poly);//Appel a la methode de StaticVector
    _deg = poly.deg();
    _degModified = false; //Degre mis a jour
    return *this;
}

/**transfert d'un vecteur**/
template <typename Elem, std::size_t Dimens, PolyDiv<Elem> DivNeg>
PolyMod<Elem, Dimens, DivNeg>& PolyMod<Elem, Dimens, DivNeg>::operator=(Vector<Elem>&& vect)
{
    this->StaticVector<Elem, Dimens>::operator=(vect);//Appel a la methode de StaticVector
    this->evalDeg(); //Met degre a jour
    return *this;
}
/**transfert d'un polynome**/
template <typename Elem, std::size_t Dimens, PolyDiv<Elem> DivNeg>
PolyMod<Elem, Dimens, DivNeg>& PolyMod<Elem, Dimens, DivNeg>::operator=(VectPoly<Elem>&& poly)
{
    this->StaticVector<Elem, Dimens>::operator=(poly);//Appel a la methode de StaticVector
    _deg = poly.deg();
    _degModified = false; //Degre mis a jour
    return *this;
}
/**transfert d'un vecteur statique**/
template <typename Elem, std::size_t Dimens, PolyDiv<Elem> DivNeg>
PolyMod<Elem, Dimens, DivNeg>& PolyMod<Elem, Dimens, DivNeg>::operator=(StaticVector<Elem, Dimens>&& vect)
{
    this->StaticVector<Elem, Dimens>::operator=(vect);//Appel a la methode de StaticVector
    this->evalDeg(); //Met degre a jour
    return *this;
}
/**transfert d'un polynome modulaire**/
template <typename Elem, std::size_t Dimens, PolyDiv<Elem> DivNeg>
PolyMod<Elem, Dimens, DivNeg>& PolyMod<Elem, Dimens, DivNeg>::operator=(PolyMod<Elem, Dimens, DivNeg>&& poly)
{
    this->StaticVector<Elem, Dimens>::operator=(poly);//Appel a la methode de StaticVector
    _deg = poly.deg();
    _degModified = false; //Degre mis a jour
    return *this;
}


/**op+= addition d'un vecteur (idem pour polynome)**/
template <typename Elem, std::size_t Dimens, PolyDiv<Elem> DivNeg>
void PolyMod<Elem, Dimens, DivNeg>::operator+=(const Vector<Elem>& vect)
{
    this->StaticVector<Elem, Dimens>::operator+=(vect); //Appelle op. += de StaticVector
    this->evalDeg(); //Met degre a jour
}

/**op-= soustraction d'un vecteur (idem pour polynome)**/
template <typename Elem, std::size_t Dimens, PolyDiv<Elem> DivNeg>
void PolyMod<Elem, Dimens, DivNeg>::operator-=(const Vector<Elem>& vect)
{
    this->StaticVector<Elem, Dimens>::operator-=(vect); //Appelle op. -= de StaticVector
    this->evalDeg(); //Met degre a jour
}

/**op*= multiplication par polynome**/
template <typename Elem, std::size_t Dimens, PolyDiv<Elem> DivNeg>
void PolyMod<Elem, Dimens, DivNeg>::operator*=(const VectPoly<Elem>& other)
{
	//Multiplie this par polynome other, modulo (x^Dimens - Diviseur = DivNeg)
	Elem* oldValues = _values;
	_values = new Elem[Dimens]; //Nouvelles valeurs
	int otherDeg = other.deg();
	int thisDeg = this->deg();

	//Degre qui resulterait de la multiplication SANS MODULO
    int newDeg = _deg < 0 || otherDeg < 0 ? -1 : thisDeg + otherDeg;
    int DimInt = static_cast<int>(Dimens);

	//Degres < Dimens : partie sans modulo
    for (int i=0; i<DimInt && i<=newDeg; ++i) //Parcourt degres (<Dimens) de polynome resultant
    {
        _values[i] = 0; //Initialise le coefficient i
        //Parcourt valeurs j telles que (0 <= j <= _deg) et (0 <= i-j <= otherDeg)
        for (int j=(i>otherDeg ? i-otherDeg : 0); j<=i && j<=_deg; j++) //Calcule coeff.
        {
			//Somme des coeffs dont la somme des degres vaut i : j+(i-j)=i
			_values[i] += oldValues[j] * other[i-j]; //Ajoute produit au coeff de degre i
        }
    }

	//Degres >= Dimens : doit appliquer modulo
	PolyDyn<Elem> DivMod(DivNeg); //Valeur modulaire correspondant a x^i
    for (int i=DimInt; i<=newDeg; ++i) //Parcourt degres (>=Dimens) de polynome resultant
    {
        Elem mMultip=0; //Compteur de multiples du modulo a ajouter au coeff de degre j

        //Parcourt SUITE des valeurs j telles que (0 <= j <= _deg) et (0 <= i-j <= otherDeg)
        for (int j=i-otherDeg; j<= thisDeg; ++j) mMultip += oldValues[j] * other[i-j]; //Calcule multiple

		//Ajoute aux coeff. de this le produit de mMultip et du polynome modulé correspondant à x^i
		for (int j=0; j<DimInt; j++) _values[j] += mMultip * DivMod[j];

		//Ajuste le polynôme modulé à la puissance suivante : x^i * x
		Elem greatestCoeff = DivMod[Dimens-1]; //Coefficient devenant degre Dimens
        for (int j=DimInt-1; j>0; j--)
        {
			DivMod[j] = DivMod[j-1]; //Tous coefficients "montent" de un degré
			DivMod[j] += greatestCoeff * DivNeg[j]; //On ajoute le polynôme diviseur fois le coeff de degre i+1
        }
        DivMod[0] = greatestCoeff * DivNeg[0]; //Coeff de plus bas degré
    }
    if (newDeg < DimInt)
    {
		for (int i = newDeg+1; i<DimInt; ++i) _values[i] = 0; //Initialise coeff restants si necessaire
		_deg = newDeg; //Le degre resultant n'a pas ete affecte par le modulo -> on le conserve
		_degModified = false; //Degre est a jour
    }
    else this->evalDeg(); //Le degre resultat peut avoir ete modifie -> on le reevalue
    delete[] oldValues;
}


/**--------------------HORS CLASSE**/

/**addition binaire entre PolyMod de meme type**/
template <typename Elem, std::size_t Dimens, PolyDiv<Elem> DivNeg>
PolyMod<Elem, Dimens, DivNeg> operator+(const PolyMod<Elem, Dimens, DivNeg>& polyA, const PolyMod<Elem, Dimens, DivNeg>& polyB)
{
	PolyMod<Elem, Dimens, DivNeg> resPoly(polyA); //Copie de polyA comme Polynome Modulaire
    resPoly += polyB;
    return resPoly; //Retourne par valeur (effc++)
}

/**soustraction binaire entre PolyMod de meme type**/
template <typename Elem, std::size_t Dimens, PolyDiv<Elem> DivNeg>
PolyMod<Elem, Dimens, DivNeg> operator-(const PolyMod<Elem, Dimens, DivNeg>& polyA, const PolyMod<Elem, Dimens, DivNeg>& polyB)
{
    PolyMod<Elem, Dimens, DivNeg> resPoly(polyA); //Copie de polyA comme Polynome Modulaire
    resPoly += polyB;
    return resPoly; //Retourne par valeur (effc++)
}

/**multiplication de PolyMod de meme type**/
template <typename Elem, std::size_t Dimens, PolyDiv<Elem> DivNeg>
PolyMod<Elem, Dimens, DivNeg> operator*(const PolyMod<Elem, Dimens, DivNeg>& polyA, const PolyMod<Elem, Dimens, DivNeg>& polyB)
{
    PolyMod<Elem, Dimens, DivNeg> resPoly(polyA); //Copie de polyA comme Polynome Modulaire
    resPoly *= polyB;
    return resPoly; //Retourne par valeur (effc++)
}

/**plus unaire**/
template <typename Elem, std::size_t Dimens, PolyDiv<Elem> DivNeg>
PolyMod<Elem, Dimens, DivNeg> operator+(const PolyMod<Elem, Dimens, DivNeg>& poly)
{
    PolyMod<Elem, Dimens, DivNeg> newPoly(poly); //Ctr copie
    newPoly.unary_plus();
    return newPoly; //Retourne par valeur (effc++)
}

/**moins unaire**/
template <typename Elem, std::size_t Dimens, PolyDiv<Elem> DivNeg>
PolyMod<Elem, Dimens, DivNeg> operator-(const PolyMod<Elem, Dimens, DivNeg>& poly)
{
    PolyMod<Elem, Dimens, DivNeg> newPoly(poly); //Ctr copie
    newPoly.unary_minus();
    return newPoly; //Retourne par valeur (effc++)
}


#endif // POLYMOD_H
