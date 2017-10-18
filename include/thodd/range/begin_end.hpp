#ifndef __THODD_RANGE_BEGIN_END_HPP__
#  define __THODD_RANGE_BEGIN_END_HPP__

#  include <utility>

namespace 
thodd
{
    constexpr auto
    begin (auto && container)
    {
        return 
        std::forward<decltype(container)>(container).begin ; 
    }

    constexpr auto 
    end (auto && container)
    {
        return 
        std::forward<decltype(container)>(container).end ;
    }
}

#endif