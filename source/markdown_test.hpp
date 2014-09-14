#ifndef _53ed167418c3493a9815f316bbdf8ce9
#define _53ed167418c3493a9815f316bbdf8ce9

#include <fstream>
#include "markdown.hpp"

namespace bsb
{
namespace markdown
{

  template <class S>
  inline void test(S & ostream)
  {
    ostream << heading(2, "markdown");
    ostream << heading(4, __FILE__);
    ostream << table_header("llrr", "Word 1", "Word 2", "Word 3", "Word 4")
	    << table_row("hi", "how", "are", "you")
	    << table_row("I", "am", "fine",
			 span("thanks", "background-color:" + to_hex({ 0, 0, 0 }), "color:" + to_hex({ 255, 255, 255 })));
  }

}
}

#endif
