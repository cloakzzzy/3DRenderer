#include "b.hpp"
#include <iostream>

void nspace::b::bm() {
	std::cout << "method from class b " <<a::av<< a::a1<<c::c1<<'\n';
}