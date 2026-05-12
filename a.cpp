#include "a.hpp"
#include <iostream>

void nspace::a::am() {
	std::cout << "method from class a " << b::bv << b::b1<< '\n';
}