#ifndef __THODD_RANGE_SET_HPP__
#  define __THODD_RANGE_SET_HPP__ 

#  include <set>

namespace 
thodd
{
  template <
    typename type_t>
  using set = std::set<type_t> ;

  constexpr auto
  make_set (auto && first, auto && ... item)
  -> decltype(auto)
  {
    return 
    set<std::decay_t<decltype(first)>> 
    { { std::forward<decltype(first)>(first), 
        std::forward<decltype(item)>(item)... } };
  }

  constexpr auto
  insert (set<auto> & s, auto && item)
  -> decltype(auto)
  {
    s.insert(std::forward<decltype(item)>(item)) ;
    return s ;
  }
}
#endif