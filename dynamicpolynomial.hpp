#ifndef POLYDYN_H
#define POLYDYN_H

#include <cstddef>
#include <stdexcept>

#include "polynomialvector.hpp"
#include "dynamicvector.hpp"




template <typename Elem>
class PolyDyn: public VectPoly<Elem>, public DynamicVector<Elem>
{
	protected:
		using VectPoly<Elem>::_dim;
		using VectPoly<Elem>::_deg;
		using VectPoly<Elem>::_values;
		using VectPoly<Elem>::_degModified;

	public:
		/**Constructeurs**/
        PolyDyn();							//trivial
        PolyDyn(const Elem&, std::size_t);	//init: valeur + taille
        PolyDyn(const Elem*, std::size_t);	//init: tableau valeurs + taille
        PolyDyn(const PolyDyn<Elem>&);		//de copie
        PolyDyn(PolyDyn<Elem>&&);			//de transfert
        PolyDyn(const VectPoly<Elem>&);		//de conversion

        /**Destructeur**/
        //Pas besoin de destructeur autre que celui de classe de base

		/**Operateurs**/
		virtual PolyDyn<Elem>& operator=(const Vector<Elem>&) override;		//=Vector (redefini)
		virtual PolyDyn<Elem>& operator=(Vector<Elem>&&) override;
		virtual PolyDyn<Elem>& operator=(const VectPoly<Elem>&) override;	//=VectPoly (redefini)
		virtual PolyDyn<Elem>& operator=(VectPoly<Elem>&&) override;
		virtual PolyDyn<Elem>& operator=(const DynamicVector<Elem>&) override;	//=DynamicVector (redefini)
		virtual PolyDyn<Elem>& operator=(DynamicVector<Elem>&&) override;
		virtual PolyDyn<Elem>& operator=(const PolyDyn<Elem>&);		//=PolyDyn (copie)
		virtual PolyDyn<Elem>& operator=(PolyDyn<Elem>&&);

		virtual void operator+=(const Vector<Elem>&) override;	//Addition d'un vecteur (idem pour polynomes)
        virtual void operator-=(const Vector<Elem>&) override;	//Soustraction d'un vecteur

		using VectPoly<Elem>::operator*=; //Multiplication par element
		void operator*=(const VectPoly<Elem>&) override; //Multiplication par polynome
};


/**--------------------CONSTRUCTEURS**/

/**initialisants**/
template <typename Elem>
PolyDyn<Elem>::PolyDyn():
	Vector<Elem>(),
	VectPoly<Elem>(),
	DynamicVector<Elem>() {} //Ctr par defaut (trivial): polynome nul

template <typename Elem>
PolyDyn<Elem>::PolyDyn(const Elem& element, std::size_t dim):
    Vector<Elem>(element, dim),
    VectPoly<Elem>(element, dim),
    DynamicVector<Elem>(element, dim) {} //Ctr correspondants de classes parentes

template <typename Elem>
PolyDyn<Elem>::PolyDyn(const Elem* elemArray, std::size_t dim):
    Vector<Elem>(elemArray, dim),
    VectPoly<Elem>(elemArray, dim),
    DynamicVector<Elem>(elemArray, dim) {} //Ctr correspondants de classes parentes

/**de copie**/
template <typename Elem>
PolyDyn<Elem>::PolyDyn(const PolyDyn<Elem>& poly):
    Vector<Elem>(poly),
    VectPoly<Elem>(poly),
    DynamicVector<Elem>(poly) {} //Appelle ctrs. copie

/**de transfert**/
template <typename Elem>
PolyDyn<Elem>::PolyDyn(PolyDyn<Elem>&& poly):
    Vector<Elem>(std::forward<VectPoly<Elem>>(poly)),
    VectPoly<Elem>(std::forward<VectPoly<Elem>>(poly)),
    DynamicVector<Elem>(std::forward<VectPoly<Elem>>(poly)) {} //Appelle ctrs. transfert

/**de conversion**/
template <typename Elem>
PolyDyn<Elem>::PolyDyn(const VectPoly<Elem>& vect):
	Vector<Elem>(vect), VectPoly<Elem>(vect), DynamicVector<Elem>(vect) {} //Conversion: copie & evalue degre



/**--------------------OPERATEURS**/

/**assignation a vecteur**/
template <typename Elem>
PolyDyn<Elem>& PolyDyn<Elem>::operator=(const Vector<Elem>& vect)
{
    this->DynamicVector<Elem>::operator=(vect);//Appelle op. de copie de DynamicVector
    this->evalDeg(); //Met degre a jour
    return *this;
}
/**assignation a vecteur polynome**/
template <typename Elem>
PolyDyn<Elem>& PolyDyn<Elem>::operator=(const VectPoly<Elem>& poly)
{
    this->DynamicVector<Elem>::operator=(poly);//Appelle op. de copie de DynamicVector
    _deg = poly.deg();
    _degModified = false; //Degre mis a jour
	return *this;
}
/**assignation a vecteur dynamique**/
template <typename Elem>
PolyDyn<Elem>& PolyDyn<Elem>::operator=(const DynamicVector<Elem>& vect)
{
    this->DynamicVector<Elem>::operator=(vect);//Appelle op. de copie de DynamicVector
    this->evalDeg(); //Met degre a jour
    return *this;
}
/**assignation a polynome dynamique**/
template <typename Elem>
PolyDyn<Elem>& PolyDyn<Elem>::operator=(const PolyDyn<Elem>& poly)
{
    this->DynamicVector<Elem>::operator=(poly);//Appelle op. de copie de DynamicVector
    _deg = poly.deg();
    _degModified = false; //Degre mis a jour
    return *this;
}


/**transfert d'un vecteur**/
template <typename Elem>
PolyDyn<Elem>& PolyDyn<Elem>::operator=(Vector<Elem>&& vect)
{
    this->DynamicVector<Elem>::operator=(std::move(vect));//Appelle op. transfert de DynamicVector
    this->evalDeg(); //Met degre a jour
    return *this;
}
/**transfert d'un vecteur polynome**/
template <typename Elem>
PolyDyn<Elem>& PolyDyn<Elem>::operator=(VectPoly<Elem>&& poly)
{
    this->DynamicVector<Elem>::operator=(std::move(poly));//Appelle op. transfert de DynamicVector
    _deg = poly.deg();
    _degModified = false; //Degre mis a jour
	return *this;
}
/**transfert d'un vecteur dynamique**/
template <typename Elem>
PolyDyn<Elem>& PolyDyn<Elem>::operator=(DynamicVector<Elem>&& vect)
{
    this->DynamicVector<Elem>::operator=(std::move(vect));//Appelle op. transfert de DynamicVector
    this->evalDeg(); //Met degre a jour
    return *this;
}
/**transfert d'un polynome dynamique**/
template <typename Elem>
PolyDyn<Elem>& PolyDyn<Elem>::operator=(PolyDyn<Elem>&& poly)
{
	this->DynamicVector<Elem>::operator=(std::move(poly));//Appelle op. transfert de DynamicVector
	_deg = poly.deg();
	_degModified = false; //Degre mis a jour
	return *this;
}


/**op+= addition d'un Vector<Elem> (idem pour polynome)**/
template <typename Elem>
void PolyDyn<Elem>::operator+=(const Vector<Elem>& vect)
{
    this->DynamicVector<Elem>::operator+=(vect); //Appelle op. += de DynamicVector
    this->evalDeg(); //Reevalue degre
}

/**op-= soustraction d'un Vector<Elem> (idem pour polynome)**/
template <typename Elem>
void PolyDyn<Elem>::operator-=(const Vector<Elem>& vect)
{
    this->DynamicVector<Elem>::operator-=(vect); //Appelle op. += de DynamicVector
    this->evalDeg(); //Reevalue degre
}


/**op*= multiplication par polynome**/
template <typename Elem>
void PolyDyn<Elem>::operator*=(const VectPoly<Elem>& other)
{
	int otherDeg = other.deg();
	int thisDeg = this->deg();
	if (thisDeg==-1 or otherDeg==-1) //Resultat forcement nul
	{
		Elem* oldValues = _values;
		_values = new Elem[0];
		_dim = 0;
		_deg = -1;
		delete[] oldValues;
	}
	else							//Resultat variable:
	{
		if (otherDeg>0) 	//Il FAUT ajuster le degre de this, et on en profite pour ajuster sa dimension
		{
			Elem* oldValues = _values;
			_values = new Elem[thisDeg + otherDeg + 1]; //dimension resultante = degre resultant + 1

			//Calcul optimise: pas besoin d'initialiser (degres extremes parcourus une seule fois)!
			for (int j=0; j<=otherDeg; ++j) {_values[j] = oldValues[0] * other[j];} //parcourt premier coeff de this
			for (int i=1; i<=thisDeg; ++i) //chaque coeff. de this sauf le premier
			{
				for (int j=0; j<otherDeg; ++j) //chaque coeff de other sauf le dernier
				{
					_values[i+j] += oldValues[i] * other[j]; //ajoute leur produit au coeff. de la somme de leurs degres
				}
				_values[i+otherDeg] = oldValues[i] * other[otherDeg]; //parcourt dernier coeff de other
			}
			_degModified = false;	//Degre mis a jour
			_deg = thisDeg + otherDeg; //Nouveau degre
			_dim = _deg+1; //Nouvelle dim
			delete[] oldValues; //elimine anciens coeff.
		}
		else 				//Dans ce cas les modifications peuvent se faire "sur place"
		{
			for (int i=0; i<=_deg; ++i) { _values[i] *= other[0]; }
		}
    }
}


/**--------------------HORS CLASSE**/

/**addition binaire entre VectPoly<Elem>**/
template <typename Elem>
PolyDyn<Elem> operator+(const VectPoly<Elem>& polyA, const VectPoly<Elem>& polyB)
{
    PolyDyn<Elem> resPoly(polyA);//Copie de polyA comme polynome dynamique
    resPoly += polyB;
    return resPoly;
}

/**soustraction binaire entre VectPoly<Elem>**/
template <typename Elem>
PolyDyn<Elem> operator-(const VectPoly<Elem>& polyA, const VectPoly<Elem>& polyB)
{
    PolyDyn<Elem> resPoly(polyA); //Copie de polyA comme polynome dynamique
    resPoly -= polyB;
    return resPoly;
}

/**multiplication de VectPoly<Elem>**/
template <typename Elem>
PolyDyn<Elem> operator*(const VectPoly<Elem>& polyA, const VectPoly<Elem>& polyB)
{
    PolyDyn<Elem> resPoly = PolyDyn<Elem>(polyA); //Copie de polyA comme polynome dynamique
    resPoly *= polyB;
    return resPoly; //Retourne par valeur (effc++)
}

/**plus unaire**/
template <typename Elem>
PolyDyn<Elem> operator+(const PolyDyn<Elem>& poly)
{
    PolyDyn<Elem> newPoly(poly); //Ctr copie
    newPoly.unary_plus();
    return newPoly; //Retourne par valeur (effc++)
}

/**moins unaire**/
template <typename Elem>
PolyDyn<Elem> operator-(const PolyDyn<Elem>& poly)
{
    PolyDyn<Elem> newPoly(poly); //Ctr copie
    newPoly.unary_minus();
    return newPoly; //Retourne par valeur (effc++)
}


#endif // POLYDYN_H
