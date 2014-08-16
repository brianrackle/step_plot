#pragma once
#include <limits>
#include <sstream>

namespace bsb
{
namespace range_map
{
	template <class T>
	class range
	{
	public:
		range(T l, T h) : low(l), high(h), ls(std::to_string(l)), hs(std::to_string(h)){}

		T low;
		T high;
		std::string ls;
		std::string hs;
	};

	template <class _VT>
	std::string to_ss(const _VT value, const std::streamsize precision = 7)
	{
		std::stringstream stream;
		stream.precision(precision);
		stream << std::scientific << value;
		return stream.str();
	}

	template <class _VT>
	std::string to_sh(const _VT value)
	{
		std::stringstream stream;
		stream << std::hex << value;
		return stream.str();
	}

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