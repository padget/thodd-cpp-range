#ifndef __THODD_RANGE_DISTANCE_HPP__
#  define __THODD_RANGE_DISTANCE_HPP__

#  include <utility>

#  include <thodd/range/reduce.hpp>
#  include <thodd/functional.hpp>

namespace
thodd 
{
    inline constexpr auto
    distance = 
    [] (auto && container) 
    {
        return 
        reduce (std::forward<decltype(container)>(container), 0u, inc($0)) ;
    } ;
}

#endif