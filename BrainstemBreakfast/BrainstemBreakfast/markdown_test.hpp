#pragma once
#include <fstream>
#include "Markdown.hpp"

namespace bsb
{
	namespace markdown
	{
		template <class S>
		inline void test(S & stream)
		{
			stream << heading(2, "markdown");
			stream << heading(4, __FILE__);
			stream << table_header("llrr", "Word 1", "Word 2", "Word 3", "Word 4")
				<< table_row("hi", "how", "are", "you")
				<< table_row("I", "am", "fine", "thanks");
		}
	}
}
