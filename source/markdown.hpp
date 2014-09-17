#ifndef _9f0413de588d4401bfccc883b6f81ad2
#define _9f0413de588d4401bfccc883b6f81ad2

#include <regex>
#include <string>
#include <cstdlib>
#include <type_traits>
#include <cstdint>
#include "shelp.hpp"
#include "gradient.hpp"

namespace bsb
{
namespace markdown
{
  //table_header recursion base case
  inline std::string table_header(const std::string format, const std::string name)
  {
    auto output = "| " + name + " |\n";
    
    for (const auto c : format)
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
    return output + " |" + "\n";
  }

  //create markdown table header
  template<class ... _RT>
  inline std::string table_header(const std::string format, const std::string first_name, const _RT ... rest_name)
  {
    return "| " + first_name + " " + table_header(format, rest_name...);
  }

  //table_row recursion base case
  inline std::string table_row(const std::string content)
  {
    return  "| " + content + "|\n";
  }

  //create markdown table row
  template <class ... _RT>
  inline std::string table_row(const std::string first_content, const _RT ... rest_content)
  {
    return "| " + first_content + " " + table_row(rest_content...);
  }


  //create markdown heading
  inline std::string heading(const uint8_t level, const std::string name)
  {
    std::string output;
    for (std::remove_const<decltype(level)>::type i = 0; i < level; ++i)
      output += "#";
    return "\n" + output + " " + name + "\n";
  }

  //create a markdown anchor link. To be paired with anchor
  inline std::string anchor_link(const std::string content, const std::string name)
  {
    return "[" + content + "](#" + name + ")\n";
  }

  //create a markdown paragraph
  inline std::string pgf(const std::string content)
  {
    return "\n\n" + content + "\n\n";
  }

  //create a markdown block quote
  inline std::string block_quote(const std::string content)
  {
    return "\n" + std::regex_replace("> " + content, std::regex("\n"), "$&> ") + "\n";
  }

  //make a full anchor tag that supports content
  //create an html anchor. To be paired with an anchor link
  inline std::string anchor(const std::string name)
  {
    return "<a name = \"" + name + "\"></a>\n";
  }

  //converts rgb to hex
  inline std::string to_hex(const gradient::rgb clr)
  {
    return "#" + shelp::to_sh(clr.r) + shelp::to_sh(clr.g) + shelp::to_sh(clr.b);
  }

  //creates an html style attribute
  inline std::string create_style()
  {
    return "style=\"\"";
  }

  //populate_style recursion base cas
  inline std::string populate_style(const std::string content, const std::string style)
  {
    return std::regex_replace(content, std::regex("\"(.*?)\""), "\"$01" + style + ";\"");
  }

  //populates an html style attribute (content) with styles
  template <class ... _RT>
  inline std::string populate_style(const std::string content, const std::string first_style, const _RT ... rest_style)
  {
    return populate_style(populate_style(content, first_style), rest_style...);
  }

  //creates an html span element and sets the style attribute
  inline std::string span(const std::string content, const std::string first_style)
  {
    return "<span " +
      populate_style(create_style(), first_style) + ">" +
      content +
      "</span>";
  }

  //creates an html span element and sets the style attributes
  template<class ... _RT>
  inline std::string span(const std::string content, const std::string first_style, const _RT ... rest_style)
  {
    return "<span " +
      populate_style(create_style(), first_style, rest_style...) + ">" +
      content +
      "</span>";
  }
		
}
}

#endif
