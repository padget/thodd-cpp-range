#ifndef __THODD_RANGE_MAP_HPP__
#  define __THODD_RANGE_MAP_HPP__

#  include <map>

namespace 
thodd
{
  template <
    typename key_t,
    typename type_t>
  using map = std::map<key_t, type_t> ;
  
  constexpr auto 
  push (
    map<auto, auto> & ma, 
    auto && key, 
    auto && value)
  -> decltype(auto)
  {
    ma.emplace(
      std::forward<decltype(key)>(key), 
      std::forward<decltype(value)>(value)) ;

    return ma ;
  }
}

#endif