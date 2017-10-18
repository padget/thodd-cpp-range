#ifndef __THODD_RANGE_MAP_HPP__
#  define __THODD_RANGE_MAP_HPP__

#  include <map>

namespace 
thodd
{
    
    template <
        typename key_t,
        typename type_t>
    struct map
    {
        std::map<key_t, type_t> data ;
    } ;

    template <
        typename key_t,
        typename type_t>
    struct map_iterator 
    {
        typename std::map<key_t, type_t>::iterator it ; 
    } ;

    constexpr auto 
    push (map<auto, auto> & ma, auto && key, auto && value)
    -> decltype(auto)
    {
        ma.data[std::forward<decltype(key)>(key)] = std::forward<decltype(value)>(value) ;
        return ma ;
    }

    constexpr auto 
    push (map<auto, auto> const & ma, auto && key, auto && value)
    -> decltype(auto) const
    {
        std::decay_t<decltype(ma)> new_map { ma } ;
        return 
        push (new_map, std::forward<decltype(key)>(key), std::forward<decltype(value)>(value)) ;
    }

    constexpr map_iterator<auto, auto> & 
    next (map_iterator<auto, auto> & it)
    { 
        ++it.it ;
        return it ;
    }

    constexpr map_iterator<auto, auto> const & 
    next (map_iterator<auto, auto> const & it)
    { 
        ++it.it ;
        return it ;
    }

    constexpr map_iterator<auto, auto> && 
    next (map_iterator<auto, auto> && it)
    { 
        ++it.it ;
        return it ;
    }

    constexpr auto
    get (map_iterator<auto, auto> & it)
    -> decltype(*it.it) &
    { return *it.it ; }

    constexpr auto 
    get (map_iterator<auto, auto> const & it)
    -> decltype(*it.it) const &
    { return *it.it ; }

    constexpr auto 
    get (map_iterator<auto, auto> && it)
    -> decltype(*it.it) const &
    { return *it.it ; }


    constexpr bool const
    not_equals (
        map_iterator<auto, auto> const & lit, 
        map_iterator<auto, auto> const & rit)
    { return lit.it != rit.it ; }

        
    template <
        typename key_t,
        typename type_t>
    constexpr thodd::map_iterator<key_t, type_t> 
    begin (thodd::map<key_t, type_t> & ma)
    {
        return 
        thodd::map_iterator<key_t, type_t>
        { ma.data.begin() } ;
    }

    template <
        typename key_t,
        typename type_t>
    constexpr thodd::map_iterator<key_t, type_t> const 
    begin (thodd::map<key_t, type_t> const & ma)
    {
        return 
        thodd::map_iterator<key_t, type_t>
        { ma.data.begin() } ;
    }

    template <
        typename key_t,
        typename type_t>
    constexpr thodd::map_iterator<key_t, type_t> const 
    begin (thodd::map<key_t, type_t> && ma)
    {
        return 
        thodd::map_iterator<key_t, type_t>
        { ma.data.begin() } ;
    }

    template <
        typename key_t, 
        typename type_t>
    constexpr thodd::map_iterator<key_t, type_t> 
    end (thodd::map<key_t, type_t> & ma)
    {
        return 
        thodd::map_iterator<key_t, type_t>
        { ma.data.end() } ;
    }

    template <
        typename key_t, 
        typename type_t>
    constexpr thodd::map_iterator<key_t, type_t> const
    end (thodd::map<key_t, type_t> const & ma)
    {
        return 
        thodd::map_iterator<key_t, type_t>
        { ma.data.end() } ;
    }

    template <
        typename key_t, 
        typename type_t>
    constexpr thodd::map_iterator<key_t, type_t> const
    end (thodd::map<key_t, type_t> && ma)
    {
        return 
        thodd::map_iterator<key_t, type_t>
        { ma.data.end() } ;
    }
}

#endif