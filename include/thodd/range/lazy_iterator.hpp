#ifndef __THODD_RANGE_LAZY_ITERATOR_HPP__
#  define __THODD_RANGE_LAZY_ITERATOR_HPP__

#  include <type_traits>
#  include <utility>

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


    constexpr auto 
    make_lazy_iterator (
        auto && it, 
        auto && apply)
    {
        return 
        lazy_iterator<
            std::decay_t<decltype(it)>, 
            std::decay_t<decltype(apply)>>
        { std::forward<decltype(it)>(it),
          std::forward<decltype(apply)>(apply) } ;
    }

    constexpr auto
    next (lazy_iterator<auto, auto> & it)
    { next(it.it) ; }

    constexpr auto 
    value_of (lazy_iterator<auto, auto> & it)
    -> decltype(auto)
    { return it.apply(value_of(it.it)) ; }

    constexpr bool
    not_equals (
        lazy_iterator<auto, auto> const & lit, 
        lazy_iterator<auto, auto> const & rit)
    { return not_equals(lit.it, rit.it) ; }
}

#endif