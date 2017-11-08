#ifndef __THODD_RANGE_LAZY_FILTER_ITERATOR_HPP__
#  define __THODD_RANGE_LAZY_FILTER_ITERATOR_HPP__

#  include <type_traits>
#  include <utility>

#  include <thodd/optional.hpp>

namespace 
thodd 
{
    namespace detail
    {
        template <typename type_t>
        auto ref_or_value (type_t & t) -> type_t* 
        { return &t ; }

        template <typename type_t>
        auto ref_or_value (type_t const & t) -> type_t 
        { return t ; }
    }

    template <
        typename iterator_t, 
        typename predicate_t>
    struct lazy_filter_iterator 
    {
        iterator_t it ;  
        iterator_t end_it ;
        predicate_t predicate ;
        optional<std::decay_t<decltype(get(it))>> last_value {} ; 
    } ;





    constexpr auto
    make_lazy_filter_iterator (
        auto begin, auto end, auto predicate)
    {
        using iterator_t  = decltype(begin) ;
        using predicate_t = decltype(predicate) ;

        lazy_filter_iterator<iterator_t, predicate_t> lfi { begin, end, predicate } ;

        if (not_equals(lfi.it, lfi.end_it))
            if (predicate(value_of(lfi.last_value) = get(lfi.it))) 
                next (lfi) ; 

        return 
        lfi;
    }

    constexpr auto
    next (lazy_filter_iterator<auto, auto> & it)
    -> decltype(auto)
    { 
        while (not_equals(it.it, it.end_it))
        {
            next(it.it) ;

            if (not_equals(it.it, it.end_it) && it.predicate(value_of(it.last_value) = get(it))) 
                break ; 
        }

        return it ;
    }

    constexpr auto
    next (lazy_filter_iterator<auto, auto> const & it)
    -> decltype(auto)
    { 
        while (not_equals(it.it, it.end_it))
        {
            next(it.it) ;

            if (not_equals(it.it, it.end_it) && it.predicate(value_of(it.last_value) = get(it))) 
                break ; 
        }

        return it ;
    }

    constexpr auto
    next (lazy_filter_iterator<auto, auto> && it)
    -> decltype(auto)
    { 
        while (not_equals(it.it, it.end_it))
        {
            next(it.it) ;

            if (not_equals(it.it, it.end_it) && it.predicate(value_of(it.last_value) = get(it))) 
                break ; 
        }

        return it ;
    }



    constexpr auto 
    get (lazy_filter_iterator<auto, auto> & it)
    -> decltype(auto)
    { 
        return value_of(it.last_value) ; 
    }

    constexpr auto
    get (lazy_filter_iterator<auto, auto> const & it)
    -> decltype(auto)
    { 
        return value_of(it.last_value) ;
     }

    constexpr auto
    get (lazy_filter_iterator<auto, auto> && it)
    -> decltype(auto)
    { 
        return value_of(it.last_value) ; 
    }



    constexpr bool
    not_equals (
        lazy_filter_iterator<auto, auto> const & lit, 
        lazy_filter_iterator<auto, auto> const & rit)
    { return not_equals(lit.it, rit.it) ; }
}

#endif