#ifndef __THODD_RANGE_ARRAY_HPP__
#  define __THODD_RANGE_ARRAY_HPP__

#  include <utility>
#  include <array>

namespace 
thodd
{
  template <
    typename type_t, 
    size_t size_c>
  using array = std::array<type_t, size_c> ;

  constexpr auto
  make_array (auto && first, auto && ... item)
  {
    return 
    thodd::array<
      std::decay_t<decltype(first)>, 
      1 + sizeof...(item)>
    {
      { std::forward<decltype(first)>(first), 
        std::forward<decltype(item)>(item)... }
    } ;
  }
  

  template <
    typename type_t,
    size_t size_c>
  constexpr auto
  size(array<type_t, size_c> const &)
  { return size_c ; }
}

#endif