#ifndef __THODD_RANGE_LAZY_INDIRECT_ITERATOR_HPP__
#  define __THODD_RANGE_LAZY_INDIRECT_ITERATOR_HPP__

#  include <type_traits>
#  include <thodd/range/range.hpp>

namespace
thodd
{
    template <
        typename iterator_t>
    struct lazy_indirect_iterator 
    {
        iterator_t it ;
    } ;

    template <typename iterator_t>
    lazy_indirect_iterator (iterator_t) -> lazy_indirect_iterator<iterator_t> ;

    constexpr auto
    next (lazy_indirect_iterator<auto> & it)
    -> decltype(auto)
    { 
        next(it.it) ;
        return it ;
    }

    constexpr auto 
    next (lazy_indirect_iterator<auto> const & it)
    -> decltype(auto)
    { 
        next(it.it) ;
        return it ;
    }

    constexpr auto
    next (lazy_indirect_iterator<auto> && it)
    -> decltype(auto)
    { 
        next(it.it) ;
        return it ;
    }



    constexpr auto 
    get (lazy_indirect_iterator<auto> & it)
    -> decltype(auto)
    { return it.it ; }

    constexpr auto
    get (lazy_indirect_iterator<auto> const & it)
    -> decltype(auto)
    { return it.it ; }

    constexpr auto
    get (lazy_indirect_iterator<auto> && it)
    -> decltype(auto)
    { return it.it ; }



    constexpr bool
    not_equals (
        lazy_indirect_iterator<auto> const & lit, 
        lazy_indirect_iterator<auto> const & rit)
    { return not_equals(lit.it, rit.it) ; }



    inline constexpr auto
    indirect = 
    [] (auto && container) 
    {
        return 
        range { 
            lazy_indirect_iterator { begin(std::forward<decltype(container)>(container)) }, 
            lazy_indirect_iterator { end(std::forward<decltype(container)>(container)) } } ;
    } ;

}

#endif