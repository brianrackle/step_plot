#pragma once
#include <regex>
#include <string>

namespace bsb
{
	namespace markdown
	{
		//create markdown table header
		template<class ... Types>
		inline std::string table_header(const char * format, const char  * first_name, const Types ... rest_name)
		{
			return std::string("| ") + first_name + " " + table_header(format, rest_name...);
		}

		//table_header recursion base case
		inline std::string table_header(const char * format, const char  * name)
		{
			std::string output = std::string("| ") + name + "|\n";

			for (char const* pos = format; *pos; ++pos)
				switch (*pos)
			{
				case 'l':
					output += "|:--- ";
					break;
				case 'r':
					output += "| ---:";
					break;
				case 'c':
					output += "|:---:";
					break;
				default:
					break;
			}
			return output + "|" + "\n";
		}

		//create markdown table row
		template <class ... Types>
		inline std::string table_row(const char * first_content, const Types  ... rest_content)
		{
			return std::string("| ") + first_content + " " + table_row(rest_content...);
		}

		//table_row recursion base case
		inline std::string table_row(const char * content)
		{
			return  std::string("| ") + content + "|\n";
		}

		//create markdown heading
		inline std::string heading(const unsigned char level, const char * name)
		{
			std::string output;
			for (std::remove_const_t<decltype(level)> i = 0; i < level; ++i)
				output += "#";
			return output + " " + name + "\n";
		}

		//create an html anchor. To be paired with an anchor link
		inline std::string anchor(const char * name)
		{
			return std::string("<a name = \"") + name + "\"></a>\n";
		}

		//create a markdown anchor link. To be paired with anchor
		inline std::string anchor_link(const char * content, const char * name)
		{
			return std::string("[") + content + "](#" + name + ")\n";
		}

		//create a markdown paragraph
		inline std::string pgf(const char * content)
		{
			return std::string("\n\n") + content + "\n\n";
		}

		//create a markdown block quote
		inline std::string block_quote(const char * content)
		{
			std::regex regex("\n");
			return "\n" + std::regex_replace(std::string("> ") + content, regex, "$&> ") + "\n";
		}

		template<class ... Types>
		inline std::string span(const char * content, const char * first_style, Types ... rest_style)
		{

		}

		inline std::string span(const char * content, const char * first_style)
		{
			//how to make this append styles on way down... append content on close on return..
			std::string span = "<span style=\"";

		}

		//or pass color as a long like in link?
		//converts rgb to hex
		//http://stackoverflow.com/questions/14375156/how-to-convert-a-rgb-color-value-to-an-hexadecimal-value-in-c
		inline std::string rgb_to_hex(const unsigned char r, const unsigned char g, const unsigned char b)
		{

		}

		inline std::string background_color_style()
		{

		}

		inline std::string color_style()
		{
			return "color:"
		}

	}
}