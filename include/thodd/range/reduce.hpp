#ifndef __THODD_RANGE_REDUCE_HPP__
#  define __THODD_RANGE_REDUCE_HPP__

#  include <utility>
#  include <algorithm>

#  include <thodd/functional.hpp>
#  include <thodd/range/for_each.hpp>

namespace 
thodd 
{
    inline constexpr auto
    reduce =
    [] (auto && container, auto && acc, auto && accumulator)
    -> decltype(auto)
    {
        auto __acc = acc ;
        
        thodd::for_each (
            container, 
            [&__acc, &accumulator] (auto && item) { __acc = accumulator(__acc, item) ; }) ;

        return 
        __acc ;
    } ;
}

#endif