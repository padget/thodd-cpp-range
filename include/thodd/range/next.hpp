#ifndef __THODD_RANGE_NEXT_HPP__
#  define __THODD_RANGE_NEXT_HPP__

namespace 
thodd {
    inline constexpr auto next_while = 
    [] (auto && predicate) 
    {
        return 
        [predicate] (auto && it, auto const & end_it)
        -> decltype(it) 
        {
            while (not_equals (std::forward<decltype(it)>(it), end_it) && predicate (std::forward<decltype(it)>(it)))
                next (std::forward<decltype(it)>(it)) ;

            return (it) ; 
        } ;
    } ;

    inline constexpr auto next_if = 
    [] (auto && predicate) 
    {
        return 
        [predicate] (auto && it, auto const & end_it) 
        -> decltype(it)
        {
            if (not_equals (std::forward<decltype(it)>(it), end_it) && predicate (std::forward<decltype(it)>(it)))
                next (std::forward<decltype(it)>(it)) ;
            
            return (it) ;
        } ;
    } ;
}

#endif