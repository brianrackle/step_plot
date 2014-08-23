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

		ostream << table_header("ccccc", "Rainbow", "Transition1", "Transition2", "Transition3", "Transition4");
		for (int i = 0; i <= 100; ++i)
		{
			double v = (double)i / 100.0;
			auto make_cell = [](std::string clr)->std::string
			{return span(clr, color + "#ffffff", bg_color + clr); };

			ostream << table_row(
				make_cell(to_hex(gradient_value(v))),
				make_cell(to_hex(gradient_value(v, { 255, 0, 0 }, { 0, 0, 0 }))),
				make_cell(to_hex(gradient_value(v, { 255, 255, 255 }, { 0, 0, 0 }))),
				make_cell(to_hex(gradient_value(v, { 0, 0, 0 }, { 255, 255, 255 }))),
				make_cell(to_hex(gradient_value(v, { 42, 163, 90 }, { 207, 74, 33 }))));
		}
	}
}
}