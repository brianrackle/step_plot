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

		ostream << table_header("cc", "Rainbow", "Transition");
		rgb color0{ 255, 0, 0 };
		rgb color1{ 0, 0, 0};
		for (int i = 0; i <= 100; ++i)
		{
			double v = (double)i / 100.0;
			auto make_cell = [](std::string clr)->std::string
			{return span(clr, color + "#ffffff", bg_color + clr); };

			ostream << table_row(
				make_cell(to_hex(gradient_value(v))),
				make_cell(to_hex(gradient_value(v, color0, color1))));
		}
	}
}
}