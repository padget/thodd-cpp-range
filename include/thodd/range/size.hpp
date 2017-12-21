#ifndef __thodd_range_size_hpp__
#  define  __thodd_range_size_hpp__ 

#  include <thodd/range/for_each.hpp>
#  include <thodd/functional.hpp>

namespace
thodd
{
  [[pure]]
  inline constexpr auto 
  size = [] (auto const & stream) {
    auto cpt = 0u ;
    thodd::for_each(stream, thodd::inc(ref(cpt))) ;
    return cpt ;
  } ;
}

#endif