#ifndef _d7e438e1941c441e85e5b163374442b8
#define _d7e438e1941c441e85e5b163374442b8
#include <regex>
#include <ostream>
#include <string>
#include <functional>
#include <iterator>

namespace bsb
{
namespace regex_ext
{

  //replace fmt with a function
  /*
  template< class OutputIt, class BidirIt,
	    class Traits, class CharT,
	    class STraits, class SAlloc >
  OutputIt regex_replace( OutputIt out, BidirIt first, BidirIt last,
			  const std::basic_regex<CharT,Traits>& re,
			  const std::basic_string<CharT,STraits,SAlloc>& fmt,
			  std::regex_constants::match_flag_type flags = 
			  std::regex_constants::match_default );

  template< class OutputIt, class BidirIt,
	    class Traits, class CharT >
  OutputIt regex_replace( OutputIt out, BidirIt first, BidirIt last,
			  const std::basic_regex<CharT,Traits>& re,
			  const CharT* fmt,
			  std::regex_constants::match_flag_type flags = 
			  std::regex_constants::match_default );
  */

  template< class Traits, class CharT,
	    class STraits, class SAlloc >
  inline std::basic_string<CharT,STraits,SAlloc> 
  regex_replace_ext( const std::basic_string<CharT,STraits,SAlloc>& s,
			    const std::basic_regex<CharT,Traits>& re,
			    std::function<std::string (const std::string &)> fmt)
  {
    std::regex_token_iterator
      <typename std::basic_string<CharT,STraits,SAlloc>::const_iterator> 
      tbegin(s.begin(), s.end(), re, {-1,1}), tend;            
    uint8_t count = 0;
    uint8_t mark_count = re.mark_count() + 1;
    //there should be two modes. One where fmt handles all submatches and one where there is a unique fmt for each submatch
      std::basic_stringstream<CharT,STraits,SAlloc> ret_val;
      std::for_each(tbegin, tend, [&count,&mark_count,&ret_val,&fmt]
		  (const std::basic_string<CharT,STraits,SAlloc> & token){
		    if(!count) 
		      ret_val << token;
		    else
		      ret_val << fmt(token);
		    count = ++count % mark_count;
		  });
    return ret_val.str();
  }

  /*
  template< class Traits, class CharT,
	    class STraits, class SAlloc >
  std::basic_string<CharT,STraits,SAlloc> 
  regex_replace( const std::basic_string<CharT,STraits,SAlloc>& s,
		 const std::basic_regex<CharT,Traits>& re,
		 const CharT* fmt,
		 std::regex_constants::match_flag_type flags = 
		 std::regex_constants::match_default );

  template< class Traits, class CharT,
	    class STraits, class SAlloc >
  std::basic_string<CharT> 
  regex_replace( const CharT* s,
		 const std::basic_regex<CharT,Traits>& re,
		 const std::basic_string<CharT,STraits,SAlloc>& fmt,
		 std::regex_constants::match_flag_type flags = 
		 std::regex_constants::match_default );

  template< class Traits, class CharT >
  std::basic_string<CharT> 
  regex_replace( const CharT* s,
		 const std::basic_regex<CharT,Traits>& re,
		 const CharT* fmt,
		 std::regex_constants::match_flag_type flags = 
		 std::regex_constants::match_default );
  */
}
}

#endif
