#include <fstream>
#include "markdown_test.hpp"
#include "time_it_test.hpp"
#include "range_map_test.hpp"
#include "shelp_test.hpp"
#include "gradient_test.hpp"
#include "regex_replace_ext_test.hpp"

int main()
{
	std::ofstream outfile("test.md");

	bsb::markdown::test(outfile);
	bsb::time_it::test(outfile);
	bsb::range_map::test(outfile);
	bsb::shelp::test(outfile);
	bsb::gradient::test(outfile);
	bsb::regex_ext::test(outfile);
}
