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
  //honor match flag types
  //see regex_token_iterator constructor:
  //http://en.cppreference.com/w/cpp/regex/regex_token_iterator/regex_token_iterator
  //replace fmt with a function
 
  template< class OutputIt, class BidirIt,
	    class Traits, class CharT,
	    class STraits, class SAlloc >
  OutputIt regex_replace( OutputIt out, BidirIt first, BidirIt last,
			  const std::basic_regex<CharT,Traits>& re,
			  const typename std::common_type<std::function<std::basic_string<CharT,STraits,SAlloc> 
			  (const unsigned, const std::basic_string<CharT,STraits,SAlloc> &)>>::type& fmt,
			  std::regex_constants::match_flag_type flags =
			  std::regex_constants::match_default )
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
      tbegin(first, last, re, smatches), tend;            

    std::for_each(tbegin, tend, [&count,&smatch_count,&out,&fmt]
		  (const std::basic_string<CharT,STraits,SAlloc> & token)
		  {
		    if(token.size() != 0)
		      {
			if(!count) 
			  out << token;
			else
			  out << fmt(count,token);
		      }
		    count = ++count % smatch_count;
		  });
    return out;
  }

  /*
  template< class OutputIt, class BidirIt,
	    class Traits, class CharT >
  OutputIt regex_replace( OutputIt out, BidirIt first, BidirIt last,
  const std::basic_regex<CharT,Traits>& re,
			  const CharT* fmt,
			  std::regex_constants::match_flag_type flags = 
			  std::regex_constants::match_default );
  */

  //Matches regex and calls fmt for replacement value.
  //fmt is passed the sub-expression index and matched string and returns the replacement value
  template< class Traits, class CharT,
	    class STraits, class SAlloc >
  inline std::basic_string<CharT,STraits,SAlloc> 
  regex_replace_ext( const std::basic_string<CharT,STraits,SAlloc>& s,
		     const std::basic_regex<CharT,Traits>& re,
		     const typename std::common_type<std::function<std::basic_string<CharT,STraits,SAlloc> 
		     (const unsigned, const std::basic_string<CharT,STraits,SAlloc> &)>>::type& fmt)
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
      tbegin(s.begin(), s.end(), re, smatches), tend;            

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

  //Matches regex and calls fmt for replacement value.
  //fmt is passed the matched string returns the replacement value
  //to match subexpressions then use the std::string fmt(const unsigned, const std::string_ overload 
  template< class Traits, class CharT,
	    class STraits, class SAlloc >
  inline std::basic_string<CharT,STraits,SAlloc> 
  regex_replace_ext( const std::basic_string<CharT,STraits,SAlloc>& s,
		     const std::basic_regex<CharT,Traits>& re,
		     const typename std::common_type<std::function<std::basic_string<CharT,STraits,SAlloc>
		     (const std::basic_string<CharT,STraits,SAlloc> &)>>::type& fmt)
  {    
    std::vector<int> smatches{-1,0};

    unsigned smatch_count = smatches.size();
    unsigned count = 0;

    std::regex_token_iterator
      <typename std::basic_string<CharT,STraits,SAlloc>::const_iterator> 
      tbegin(s.begin(), s.end(), re, smatches), tend;            

    std::basic_stringstream<CharT,STraits,SAlloc> ret_val;
    std::for_each(tbegin, tend, [&count,&smatch_count,&ret_val,&fmt]
		  (const std::basic_string<CharT,STraits,SAlloc> & token)
		  {
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
