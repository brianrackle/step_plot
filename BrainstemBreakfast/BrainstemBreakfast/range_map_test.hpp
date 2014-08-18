#pragma once
#include "range_map.hpp"
#include "markdown.hpp"
#include "shelp.hpp"

namespace bsb
{
namespace range_map
{
	template <class T>
	class range
	{
	public:
		range(T l, T h) : low(l), high(h){}

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

		range<int> r0(-100, 0);
		range<int> r1(100, 200);

		range<int> r2(std::numeric_limits<int>::lowest(), std::numeric_limits<int>::max());
		range<double> r3(std::numeric_limits<double>::lowest(), std::numeric_limits<double>::max());
		ostream << table_header("lrlrrr", "R1 Min", "R1 Max", "R2 Min", "R2 Max", "Value", "Scaled Value")
			<< table_row(to_ss(r0.low), to_ss(r0.high), to_ss(r1.low), to_ss(r1.high), to_ss(-100), to_ss(scale_value(-100, r0.low, r0.high, r1.low, r1.high)))
			<< table_row(to_ss(r2.low), to_ss(r2.high), to_ss(r3.low), to_ss(r3.high), to_ss(r2.high), to_ss(scale_value(r2.high, r2.low, r2.high, r3.low, r3.high)))
			<< table_row(to_ss(r3.low), to_ss(r3.high), to_ss(r2.low), to_ss(r2.high), to_ss(r3.high), to_ss(scale_value(r3.high, r3.low, r3.high, r2.low, r2.high)));
	}
}
}
