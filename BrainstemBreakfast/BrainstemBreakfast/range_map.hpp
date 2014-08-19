#pragma once
#include <limits>
#include <type_traits>

namespace bsb
{
namespace range_map
{
	//scales 'value' from the range 'lowestFrom'/'highestFrom' to the range 'lowestTo'/'highestTo'
	template <class _FT, class _TT,
	class = typename std::enable_if<std::is_arithmetic<_FT>::value>::type,
	class = typename std::enable_if<std::is_arithmetic<_TT>::value>::type>
	_TT scale_value(_FT value, _FT lowestFrom, _FT highestFrom, _TT lowestTo, _TT highestTo)
	{
		//scale by half to account for negative and positive range being too large to represent
		const auto && fHLF = [](_FT v){ return v / 2; };
		const auto && tHLF = [](_TT v){ return v / 2; };

		auto scaledOffsetResult =
			(tHLF(highestTo) - tHLF(lowestTo)) * 
			((fHLF(value) - fHLF(lowestFrom)) / (fHLF(highestFrom) - fHLF(lowestFrom)));

		return (_TT)(scaledOffsetResult + lowestTo + scaledOffsetResult); //seperated to prevent overflow
	}
}
}