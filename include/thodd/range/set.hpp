#ifndef __THODD_RANGE_SET_HPP__
#  define __THODD_RANGE_SET_HPP__ 

#  include <set>

namespace 
thodd
{
    template <
        typename type_t>
    struct set
    {
        std::set<type_t> data ;
    } ;

    template <
        typename type_t>
    struct set_iterator 
    {
        typename std::set<type_t>::iterator it ; 
    } ;

    constexpr auto
    make_set (auto && first, auto && ... item)
    -> decltype(auto)
    {
        return 
        set<std::decay_t<decltype(first)>> 
        { { std::forward<decltype(first)>(first), 
            std::forward<decltype(item)>(item)... } };
    }

    constexpr auto
    insert (set<auto> & l, auto && item)
    -> decltype(auto)
    {
        l.data.insert(std::forward<decltype(item)>(item)) ;
        return l ;
    }
    
    constexpr auto 
    insert (set<auto> const & l, auto && item)
    -> decltype(auto) const
    {
        auto new_set = l ;
        return 
        insert(new_set, std::forward<decltype(item)>(item)) ;
    }


    constexpr auto 
    next (set_iterator<auto> & it)
    -> decltype(auto)
    { 
        ++it.it ;
        return it ;
    }

    constexpr auto 
    next (set_iterator<auto> const & it)
    -> decltype(auto)
    { 
        ++it.it ;
        return it ;
    }

    constexpr auto 
    next (set_iterator<auto> && it)
    -> decltype(auto)
    { 
        ++it.it ;
        return it ;
    }

    constexpr auto 
    get (set_iterator<auto> & it)
    -> decltype(auto)
    {  return *it.it ; }

    constexpr auto 
    get (set_iterator<auto> const & it)
    -> decltype(auto)
    { return *it.it ; }

    constexpr auto 
    get (set_iterator<auto> && it)
    -> decltype(auto)
    { return *it.it ; }

    constexpr bool
    not_equals (
        set_iterator<auto> const & lit, 
        set_iterator<auto> const & rit)
    { return lit.it != rit.it ; }

        
    template <
        typename type_t>
    constexpr thodd::set_iterator<type_t> 
    begin (thodd::set<type_t> & lis)
    {
        return 
        thodd::set_iterator<type_t>
        { lis.data.begin() } ;
    }

    template <
        typename type_t>
    constexpr thodd::set_iterator<type_t> const 
    begin (thodd::set<type_t> const & lis)
    {
        return 
        thodd::set_iterator<type_t>
        { lis.data.begin() } ;
    }

    template <
        typename type_t>
    constexpr thodd::set_iterator<type_t> const 
    begin (thodd::set<type_t> && lis)
    {
        return 
        thodd::set_iterator<type_t>
        { lis.data.begin() } ;
    }

    template <
        typename type_t>
    constexpr thodd::set_iterator<type_t> 
    end (thodd::set<type_t> & lis)
    {
        return 
        thodd::set_iterator<type_t>
        { lis.data.end() } ;
    }

    template <
        typename type_t>
    constexpr thodd::set_iterator<type_t> const
    end (thodd::set<type_t> const & lis)
    {
        return 
        thodd::set_iterator<type_t>
        { lis.data.end() } ;
    }

    template <
        typename type_t>
    constexpr auto
    end (thodd::set<type_t> && lis)
    {
        return 
        thodd::set_iterator<type_t>
        { lis.data.end() } ;
    }
}
#endif