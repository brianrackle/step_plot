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
		range<long double> r3{ std::numeric_limits<long double>::lowest(), std::numeric_limits<long double>::max() };
		ostream << table_header("lrlrrr", "Value", "R1 Min", "R1 Max", "R2 Min", "R2 Max", "Return Value")
			<< table_row(to_ss(400), to_ss(r0.low), to_ss(r0.high), to_ss(r1.low), to_ss(r1.high), to_ss(scale_value(400, r0.low, r0.high, r1.low, r1.high)))
			<< table_row(to_ss(r2.high), to_ss(r2.low), to_ss(r2.high), to_ss(r3.low), to_ss(r3.high), to_ss(scale_value(r2.high, r2.low, r2.high, r3.low, r3.high)))
			<< table_row(to_ss(400), to_ss(r0.low), to_ss(r0.high), to_ss(r2.low), to_ss(r2.high), to_ss(scale_value(400, r0.low, r0.high, r2.low, r2.high)));
	}
}
}
