#ifndef __THODD_RANGE_COUNT_HPP__
#  define __THODD_RANGE_COUNT_HPP__

#  include <utility>

#  include <thodd/range/reduce.hpp>
#  include <thodd/range/filter.hpp>
#  include <thodd/functional.hpp>
#  include <thodd/range/distance.hpp>

namespace 
thodd 
{    
    inline constexpr auto
    count_if = 
    [] (auto && container, auto && predicate)
    {
        return 
        distance (
            filter (
                std::forward<decltype(container)>(container),
                std::forward<decltype(predicate)>(predicate)));
    } ;        

    inline constexpr auto
    count = 
    [] (auto && container, auto && object)
    {
        return 
        count_if(
            std::forward<decltype(container)>(container), 
            equal(cref(std::forward<decltype(object)>(object)), $0)) ;
    } ;    
}

#endif
