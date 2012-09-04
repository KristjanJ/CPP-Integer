#include <iostream>
#include <cstdlib>
#include "Integer.h"

int main()
{
	Integer integer1("222222222222222222222222222222222222222222222222222222222222222222200");
	Integer integer2("444444444444444444444444444444444444444444444444444444444444444444444");
	
	Integer integer3 = (integer1 += Integer("22")) * integer2;

	std::cout << "integer1: " << integer1.toString() << std::endl << std::endl;
	std::cout << "integer2: " << integer2.toString() << std::endl << std::endl;
	std::cout << "integer3 (integer1 * integer2): " << integer3.toString() << std::endl << std::endl;

	std::cin.sync();
	std::cin.get();
	return EXIT_SUCCESS;
}