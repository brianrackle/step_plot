#ifndef _t0236867e81948d8822283c3bbbe6a0f
#define _t0236867e81948d8822283c3bbbe6a0f
#include <map>
#include <iostream>
#include "regex_replace_ext.hpp"
#include "markdown.hpp"

namespace bsb
{
namespace regex_ext
{

  template <class S>
  inline void test(S & ostream)
  {
    using namespace markdown;
    
    ostream << heading(2, "regex");
    ostream << heading(4, __FILE__);

    auto fmt = [](const std::string & s)->std::string
      { 
	const std::map<std::string,std::string> def
	{
	  {"{Id_1}","This"},
	  {"{Id_2}","test"},
	  {"{Id_3}","Obama's"},
	  {"{Id_4}","favorite"},
	  {"{Id_5}","hotdog"}
	};
	const auto it = def.find(s); 
	return it != def.cend() ? it->second : s;
      };

    std::string test("Test");

    const std::string bss("{Id_1} is a {Id_2} of {Id_3} {Id_4} {Id_5}.");
    const std::regex re("(\\{.*?\\})");
    auto result = regex_replace_ext(bss, re, fmt);
    
    std::cout << result << std::endl;
  }

}
}

#endif
