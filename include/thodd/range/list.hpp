#ifndef __THODD_RANGE_LIST_HPP__
#  define __THODD_RANGE_LIST_HPP__

#  include <list>
#  include <iostream>

namespace 
thodd
{
    
    template <
        typename type_t>
    struct list
    {
        std::list<type_t> data ;
    } ;

    template <
        typename type_t>
    struct list_iterator 
    {
        typename std::list<type_t>::iterator it ; 
    } ;

    constexpr auto
    make_list (auto && first, auto && ... item)
    {
        return 
        list<std::decay_t<decltype(first)>> 
        { { std::forward<decltype(first)>(first), 
            std::forward<decltype(item)>(item)... } };
    }

    constexpr auto
    push_back (list<auto> & l, auto && item)
    -> decltype(auto)
    {
        l.data.push_back(std::forward<decltype(item)>(item)) ;
        return l ;
    }
    
    constexpr auto 
    push_back (list<auto> const & l, auto && item)
    -> decltype(auto) const
    {
        auto new_list = l ;
        return 
        push_back(new_list, std::forward<decltype(item)>(item)) ;
    }


    constexpr auto 
    next (list_iterator<auto> & it)
    -> decltype(auto)
    { 
        ++it.it ;
        return it ;
    }

    constexpr auto 
    next (list_iterator<auto> const & it)
    -> decltype(auto)
    { 
        ++it.it ;
        return it ;
    }

    constexpr auto 
    next (list_iterator<auto> && it)
    -> decltype(auto)
    { 
        ++it.it ;
        return it ;
    }

    constexpr auto 
    get (list_iterator<auto> & it)
    -> decltype(auto)
    {  return *it.it ; }

    constexpr auto 
    get (list_iterator<auto> const & it)
    -> decltype(auto)
    { return *it.it ; }

    constexpr auto 
    get (list_iterator<auto> && it)
    -> decltype(auto)
    { return *it.it ; }

    constexpr bool
    not_equals (
        list_iterator<auto> const & lit, 
        list_iterator<auto> const & rit)
    { return lit.it != rit.it ; }

        
    template <
        typename type_t>
    constexpr thodd::list_iterator<type_t> 
    begin (thodd::list<type_t> & lis)
    {
        return 
        thodd::list_iterator<type_t>
        { lis.data.begin() } ;
    }

    template <
        typename type_t>
    constexpr thodd::list_iterator<type_t> const 
    begin (thodd::list<type_t> const & lis)
    {
        return 
        thodd::list_iterator<type_t>
        { lis.data.begin() } ;
    }

    template <
        typename type_t>
    constexpr thodd::list_iterator<type_t> const 
    begin (thodd::list<type_t> && lis)
    {
        return 
        thodd::list_iterator<type_t>
        { lis.data.begin() } ;
    }

    template <
        typename type_t>
    constexpr thodd::list_iterator<type_t> 
    end (thodd::list<type_t> & lis)
    {
        return 
        thodd::list_iterator<type_t>
        { lis.data.end() } ;
    }

    template <
        typename type_t>
    constexpr thodd::list_iterator<type_t> const
    end (thodd::list<type_t> const & lis)
    {
        return 
        thodd::list_iterator<type_t>
        { lis.data.end() } ;
    }

    template <
        typename type_t>
    constexpr thodd::list_iterator<type_t> const
    end (thodd::list<type_t> && lis)
    {
        return 
        thodd::list_iterator<type_t>
        { lis.data.end() } ;
    }
}

#endif