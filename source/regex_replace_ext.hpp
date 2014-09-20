#ifndef _d7e438e1941c441e85e5b163374442b8
#define _d7e438e1941c441e85e5b163374442b8
#include <regex>
#include <ostream>
#include <string>
#include <functional>
#include <iterator>
#include <vector>
#include <numeric>
#include <type_traits>

namespace bsb
{
namespace regex_ext
{

  template< class Traits, class CharT,
	    class STraits, class SAlloc >
  inline std::basic_string<CharT,STraits,SAlloc> 
  regex_replace_ext( const std::basic_string<CharT,STraits,SAlloc>& s,
		     const std::basic_regex<CharT,Traits>& re,
		     const typename std::common_type<std::function<std::basic_string<CharT,STraits,SAlloc> 
		     (const unsigned, const std::basic_string<CharT,STraits,SAlloc> &)>>::type& fmt,
			  std::regex_constants::match_flag_type flags =
			  std::regex_constants::match_default)
  {
    std::vector<int> smatches{-1};
    if(re.mark_count() == 0)
	smatches.push_back(0);
    else
      {
	smatches.resize(1+re.mark_count());
	std::iota(std::next(smatches.begin()), smatches.end(), 1); //-1, 1, 2, etc...    
      }

    unsigned smatch_count = smatches.size();
    unsigned count = 0;

    std::regex_token_iterator
      <typename std::basic_string<CharT,STraits,SAlloc>::const_iterator> 
      tbegin(s.begin(), s.end(), re, smatches, flags), tend;            

    std::basic_stringstream<CharT,STraits,SAlloc> ret_val;
    std::for_each(tbegin, tend, [&count,&smatch_count,&ret_val,&fmt]
		  (const std::basic_string<CharT,STraits,SAlloc> & token)
		  {
		    if(token.size() != 0)
		      {
			if(!count) 
			  ret_val << token;
			else
			  ret_val << fmt(count,token);
		      }
		    count = ++count % smatch_count;
		  });
    return ret_val.str();

  }

  template< class Traits, class CharT,
	    class STraits, class SAlloc >
  inline std::basic_string<CharT,STraits,SAlloc> 
  regex_replace_ext( const std::basic_string<CharT,STraits,SAlloc>& s,
		     const std::basic_regex<CharT,Traits>& re,
		     const typename std::common_type<std::function<std::basic_string<CharT,STraits,SAlloc>
		     (const std::basic_string<CharT,STraits,SAlloc> &)>>::type& fmt,
			  std::regex_constants::match_flag_type flags =
			  std::regex_constants::match_default)
  {    
    std::vector<int> smatches{-1,0};
    unsigned smatch_count = smatches.size();
    unsigned count = 0;

    std::regex_token_iterator
      <typename std::basic_string<CharT,STraits,SAlloc>::const_iterator> 
      tbegin(s.begin(), s.end(), re, smatches, flags), tend;            

    std::basic_stringstream<CharT,STraits,SAlloc> ret_val;
    std::for_each(tbegin, tend, [&count,&smatch_count,&ret_val,&fmt]
		  (const std::basic_string<CharT,STraits,SAlloc> & token)		  {
		    if(token.size() != 0)
		      {
			if(!count) 
			  ret_val << token;
			else
			  ret_val << fmt(token);
		      }
		    count = ++count % smatch_count;
		  });
    return ret_val.str();
  }

}
}

#endif
