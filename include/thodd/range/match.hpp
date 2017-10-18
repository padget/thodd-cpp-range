#ifndef __THODD_RANGE_MATCH_HPP__ 
#  define __THODD_RANGE_MATCH_HPP__

namespace
thodd
{
    inline constexpr auto 
    all_of = 
    [] (auto && container, auto && predicate)
    {
        return 
        reduce (
            std::forward<decltype(container)>(container), true, 
            [predicate] (auto const & acc, auto && item) 
            { return acc && predicate(std::forward<decltype(item)>(item)) ; }) ;
    } ;

    inline constexpr auto 
    none_of = 
    [] (auto && container, auto && predicate)
    {
        return 
        count_if (
            std::forward<decltype(container)>(container), 
            std::forward<decltype(predicate)>(predicate)) == 0 ;
    } ;

    inline constexpr auto 
    any_of = 
    [] (auto && container, auto && predicate)
    {
        return 
        ! match_nothing (
            std::forward<decltype(container)>(container), 
            std::forward<decltype(predicate)>(predicate)) ;
    } ;
}

#endif