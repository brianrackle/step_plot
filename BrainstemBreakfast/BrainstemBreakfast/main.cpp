#include <fstream>
#include "Markdown.hpp"
int main()
{
	using namespace bsb::markdown;
	std::ofstream outfile("outfile.txt");
	outfile << table_header("llrr", "Word 1", "Word 2", "Word 3", "Word 4")
		<< table_row("hi", "how", "are", "you")
		<< table_row("I", "am", "fine", "thanks");
}