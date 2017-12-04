#ifndef __THODD_RANGE_NEXT_HPP__
#  define __THODD_RANGE_NEXT_HPP__

namespace 
thodd {
    constexpr auto next_while = 
    [] (auto && predicate) 
        {
            return 
            [predicate] (auto && it, auto const & end_it) 
            {
                while (thodd::not_equals (it, end_it) && predicate (it))
                    std::next (it) ;
            } ;
        } ;

    constexpr auto next_if = 
    [] (auto && predicate) 
    {
        return 
        [predicate] (auto && it, auto const & end_it) 
        {
            if (thodd::not_equals (it, end_it) && predicate (it))
                std::next (it) ;
        } ;
    } ;
}

#endif