#pragma once
#include "time_it.hpp"
#include "markdown.hpp"
#include <string>

namespace bsb
{
	namespace time_it
	{
		template <class S>
		inline void test(S & ostream)
		{
			using namespace markdown;
			ostream << heading(2, "time_it");
			ostream << heading(4, __FILE__);
			auto result = time_it < std::chrono::milliseconds >
				([]{ for (size_t i = 0; i < 100000 * 1000; ++i) std::pow(i, 2); });
			ostream << "milliseconds: " + std::to_string(result.count());
		}
	}
}