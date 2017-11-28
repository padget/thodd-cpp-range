#ifndef __THODD_RANGE_FIND_HPP__
#  define __THODD_RANGE_FIND_HPP__

#  include <type_traits>
#  include <utility>

#  include <thodd/optional.hpp>
#  include <thodd/range/reduce.hpp>

namespace 
thodd
{
    inline constexpr auto 
    find_first = 
    [] (auto && container, auto && predicate)
    {
        using value_t = std::decay_t<decltype(get(begin(container)))> ;
        
        return 
        reduce (
            std::forward<decltype(container)>(container),
            thodd::optional<value_t>{}, 
            [predicate] (auto & acc, auto && item)
            { 
                return 
                !has_value(acc) && predicate(std::forward<decltype(item)>(item)) ?
                make_optional(item) : acc ;
            } 
        ) ;

    } ;

}

#endif