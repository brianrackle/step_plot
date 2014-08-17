#pragma once
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

		double value = 123.456789;
		ostream << table_header("lll", "fixed", "scientific", "hex")
			<< table_row(to_sf(255), to_ss(255), to_sh(255));
	}
}
}