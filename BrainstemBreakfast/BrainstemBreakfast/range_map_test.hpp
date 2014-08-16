#pragma once
#include "range_map.hpp"
#include "markdown.hpp"

namespace bsb
{
namespace range_map
{
	template <class T>
	class range
	{
	public:
		range(T l, T h) : low(l), high(h), ls(std::to_string(l)), hs(std::to_string(h)){}

		T low;
		T high;
		std::string ls;
		std::string hs;
	};

	template <class S>
	inline void test(S & ostream)
	{
		range<int> r0(-100, 0);
		range<int> r1(100, 200);

		range<int> r2(std::numeric_limits<int>::lowest(), std::numeric_limits<int>::max());
		range<double> r3(std::numeric_limits<double>::lowest(), std::numeric_limits<double>::max());

		//markdown table
		using namespace markdown;
		ostream << table_header("lrlrrr", "R1 Min", "R1 Max", "R2 Min", "R2 Max", "Value", "Scaled Value")
			<< table_row(r0.ls, r0.hs, r1.ls, r1.hs, std::to_string(-100), std::to_string(scale_value(-100, r0.low, r0.high, r1.low, r1.high)))
			<< table_row(r2.ls, r2.hs, r3.ls, r3.hs, r2.hs, std::to_string(scale_value(r2.high, r2.low, r2.high, r3.low, r3.high)))
			<< table_row(r3.ls, r3.hs, r2.ls, r2.hs, r3.hs, std::to_string(scale_value(r3.high, r3.low, r3.high, r2.low, r2.high)));
	}
}
}
