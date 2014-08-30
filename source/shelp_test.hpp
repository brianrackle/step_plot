#ifndef _a424e4e4f52c4bfdb489e30560afc439
#define _a424e4e4f52c4bfdb489e30560afc439

#include "shelp.hpp"
#include "markdown.hpp"

namespace bsb
{
namespace shelp
{
	template <class S>
	inline void test(S & ostream)
	{
		using namespace markdown;
		using namespace shelp;

		ostream << heading(2, "shelp");
		ostream << heading(4, __FILE__);

		ostream << table_header("lll", "fixed", "scientific", "hex")
			<< table_row(to_sf(255,5), to_ss(255,5), to_sh(255));
	}
}
}
#endif
