#ifndef __THODD_RANGE_COLLECT_HPP__
#  define __THODD_RANGE_COLLECT_HPP__

#  include <utility>

namespace
thodd
{
    inline constexpr auto 
    collect = 
    [] (auto && container, auto && collector)
    {
        return 
        std::forward<decltype(collector)>(collector)(
            std::forward<decltype(container)>(container)) ;
    } ; 
}

#endif