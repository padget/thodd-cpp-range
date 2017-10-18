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

        using value_type = std::decay_t<decltype(it)> ;
        
        constexpr auto & operator ++ () { return (++it, *this) ; }
        constexpr auto const & operator ++ () const { return (++it, *this) ; }

        constexpr auto operator * () { return it ; }
        constexpr auto operator * () const { return it ; }

        constexpr auto operator != (lazy_indirect_iterator const & other) const { return other.it != it ; }
    } ;

    template <typename iterator_t>
    lazy_indirect_iterator (iterator_t) -> lazy_indirect_iterator<iterator_t> ;

    inline constexpr auto
    indirect = 
    [] (auto && container) 
    {
        return 
        range { 
            lazy_indirect_iterator { std::forward<decltype(container)>(container).begin() }, 
            lazy_indirect_iterator { std::forward<decltype(container)>(container).end() } } ;
    } ;

}

#endif