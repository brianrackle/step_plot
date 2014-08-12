#pragma once
#include <regex>
#include <string>
#include <cstdlib>

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

		inline std::string uchar_to_hex(const unsigned char c)
		{
			char buff[10];
			_itoa_s(c, buff, 16);
			return buff;
		}

		enum class style_enum
		{
			background_color = 0,
			color
		};

		using style_type = std::pair < const style_enum, const std::string >;

		template<class ... Types>
		inline std::string span(const char * content, const style_type first_style, const Types ... rest_style)
		{
			return std::string(" <span ") +
				populate_style(create_style(), first_style, rest_style...) + ">" +
				content +
				"</span> ";
		}

		//converts rgb to hex
		//http://stackoverflow.com/questions/14375156/how-to-convert-a-rgb-color-value-to-an-hexadecimal-value-in-c
		inline std::string rgb_to_hex(const unsigned char r, const unsigned char g, const unsigned char b)
		{
			return "0x" + uchar_to_hex(r) + uchar_to_hex(g) + uchar_to_hex(b);
		}

		inline std::string create_style()
		{
			return "style=\"\"";
		}

		//populates style attribute (content) with styles
		template <class ... T>
		inline std::string populate_style(const char * content, const style_type first_style_t, const T ... rest_style_t)
		{
			populate_style(populate_style(content, first_style_t), rest_style_t...);
		}

		//populates style attribute (content) with styles
		inline std::string populate_style(const char * content, const style_type style_t)
		{
			std::regex regex("\"(.*?)\"");
			
			std::string style_text;
			switch (style_t.first)
			{
			case style_enum::background_color:
				style_text = "background_color:";
				break;
			case style_enum::color:
				style_text = "color:";
				break;
			default:
				break;
			}
			return std::regex_replace(content, regex, "$01" + style_text + style_t.second + ";");
		}
	}
}