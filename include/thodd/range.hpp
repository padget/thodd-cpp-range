#ifndef __THODD_RANGE_HPP__
#  define __THODD_RANGE_HPP__



namespace 
thodd
{
  constexpr auto 
  get (auto && it)
  -> decltype(auto)
  { return *std::forward<decltype(it)>(it) ; }


  constexpr bool
  not_equals (
    auto const & lit, 
    auto const & rit)
  { return lit != rit ; }


  constexpr auto 
  begin(auto && container)
  -> decltype(auto)
  { return std::forward<decltype(container)>(container).begin() ; }


  constexpr auto 
  end(auto && container)
  -> decltype(auto)
  { return std::forward<decltype(container)>(container).end() ; }
}

#  include <thodd/range/for_each.hpp>

#  include <thodd/range/array.hpp>
#  include <thodd/range/list.hpp>
#  include <thodd/range/map.hpp>
#  include <thodd/range/set.hpp>
#  include <thodd/range/string.hpp>

#  include <thodd/range/range.hpp>

#  include <thodd/range/lazy_iterator.hpp>
#  include <thodd/range/lazy_indirect_iterator.hpp>
#  include <thodd/range/collect.hpp>
#  include <thodd/range/collectors.hpp>
#  include <thodd/range/count.hpp> 
#  include <thodd/range/distance.hpp>
#  include <thodd/range/filter.hpp>
#  include <thodd/range/find.hpp>
#  include <thodd/range/generate.hpp>
#  include <thodd/range/project.hpp>
#  include <thodd/range/match.hpp>
#  include <thodd/range/minmax.hpp>
#  include <thodd/range/next.hpp>
#  include <thodd/range/reduce.hpp>
#  include <thodd/range/step.hpp>

#endif