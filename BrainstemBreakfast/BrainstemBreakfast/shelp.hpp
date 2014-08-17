#pragma once
#include <sstream>
#include <iomanip>

namespace bsb
{
namespace shelp
{
	template <class _VT>
	inline std::string to_ss(const _VT value, const std::streamsize precision = 5)
	{
		std::stringstream stream;
		stream.precision(precision);
		stream << std::scientific << value;
		return stream.str();
	}

	template <class _VT>
	inline std::string to_sh(const _VT value)
	{
		char buff[10];
		_itoa_s(value, buff, 16);
		return buff;
	}

	template <class _VT>
	inline std::string to_sf(const _VT value, const std::streamsize precision = 5)
	{
		std::stringstream stream;
		stream.precision(precision);
		stream << std::fixed << value;
		return stream.str();
	}
}
}