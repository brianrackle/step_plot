#pragma once
#include <limits>

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

	template <class _fT, class _tT>
	_tT scale_value(_fT value, _fT lowestFrom, _fT highestFrom, _tT lowestTo, _tT highestTo)
	{
		if (value == lowestFrom) return lowestTo;		
		if (value == highestFrom) return highestTo;

		//scale by half to account for negative and positive range being too large to represent
		const auto && fHLF = [](_fT v){ return v / 2; };
		const auto && tHLF = [](_tT v){ return v / 2; };

		auto scaledOffsetResult =
			((tHLF(highestTo) - tHLF(lowestTo)) * 
			((fHLF(value) - fHLF(lowestFrom)) / (fHLF(highestFrom) - fHLF(lowestFrom))));

		return (_tT)(scaledOffsetResult + lowestTo + scaledOffsetResult); //seperated to prevent overflow
	}
}
}