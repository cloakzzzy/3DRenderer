#include "c.hpp"
#include <iostream>

void nspace::c::cm() {
	std::cout << "method from class c " << c::cv << a::a1 << b::b1<<  '\n';
}
