#pragma once
#include <sstream>
#include <iomanip>
#include <type_traits>
namespace bsb
{
namespace shelp
{
	template <class _VT,
	class = typename std::enable_if<std::is_arithmetic<_VT>::value>::type>
	inline std::string to_ss(const _VT value, const std::streamsize precision = 5)
	{
		std::stringstream stream;
		stream.precision(precision);
		stream << std::scientific << value;
		return stream.str();
	}

	template <class _VT,
	class = typename std::enable_if<std::is_arithmetic<_VT>::value>::type>
	inline std::string to_sh(const _VT value)
	{
		std::stringstream stream;
		stream << std::hex << std::setfill('0') << std::setw(sizeof(_VT) * 2) << (long)value;
		std::string temp = stream.str();
		return stream.str();
	}

	template <class _VT,
	class = typename std::enable_if<std::is_arithmetic<_VT>::value>::type>
	inline std::string to_sf(const _VT value, const std::streamsize precision = 5)
	{
		std::stringstream stream;
		stream.precision(precision);
		stream << std::fixed << value;
		return stream.str();
	}

	template <class _VT>
	inline std::string to_str(const _VT value)
	{
		std::stringstream stream;
		stream << value;
		return stream.str();
	}
}
}