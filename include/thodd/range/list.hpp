#ifndef __THODD_RANGE_LIST_HPP__
#  define __THODD_RANGE_LIST_HPP__

#  include <list>

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

    template <typename type_t>
    constexpr auto
    push_back (list<type_t> & l, auto && item)
    -> decltype(auto)
    {
        l.push_back(std::forward<decltype(item)>(item)) ;
        return l ;
    }
    

    template <typename type_t>
    constexpr auto 
    push_back (list<type_t> const & l, auto && item)
    -> decltype(auto) const
    {
        list<type_t> new_list { l } ;
        return 
        push_back(new_list, std::forward<decltype(item)>(item)) ;
    }


    constexpr list_iterator<auto> & 
    next (list_iterator<auto> & it)
    { 
        ++it.it ;
        return it ;
    }

    constexpr list_iterator<auto> const & 
    next (list_iterator<auto> const & it)
    { 
        ++it.it ;
        return it ;
    }

    constexpr list_iterator<auto> && 
    next (list_iterator<auto> && it)
    { 
        ++it.it ;
        return it ;
    }

    constexpr auto & 
    get (list_iterator<auto> & it)
    { return *it.it ; }

    constexpr auto const & 
    get (list_iterator<auto> const & it)
    { return *it.it ; }

    constexpr auto && 
    get (list_iterator<auto> && it)
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