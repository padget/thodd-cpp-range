#ifndef __THODD_RANGE_MINMAX_HPP__
#  define __THODD_RANGE_MINMAX_HPP__

#  include <type_traits>

#  include <thodd/range/reduce.hpp>
#  include <thodd/optional.hpp>

namespace
thodd 
{
    inline constexpr auto 
    max =
    [] (auto && container, auto && comparator)
    {
        return 
        reduce (
            std::forward<decltype(container)>(container),
            optional<std::decay_t<decltype(get(begin(container)))>>{}, 
            [comparator] (auto && acc, auto && item) 
            {
                if(!has_value(acc)) return make_optional(item) ;
                else return comparator(value_of(acc), item) ? make_optional (item) : acc ; 
            }) ;
    } ;

    inline constexpr auto 
    min = 
    [] (auto && container, auto && comparator) 
    {
        return 
        reduce (
            std::forward<decltype(container)>(container),
            optional<std::decay_t<decltype(get(begin(container)))>>{}, 
            [comparator] (auto && acc, auto && item) 
            {
                if(!has_value(acc)) return make_optional(item) ;
                else return comparator(value_of(acc), item) ? make_optional (item) : acc ; 
            }) ;
    } ;
}

#endif