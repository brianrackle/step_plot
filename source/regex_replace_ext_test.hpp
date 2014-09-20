#ifndef _t0236867e81948d8822283c3bbbe6a0f
#define _t0236867e81948d8822283c3bbbe6a0f
#include <map>
#include <iostream>
#include <vector>
#include <string>
#include <functional>
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
      
    using dictionary = std::map<std::string,std::string>;
 
    const std::vector<const dictionary> dict
      {
	{
	  {"{Id_1}","This"},
	  {"{Id_2}","test"},
	  {"{Id_3}","my"},
	  {"{Id_4}","favorite"},
	  {"{Id_5}","hotdog"}
	},
	{
	  {"[Fill_0]","is a"},
	  {"[Fill_1]","of"}
	}
      };
    
    auto fmt0 = [&dict](const unsigned smatch, const std::string & s)->std::string
      {
	return std::to_string(smatch);
      };

    auto fmt1 = [&dict](const unsigned smatch, const std::string & s)->std::string
      {
	auto dict_smatch = smatch - 1;
	if(dict_smatch > dict.size()-1)
	  return "fail";
  
        const auto it = dict[dict_smatch].find(s); 
	return it != dict[dict_smatch].cend() ? it->second : s;
      };
    
    auto fmt2 = [&dict](const std::string & s)->std::string
      {
	for(const auto & d : dict)
	  {
	    auto d_it = d.find(s);
	    if(d_it != d.end())
	      return d_it->second;
	  }
	  return s;
      };
    
    std::string test("Test");

    const std::string bss("{Id_1} [Fill_0] {Id_2} [Fill_1] {Id_3} {Id_4} {Id_5}.");
    const std::regex re("(\\{.*?\\})|(\\[.*?\\])");

    std::cout << bss << std::endl;
    std::cout << regex_replace_ext(bss, re, fmt0) << std::endl;
    std::cout << regex_replace_ext(bss, re, fmt1) << std::endl;
    std::cout << regex_replace_ext(bss, re, fmt2) << std::endl;
  }

}
}

#endif
