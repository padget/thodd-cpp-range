#ifndef __THODD_RANGE_FILTER_HPP__
#  define __THODD_RANGE_FILTER_HPP__

#  include <utility>
#  include <type_traits>

#  include <thodd/range/range.hpp>
#  include <thodd/functional.hpp>
#  include <thodd/optional.hpp>

namespace 
thodd 
{
    template <
        typename iterator_t, 
        typename predicate_t>
    struct lazy_filter_iterator 
    {
        iterator_t it ;  
        iterator_t end_it ;
        predicate_t predicate ;
        optional<std::decay_t<decltype(value_of(it))>> last_value {} ; 
    } ;


    constexpr auto
    make_lazy_filter_iterator (
        auto && begin, 
        auto && end, 
        auto && predicate)
    {
        using iterator_t  = std::decay_t<decltype(begin)> ;
        using predicate_t = std::decay_t<decltype(predicate)> ;

        lazy_filter_iterator<iterator_t, predicate_t> lfi 
            { std::forward<decltype(begin)>(begin), 
              std::forward<decltype(end)>(end), 
              std::forward<decltype(predicate)>(predicate) } ;

        if (not_equals(lfi.it, lfi.end_it))
            if (!predicate(value_of(lfi.last_value = thodd::make_optional(value_of(lfi.it))))) 
                next (lfi) ; 

        return 
        lfi;
    }

   



    constexpr auto 
    value_of (lazy_filter_iterator<auto, auto> & it)
    -> decltype(auto)
    { 
        return value_of(it.last_value) ; 
    }

    constexpr auto
    next (thodd::lazy_filter_iterator<auto, auto> & it)
    -> decltype(auto)
    { 
        while (not_equals(it.it, it.end_it))
        {
            next(it.it) ;

            if (not_equals(it.it, it.end_it) && it.predicate(value_of(it.last_value = make_optional(value_of(it.it))))) 
                break ; 
        }

        return it ;
    }
   
    constexpr bool
    not_equals (
        lazy_filter_iterator<auto, auto> const & lit, 
        lazy_filter_iterator<auto, auto> const & rit)
    { return not_equals(lit.it, rit.it) ; }

    inline constexpr auto
    filter =  
    [] (auto && container, auto && predicate)
    {
        auto begin_it = begin(std::forward<decltype(container)>(container)) ;
        auto end_it = end(std::forward<decltype(container)>(container)) ;

        auto begin_filter = make_lazy_filter_iterator (begin_it, end_it, std::forward<decltype(predicate)>(predicate)) ;
        auto end_filter   = make_lazy_filter_iterator (end_it, end_it, std::forward<decltype(predicate)>(predicate)) ;

        return 
        make_range (begin_filter, end_filter) ;
    } ;


    inline constexpr auto 
    filters = 
    [] (auto && container, auto && ... predicates) 
    {
        return
        filter (
            std::forward<decltype(container)>(container), 
            and_(std::forward<decltype(predicates)>(predicates)...)) ;
    } ;
}

#endif