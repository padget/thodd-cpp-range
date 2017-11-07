#ifndef __THODD_RANGE_LAZY_ITERATOR_HPP__
#  define __THODD_RANGE_LAZY_ITERATOR_HPP__

#  include <type_traits>

namespace 
thodd 
{
    template <
        typename iterator_t, 
        typename apply_t>
    struct lazy_iterator 
    {
        iterator_t it ;
        apply_t apply ;
    } ;

    template <typename iterator_t, typename apply_t>
    lazy_iterator (iterator_t, apply_t) -> lazy_iterator<iterator_t, apply_t> ;


    
    constexpr auto
    next (lazy_iterator<auto, auto> & it)
    -> decltype(auto)
    { 
        next(it.it) ;
        return it ;
    }

    constexpr auto 
    next (lazy_iterator<auto, auto> const & it)
    -> decltype(auto)
    { 
        next(it.it) ;
        return it ;
    }

    constexpr auto
    next (lazy_iterator<auto, auto> && it)
    -> decltype(auto)
    { 
        next(it.it) ;
        return it ;
    }



    constexpr auto 
    get (lazy_iterator<auto, auto> & it)
    -> decltype(auto)
    { return it.apply(get(it.it)) ; }

    constexpr auto
    get (lazy_iterator<auto, auto> const & it)
    -> decltype(auto)
    { return it.apply(get(it.it)) ; }

    constexpr auto
    get (lazy_iterator<auto, auto> && it)
    -> decltype(auto)
    { return it.apply(get(it.it)) ; }



    constexpr bool
    not_equals (
        lazy_iterator<auto, auto> const & lit, 
        lazy_iterator<auto, auto> const & rit)
    { return not_equals(lit.it, rit.it) ; }
}

#endif