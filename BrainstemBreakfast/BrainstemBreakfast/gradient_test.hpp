#pragma once
#include "gradient.hpp"
#include "markdown.hpp"
#include "shelp.hpp"
#include "range_map.hpp"

namespace bsb
{
namespace gradient
{
	std::string make_cell(std::string clr)
	{
		return markdown::span(clr, markdown::color + "#ffffff", markdown::bg_color + clr);
	}

	std::string hex_grad(const double_t v, const rgb t, const rgb f)
	{
		return markdown::to_hex(gradient_value(v, t, f));
	};

	std::string gradient_string(std::string str, const rgb from_color, const rgb to_color)
	{
		std::string result;
		auto size = str.size();
		using str_t = decltype(str.size());
		for (str_t i = 0; i < str.size(); ++i)
		{
			auto v = range_map::scale_value(i, str_t(0), str.size(), 0.0, 1.0);
			result += markdown::span(shelp::to_str(str[i]), markdown::color +
				hex_grad(v, from_color, to_color));
		}
		return result;
	};

	std::string hex_grad(const double_t v)
	{
		return markdown::to_hex(gradient_value(v));
	};

	std::string gradient_string(std::string str)
	{
		std::string result;
		auto size = str.size();
		using str_t = decltype(str.size());
		for (str_t i = 0; i < str.size(); ++i)
		{
			auto v = range_map::scale_value(i, str_t(0), str.size(), 0.0, 1.0);
			result += markdown::span(shelp::to_str(str[i]), markdown::color +
				hex_grad(v));
		}
		return result;
	};

	template <class S>
	inline void test(S & ostream)
	{
		using namespace markdown;

		ostream << heading(2, "gradient");
		ostream << heading(4, __FILE__);

		ostream << table_header("ccccc", "Rainbow", "Transition1", "Transition2", "Transition3", "Transition4");
		for (int i = 0; i <= 10; ++i)
		{
			double_t v = (double_t)i / 10.0;

			ostream << table_row(
				make_cell(to_hex(gradient_value(v))),
				make_cell(hex_grad(v, { 255, 0, 0 }, { 0, 0, 0 })),
				make_cell(hex_grad(v, { 255, 255, 255 }, { 0, 0, 0 })),
				make_cell(hex_grad(v, { 0, 0, 0 }, { 255, 255, 255 })),
				make_cell(hex_grad(v, { 42, 163, 90 }, { 207, 74, 33 })));
		}

		ostream << pgf(gradient_string(std::string("This is a test of 'gradient_string'. Each character in the string is given a unique value in the gradient."), { 42, 163, 90 }, { 207, 74, 33 }));
		ostream << gradient_string(std::string("This is a test of 'gradient_string'. Each character in the string is given a unique value in the gradient."));
	}
}
}