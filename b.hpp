#pragma once
#include <string>
#include "a.hpp"
#include "c.hpp"

namespace nspace {
	class b {
		friend class a;
		friend class c;
		static inline std::string b1 = "private member from class b ";
	public:
		static inline std::string bv = "variable from class b ";
		void bm();
	};
}
