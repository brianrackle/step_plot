#ifndef _c9b3775782f94483965d7b3ca0224896 
#define _c9b3775782f94483965d7b3ca0224896 

#include <cmath>
#include <limits>
#include <cstdint>
#include "range_map.hpp"

namespace bsb
{
namespace gradient
{
	struct rgb
	{
		using value_type = uint8_t;
		value_type r, g, b;
	};

	//rainbow gradient
	inline rgb gradient_value(const long double value)
	{
		const uint8_t regions = 6;
		auto max_rgb = std::numeric_limits<rgb::value_type>::max();
		long double region;
		auto subregion_value = (rgb::value_type)(std::modf(value * regions, &region) * max_rgb);
		auto region_value = (rgb::value_type)region % 6; 

		rgb gradient{ 0, 0, 0 };
		switch (region_value)
		{
		case 0:
			gradient.r = max_rgb;
			gradient.g = subregion_value;
			gradient.b = 0;
			break;
		case 1:
			gradient.r = max_rgb - subregion_value;
			gradient.g = max_rgb;
			gradient.b = 0;
			break;
		case 2:
			gradient.r = 0;
			gradient.g = max_rgb;
			gradient.b = subregion_value;
			break;
		case 3:
			gradient.r = 0;
			gradient.g = max_rgb - subregion_value;
			gradient.b = max_rgb;
			break;
		case 4:
			gradient.r = subregion_value;
			gradient.g = 0;
			gradient.b = max_rgb;
			break;
		case 5:
			gradient.r = max_rgb;
			gradient.g = 0;
			gradient.b = max_rgb - subregion_value;
			break;
		};
		
		return gradient;
	}

	//gradient between two colors
	inline rgb gradient_value(const long double value, const rgb & from_color, const rgb & to_color)
	{
		using namespace range_map;
		return {
			scale_value(value, from_color.r, to_color.r),
			scale_value(value, from_color.g, to_color.g),
			scale_value(value, from_color.b, to_color.b) };
	}
}
}

#endif
