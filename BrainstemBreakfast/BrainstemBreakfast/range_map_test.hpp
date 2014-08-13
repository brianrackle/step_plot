#pragma once
#include "range_map.hpp"
#include "markdown.hpp"

namespace bsb
{
	namespace range_map
	{
		template <class S>
		inline void test(S & ostream)
		{
			std::pair<int, int> range0(-100, 0);
			std::pair<long, long> range1(100, 200);

			std::pair<int, int> range3(std::numeric_limits<int>::lowest(), std::numeric_limits<int>::max());
			std::pair<double, double> range4(std::numeric_limits<double>::lowest(), std::numeric_limits<double>::max());

			//markdown table
			using namespace markdown;
			table_header("lrlrrr", "R1 Min", "R1 Max", "R2 Min", "R2 Max", "Value", "Scaled Value");
			ostream << "Value: " -100 scale_value(-100, range0.first, range0.second, range1.first, range1.second);
		}
	}
}
