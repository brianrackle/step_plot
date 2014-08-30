#ifndef _0a479ea3eab34d7d94990938f9399c1a
#define  _0a479ea3eab34d7d94990938f9399c1a

#include "time_it.hpp"
#include "markdown.hpp"
#include <string>

namespace bsb
{
namespace time_it
{
	template <class S>
	inline void test(S & ostream)
	{
		using namespace markdown;
		ostream << heading(2, "time_it");
		ostream << heading(4, __FILE__);
		auto result = time_it < std::chrono::milliseconds >
			([]{ for (size_t i = 0; i < 1000 * 1000; ++i) std::pow(i, 2); });
		ostream << "milliseconds: " + std::to_string(result.count()) << "\n";
	}
}
}
#endif
