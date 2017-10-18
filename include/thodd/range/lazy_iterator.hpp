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

        using value_type = std::decay_t<decltype(apply(*it))> ;

        constexpr auto & operator ++ () { return (++it, *this) ; }
        constexpr auto const & operator ++ () const { return (++it, *this) ; }

        constexpr auto operator * () -> decltype(auto) { return apply(*it) ; }
        constexpr auto operator * () const -> decltype(auto) { return apply(*it) ; }

        constexpr auto operator != (lazy_iterator const & other) const { return other.it != it ; }
    } ;

    template <typename iterator_t, typename apply_t>
    lazy_iterator (iterator_t, apply_t) -> lazy_iterator<iterator_t, apply_t> ;
}

#endif