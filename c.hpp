#pragma once
#include <string>
#include "a.hpp"
#include "b.hpp"

namespace nspace {
	class c {
		friend class a;
		friend class b;
		inline static std::string c1 = "private member from class c ";
	public:
		inline static std::string cv = "variable from class c ";

		void cm();
	};
}