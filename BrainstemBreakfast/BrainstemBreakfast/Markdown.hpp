#pragma once
#include <regex>
#include <string>
#include <cstdlib>
#include <type_traits>
#include <cstdint>
#include "shelp.hpp"

namespace bsb
{
namespace markdown
{
#pragma region Markdown

	//create markdown table header
	template<class _FT, class _NT, class ... _RT>
	inline std::string table_header(const _FT format, const _NT first_name, const _RT ... rest_name)
	{
		static_assert(std::is_constructible<std::string, _FT>::value, "format type '_FT' must be a string constructor parameter");
		static_assert(std::is_constructible<std::string, _NT>::value, "format type '_NT' must be a string constructor parameter");
		//if string type _FT::value_type t;
		//prevent template types from being different value_types

		return std::string("| ") + first_name + " " + table_header(format, rest_name...);
	}

	//table_header recursion base case
	template<class _FT, class _NT>
	inline std::string table_header(const _FT format, const _NT name)
	{
		static_assert(std::is_constructible<std::string, _FT>::value, "format type '_FT' must be a string constructor parameter");
		static_assert(std::is_constructible<std::string, _NT>::value, "format type '_NT' must be a string constructor parameter");

		std::string output = std::string("| ") + name + "|\n";

		for (const auto c : std::string(format))
		{
			switch (c)
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
		}
		return output + "|" + "\n";
	}

	//create markdown table row
	template <class _CT, class ... _RT>
	inline std::string table_row(const _CT first_content, const _RT ... rest_content)
	{
		static_assert(std::is_constructible<std::string, _CT>::value, "format type '_CT' must be a string constructor parameter");

		return std::string("| ") + first_content + " " + table_row(rest_content...);
	}

	//table_row recursion base case
	template <class _CT>
	inline std::string table_row(const _CT content)
	{
		static_assert(std::is_constructible<std::string, _CT>::value, "format type '_CT' must be a string constructor parameter");

		return  std::string("| ") + content + "|\n";
	}

	//create markdown heading
	template <class _NT>
	inline std::string heading(const uint8_t level, const _NT name)
	{
		static_assert(std::is_constructible<std::string, _NT>::value, "format type '_NT' must be a string constructor parameter");

		std::string output;
		for (std::remove_const_t<decltype(level)> i = 0; i < level; ++i)
			output += "#";
		return output + " " + name + "\n";
	}

	//create a markdown anchor link. To be paired with anchor
	template <class _CT, class _NT>
	inline std::string anchor_link(const _CT content, const _NT name)
	{
		static_assert(std::is_constructible<std::string, _CT>::value, "format type '_CT' must be a string constructor parameter");
		static_assert(std::is_constructible<std::string, _NT>::value, "format type '_NT' must be a string constructor parameter");

		return std::string("[") + content + "](#" + name + ")\n";
	}

	//create a markdown paragraph
	template <class _CT>
	inline std::string pgf(const _CT content)
	{
		static_assert(std::is_constructible<std::string, _CT>::value, "format type '_CT' must be a string constructor parameter");

		return std::string("\n\n") + content + "\n\n";
	}

	//create a markdown block quote
	template <class _CT>
	inline std::string block_quote(const _CT content)
	{
		static_assert(std::is_constructible<std::string, _CT>::value, "format type '_CT' must be a string constructor parameter");

		return "\n" + std::regex_replace(std::string("> ") + content, std::regex("\n"), "$&> ") + "\n";
	}
#pragma endregion
#pragma region HTML
	//make a full anchor tag that supports content
	//create an html anchor. To be paired with an anchor link
	template <class _NT>
	inline std::string anchor(const _NT name)
	{
		static_assert(std::is_constructible<std::string, _NT>::value, "format type '_NT' must be a string constructor parameter");

		return std::string("<a name = \"") + name + "\"></a>\n";
	}

	static std::string bg_color("background-color:");
	static std::string color("color:");

	//converts rgb to hex
	inline std::string rgb_to_hex(const uint8_t r, const uint8_t g, const uint8_t b)
	{
		return "#" + shelp::to_sh(r) + shelp::to_sh(g) + shelp::to_sh(b);
	}

	//creates an html style attribute
	inline std::string create_style()
	{
		return "style=\"\"";
	}

	//populates an html style attribute (content) with styles
	template <class _CT, class _ST, class ... _RT>
	inline std::string populate_style(const _CT content, const _ST first_style, const _RT ... rest_style)
	{
		static_assert(std::is_constructible<std::string, _CT>::value, "format type '_CT' must be a string constructor parameter");
		static_assert(std::is_constructible<std::string, _ST>::value, "format type '_ST' must be a string constructor parameter");

		return populate_style(populate_style(content, first_style).c_str(), rest_style...);
	}

	//populate_style recursion base cas
	template <class _CT, class _ST>
	inline std::string populate_style(const _CT content, const _ST style)
	{
		static_assert(std::is_constructible<std::string, _CT>::value, "format type '_CT' must be a string constructor parameter");
		static_assert(std::is_constructible<std::string, _ST>::value, "format type '_ST' must be a string constructor parameter");

		return std::regex_replace(content, std::regex("\"(.*?)\""), std::string("\"$01") + style + ";\"");
	}

	//creates an html span element and sets the style attributes
	template<class _CT, class _ST, class ... _RT>
	inline std::string span(const _CT content, const _ST first_style, const _RT ... rest_style)
	{
		static_assert(std::is_constructible<std::string, _CT>::value, "format type '_CT' must be a string constructor parameter");
		static_assert(std::is_constructible<std::string, _ST>::value, "format type '_ST' must be a string constructor parameter");

		return "<span " +
			populate_style(create_style().c_str(), first_style, rest_style...) + ">" +
			content +
			"</span> ";
	}
		
	//creates an html span element and sets the style attribute
	template<class _CT, class _ST>
	inline std::string span(const _CT content, const _ST first_style)
	{
		static_assert(std::is_constructible<std::string, _CT>::value, "format type '_CT' must be a string constructor parameter");
		static_assert(std::is_constructible<std::string, _ST>::value, "format type '_ST' must be a string constructor parameter");

		return " <span " +
			populate_style(create_style().c_str(), first_style) + ">" +
			content +
			"</span> ";
	}
#pragma endregion
}
}