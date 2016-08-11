#include <iostream>
#include "dynamicvector.hpp"
#include "staticvector.hpp"

int main() {
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
