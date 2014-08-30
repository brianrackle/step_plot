#ifndef _bcad905733e04e498c855289d46cff8a
#define _bcad905733e04e498c855289d46cff8a

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

	template <class _FT, class _TT,
	class = typename std::enable_if<std::is_arithmetic<_FT>::value>::type,
	class = typename std::enable_if<std::is_arithmetic<_TT>::value>::type>
	std::string row_results(const _FT value, const _FT r1_min, const _FT r1_max, const _TT r2_min, const _TT r2_max)
	{
		using namespace markdown;
		using namespace shelp;

		return table_row(to_ss(value), to_ss(r1_min), to_ss(r1_max), to_ss(r2_min), to_ss(r2_max),
			to_ss(scale_value(value, r1_min, r1_max, r2_min, r2_max)));
	}


	template <class S>
	inline void test(S & ostream)
	{
		using namespace markdown;

		ostream << heading(2, "range_map");
		ostream << heading(4, __FILE__);

		range<int> r0{ 300, 500 };
		range<int> r1{ std::numeric_limits<int>::lowest(), std::numeric_limits<int>::max() };
		range<long double> r2{ std::numeric_limits<long double>::lowest(), std::numeric_limits<long double>::max() };

		ostream << table_header("lrlrlr", "Value", "R1 Min", "R1 Max", "R2 Min", "R2 Max", "Return Value")
			<< row_results(r1.high, r1.low, r1.high, r2.low, r2.high)
			<< row_results(400, r0.low, r0.high, r1.low, r1.high)
			<< row_results(127, 0, 255, 0.0, 1.0);
	}
}
}
#endif
