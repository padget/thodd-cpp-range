#ifndef __THODD_RANGE_NEXT_HPP__
#  define __THODD_RANGE_NEXT_HPP__

namespace 
thodd {
    inline constexpr auto 
    next_while (auto && predicate, auto & it, auto const & end_it)
    -> decltype(it) 
    {
        while (not_equals(it, end_it) && predicate(it))
            next (it) ;

        return (it) ; 
    }

    inline constexpr auto 
    next_if (auto && predicate, auto & it, auto end_it) 
    -> decltype (it)
    {
        if (not_equals(it, end_it) && predicate(it)) 
            next (it) ;
        
        return (it)
    } 
}

#endif