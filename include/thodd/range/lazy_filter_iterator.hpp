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
        optional<std::decay_t<decltype(get(it))>> last_value {}; 
    } ;





    constexpr auto
    make_lazy_filter_iterator (
        auto begin, auto end, auto predicate)
    {
        using iterator_t  = decltype(begin) ;
        using predicate_t = decltype(predicate) ;

        lazy_filter_iterator<iterator_t, predicate_t> lfi (begin, end, predicate) ;

        if (lfi.it != lfi.end_it)
        {
            if constexpr (std::is_pointer_v<decltype(lfi.last_value)>)
            { if (!predicate(*(lfi.last_value = detail::ref_or_value(*lfi.it)))) next (lfi) ; }
            else if (predicate(lfi.last_value = detail::ref_or_value(*lfi.it))) next (lfi) ; 
        } 

        return 
        lfi;
    }

    constexpr auto
    next (lazy_filter_iterator<auto, auto> & it)
    -> decltype(auto)
    { 
        while (it.it != it.end_it)
        {
            next(it.it) ;

            if constexpr (std::is_pointer_v<decltype(it.last_value)>)
            { if (it.it != it.end_it && predicate(*(it.last_value = detail::ref_or_value(get(it))))) break ; }
            else if (it.it != it.end_it && predicate(it.last_value = detail::ref_or_value(get(it)))) break ; 
        }

        return it ;
    }

    constexpr auto 
    next (lazy_filter_iterator<auto, auto> const & it)
    -> decltype(auto)
    { 
        while (it.it != it.end_it)
        {
            next(it.it) ;

            if constexpr (std::is_pointer_v<decltype(it.last_value)>)
            { if (it.it != it.end_it && predicate(*(it.last_value = detail::ref_or_value(get(it))))) break ; }
            else if (it.it != it.end_it && predicate(it.last_value = detail::ref_or_value(get(it)))) break ; 
        }

        return it ;
    }

    constexpr auto
    next (lazy_filter_iterator<auto, auto> && it)
    -> decltype(auto)
    { 
        while (it.it != it.end_it)
        {
            next(it.it) ;

            if constexpr (std::is_pointer_v<decltype(it.last_value)>)
            { if (it.it != it.end_it && predicate(*(it.last_value = detail::ref_or_value(get(it))))) break ; }
            else if (it.it != it.end_it && predicate(it.last_value = detail::ref_or_value(get(it)))) break ; 
        }

        return it ;
    }



    constexpr auto 
    get (lazy_filter_iterator<auto, auto> & it)
    -> decltype(auto)
    { 
        if constexpr (std::is_pointer_v<decltype(it.last_value)>)
            return *it.last_value ; 
        else return it.last_value ; 
    }

    constexpr auto
    get (lazy_filter_iterator<auto, auto> const & it)
    -> decltype(auto)
    { 
        if constexpr (std::is_pointer_v<decltype(it.last_value)>)
            return *it.last_value ; 
        else return it.last_value ;
     }

    constexpr auto
    get (lazy_filter_iterator<auto, auto> && it)
    -> decltype(auto)
    { 
        if constexpr (std::is_pointer_v<decltype(it.last_value)>)
            return *it.last_value ; 
        else return it.last_value ; 
    }



    constexpr bool
    not_equals (
        lazy_filter_iterator<auto, auto> const & lit, 
        lazy_filter_iterator<auto, auto> const & rit)
    { return not_equals(lit.it, rit.it) ; }
}

#endif