#pragma once
#include "gradient.hpp"
#include "markdown.hpp"

namespace bsb
{
namespace gradient
{
	template <class S>
	inline void test(S & ostream)
	{
		using namespace markdown;

		ostream << heading(2, "gradient");
		ostream << heading(4, __FILE__);
		for (int i = 0; i < 10; ++i)
		{
			double v = (double)i / 10.0;
			rgb clr = gradient_value(v);
			ostream << span("value", bg_color + rgb_to_hex(clr.r, clr.g, clr.b)) << "\n";
		}
	}
}
}