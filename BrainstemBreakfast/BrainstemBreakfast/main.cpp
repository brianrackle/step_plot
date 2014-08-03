#include <fstream>
#include "Markdown.hpp"
int main()
{
	using namespace bsb::markdown;
	std::vector<int> vec{ 1, 2, 3 };
	std::ofstream outfile("outfile.txt");
	outfile << table_header("llrr", "1", "2", "3", "4")
		<< table_row("hi", "how", "are", "you");
}