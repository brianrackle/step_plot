#pragma once
#include "time_it.hpp"
#include "markdown.hpp"
#include <string>

namespace bsb
{
	namespace time_it
	{
		template <class S>
		inline void test(S & stream)
		{
			using namespace markdown;
			stream << heading(2, "time_it");
			stream << heading(4, __FILE__);
			auto result = time_it < std::chrono::milliseconds >
				([]{ for (size_t i = 0; i < 100000 * 1000; ++i) std::pow(i, 2); });
			stream << "milliseconds: " + std::to_string(result.count());
		}
	}
}