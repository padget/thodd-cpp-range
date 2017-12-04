#ifndef __THODD_RANGE_vector_HPP__
#  define __THODD_RANGE_vector_HPP__

#  include <vector>

namespace 
thodd
{
    
  template <
    typename type_t>
  using vector = std::vector<type_t> ;


constexpr auto
make_vector (auto && first, auto && ... item)
{
  return 
  vector<std::decay_t<decltype(first)>> 
  { { std::forward<decltype(first)>(first), 
      std::forward<decltype(item)>(item)... } };
  }

  constexpr auto
  push_back (vector<auto> & l, auto && item)
  -> decltype(auto)
  {
    l.push_back(std::forward<decltype(item)>(item)) ;
    return l ;
  }
}

#endif