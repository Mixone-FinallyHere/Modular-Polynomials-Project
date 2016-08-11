#include <iostream>
#include "polynomialvector.hpp"
#include "modularpolynomial.hpp"

// Miguel Terol Espino
// 000356914
// mteroles@ulb.ac.be

extern const Polynomial<int> diviseur(3, 6);

int main() {

	Polynomial<int> poly(2, 7);

	ModularPolynomial<int, 2, diviseur> test(2);

	std::cout << poly << std::endl;

	std::cin >> poly;

	std::cout << poly << std::endl;

	std::cout << test << std::endl;

    StaticVector< int, 6 > staticVector;
    StaticVector<int, 6> statV;

    std::cin >> statV;

	staticVector[0] = 3;
	staticVector[2] = 6;
	staticVector[5] = 2;
	std::cout << staticVector << std::endl;

	staticVector += statV;
	std::cout << staticVector << std::endl;

	DynamicVector< int > dynamicVector( 6 );

	std::cin >> dynamicVector;

	dynamicVector[0] = 3;
	dynamicVector[2] = 6;
	dynamicVector[5] = 2;
	std::cout << dynamicVector << std::endl;

	dynamicVector.setSize( 2 );
	std::cout << dynamicVector << std::endl;

	dynamicVector.setSize( 7 );
	std::cout << dynamicVector << std::endl;


	StaticVector< int, 6 > st10( staticVector );



	return 0;
}
