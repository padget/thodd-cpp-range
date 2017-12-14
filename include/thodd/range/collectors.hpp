#ifndef __THODD_RANGE_COLLECTORS_HPP__
#  define __THODD_RANGE_COLLECTORS_HPP__

#  include <utility>

#  include <thodd/range/list.hpp>
#  include <thodd/range/array.hpp>
#  include <thodd/range/for_each.hpp>
namespace
thodd 
{
  template <
    typename type_t>
  inline constexpr auto 
  to_list = 
  [] (auto && container) 
  {
    thodd::list<type_t> collected ;

    thodd::for_each (
      std::forward<decltype(container)>(container),
      [&collected] (auto && item) 
      { push_back (collected, std::forward<decltype(item)>(item)) ; }) ;
    
    return collected ;
  } ;

  template <
    typename type_t, 
    size_t size_c>
  inline constexpr auto 
  to_array = 
  [] (auto && container) 
  {
    thodd::array<type_t, size_c> collected ; 
    size_t idx = 0u ;

    thodd::for_each (
      std::forward<decltype(container)>(container), 
      [&collected, &idx] (auto && item) 
      { collected.data[idx] = std::forward<decltype(item)>(item) ; ++idx ; }) ;

    return collected ;
  } ;
}

#endif