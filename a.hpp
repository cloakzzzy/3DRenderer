#pragma once
#include <string>
#include "b.hpp"
#include "c.hpp"

namespace nspace {
	class a {
		inline static std::string a1 = "private member from class a ";
	public:
		friend class b;
		friend class c;

		inline static std::string av = "variable from class a ";
		


		void am();
	};


}
/*
#include <iostream>
#include <SDL3/SDL.h>
#include <SDL3/SDL_mouse.h>
#include <glew.h>
#include "Engine.hpp"

int main() {

	nspace::a A;
	A.am();

	nspace::b B;
	B.bm();

	nspace::c C;
	C.cm();

}
*/