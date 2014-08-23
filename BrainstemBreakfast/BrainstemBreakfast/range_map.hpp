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
	_TT scale_value(const _FT value, const _FT lowestFrom, const _FT highestFrom, const _TT lowestTo, const _TT highestTo)
	{
		if (value <= lowestFrom)
			return lowestTo;
		if (value >= highestFrom)
			return highestTo;

		//scale by half to account for negative and positive range being too large to represent
		const auto && fHLF = [](_FT v){ return v / 2; };
		const auto && tHLF = [](_TT v){ return v / 2; };

		auto scaledOffsetResult =
			(tHLF(highestTo) - tHLF(lowestTo)) * 
			((fHLF(value) - fHLF(lowestFrom)) / (fHLF(highestFrom) - fHLF(lowestFrom)));

		return (_TT)(scaledOffsetResult + lowestTo + scaledOffsetResult); //seperated to prevent overflow
	}

	//scales 'value' from the range 0.0/1.0 to the range 'lowestTo'/'highestTo'
	template <class _TT,
	class = typename std::enable_if<std::is_arithmetic<_TT>::value>::type>
		_TT scale_value(const double_t value, const _TT lowestTo, const _TT highestTo)
	{
		if (value <= 0.0)
			return lowestTo;
		if (value >= 1.0)
			return highestTo;

		//scale by half to account for negative and positive range being too large to represent
		const auto && tHLF = [](_TT v){ return v / 2; };

		auto scaledOffsetResult = (tHLF(highestTo) - tHLF(lowestTo)) * value;
		return (_TT)(scaledOffsetResult + lowestTo + scaledOffsetResult); //seperated to prevent overflow
	}
}
}