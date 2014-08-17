#pragma once
#include <sstream>

namespace bsb
{
namespace shelp
{
	template <class _VT>
	std::string to_ss(const _VT value, const std::streamsize precision = 5)
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
}
}