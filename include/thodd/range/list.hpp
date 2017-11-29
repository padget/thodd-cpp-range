#ifndef __THODD_RANGE_LIST_HPP__
#  define __THODD_RANGE_LIST_HPP__

#  include <list>

namespace 
thodd
{
    
  template <
    typename type_t>
  using list = std::list<type_t> ;


constexpr auto
make_list (auto && first, auto && ... item)
{
  return 
  list<std::decay_t<decltype(first)>> 
  { { std::forward<decltype(first)>(first), 
      std::forward<decltype(item)>(item)... } };
  }

  constexpr auto
  push_back (list<auto> & l, auto && item)
  -> decltype(auto)
  {
    l.push_back(std::forward<decltype(item)>(item)) ;
    return l ;
  }
}

#endif