#pragma once
#include "range_map.hpp"
#include "markdown.hpp"
#include "shelp.hpp"

namespace bsb
{
namespace range_map
{
	template <class T>
	struct range
	{
		T low;
		T high;
	};

	template <class S>
	inline void test(S & ostream)
	{
		using namespace markdown;
		using namespace shelp;

		ostream << heading(2, "range_map");
		ostream << heading(4, __FILE__);

		range<int> r0{ 300, 500 };
		range<int> r1{ 0, 1 };

		range<int> r2{ std::numeric_limits<int>::lowest(), std::numeric_limits<int>::max() };
		range<double> r3{ std::numeric_limits<double>::lowest(), std::numeric_limits<double>::max() };

		//breaking visual studio 14 CTP3
		auto row_results = [](auto value, auto r1_min, auto r1_max, auto r2_min, auto r2_max)->std::string
		{
			return table_row(to_ss(value), to_ss(r1_min), to_ss(r1_max), to_ss(r2_min), to_ss(r2_max),
				to_ss(scale_value(value, r1_min, r1_max, r2_min, r2_max)));
		};

		ostream << table_header("llrlrr", "Value", "R1 Min", "R1 Max", "R2 Min", "R2 Max", "Return Value")
			<< row_results(400, r0.low, r0.high, r1.low, r1.high);
			//<< row_results(r2.high, r2.low, r2.high, r3.low, r3.high)
			//<< row_results(400, r0.low, r0.high, r2.low, r2.high)
			//<< row_results(127, 0, 255, 0.0, 1.0);
	}
}
}
