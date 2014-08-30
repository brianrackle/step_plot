#ifndef _6156744030884cb98e7ce1f37dbe0ed6
#define _6156744030884cb98e7ce1f37dbe0ed6

#include <sstream>
#include <iomanip>
#include <type_traits>
namespace bsb
{
namespace shelp
{
  const int DEFAULT_PRECISION = 5;

  //creates a string using scientific notation
  template <class _VT,
	    class = typename std::enable_if<std::is_arithmetic<_VT>::value>::type>
  inline std::string to_ss(const _VT value, const std::streamsize precision)
  {
    std::stringstream stream;
    stream.precision(precision);
    stream << std::scientific << value;
    return stream.str();
  }

  //creates a string using scientific notation
  template <class _VT,
	    class = typename std::enable_if<std::is_arithmetic<_VT>::value>::type>
  inline std::string to_ss(const _VT value)
  {
    return to_ss(value, DEFAULT_PRECISION);
  }

  //creates a string using hex notation
  template <class _VT,
	    class = typename std::enable_if<std::is_arithmetic<_VT>::value>::type>
  inline std::string to_sh(const _VT value)
  {
    std::stringstream stream;
    stream << std::hex << std::setfill('0') << std::setw(sizeof(_VT) * 2) << (long)value;
    std::string temp = stream.str();
    return stream.str();
  }

  //creates a string using fixed notation
  template <class _VT,
	    class = typename std::enable_if<std::is_arithmetic<_VT>::value>::type>
  inline std::string to_sf(const _VT value, const std::streamsize precision)
  {
    std::stringstream stream;
    stream.precision(precision);
    stream << std::fixed << value;
    return stream.str();
  }

  //creates a string using fixed notation
  template <class _VT,
	    class = typename std::enable_if<std::is_arithmetic<_VT>::value>::type>
  inline std::string to_sf(const _VT value)
  {
    return to_sf(value, DEFAULT_PRECISION);
  }

  //creates a string from value
  template <class _VT>
  inline std::string to_str(const _VT value)
  {
    std::stringstream stream;
    stream << value;
    return stream.str();
  }
}
}
#endif
