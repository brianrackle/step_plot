#include <fstream>
#include "markdown_test.hpp"
#include "time_it_test.hpp"


int main()
{
	std::ofstream outfile("test.md");
	bsb::markdown::test(outfile);
	bsb::time_it::test(outfile);
}