#ifndef __THODD_RANGE_REDUCE_HPP__
#  define __THODD_RANGE_REDUCE_HPP__

#  include <utility>
#  include <algorithm>

#  include <thodd/functional.hpp>

namespace 
thodd 
{
    inline constexpr auto
    reduce =
    [] (auto && container, auto && acc, auto && accumulator)
    -> decltype(auto)
    {
        auto __acc = acc ;
        
        for (auto && item : container)
            __acc = std::forward<decltype(accumulator)>(accumulator)(__acc, item) ;

        return 
        __acc ;
    } ;
}

#endif