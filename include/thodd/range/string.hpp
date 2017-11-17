#ifndef __THODD_RANGE_STRING_HPP__
#  define __THODD_RANGE_STRING_HPP__

#  include <string>

namespace 
thodd
{
    
    template <
        typename type_t>
    struct string
    {
        std::basic_string<type_t> data ;
    } ;

    template <
        typename type_t>
    struct string_iterator 
    {
        typename std::basic_string<type_t>::iterator it ; 
    } ;

    template < 
        typename type_t>
    constexpr auto 
    make_string (type_t const* data)
    { return string<type_t> { data } ; }

    constexpr auto 
    next (string_iterator<auto> & it)
    -> decltype(auto)
    { ++it.it ; return it ; }

    constexpr auto 
    next (string_iterator<auto> const & it)
    -> decltype(auto)
    { ++it.it ; return it ; }

    constexpr auto 
    next (string_iterator<auto> && it)
    -> decltype(auto)
    { ++it.it ; return it ; }

    constexpr auto 
    get (string_iterator<auto> & it)
    -> decltype(auto)
    {  return *it.it ; }

    constexpr auto 
    get (string_iterator<auto> const & it)
    -> decltype(auto)
    { return *it.it ; }

    constexpr auto 
    get (string_iterator<auto> && it)
    -> decltype(auto)
    { return *it.it ; }

    constexpr bool
    not_equals (
        string_iterator<auto> const & lit, 
        string_iterator<auto> const & rit)
    { return lit.it != rit.it ; }

        
    template <
        typename type_t>
    constexpr thodd::string_iterator<type_t> 
    begin (thodd::string<type_t> & lis)
    {
        return 
        thodd::string_iterator<type_t>
        { lis.data.begin() } ;
    }

    template <
        typename type_t>
    constexpr thodd::string_iterator<type_t> const 
    begin (thodd::string<type_t> const & lis)
    {
        return 
        thodd::string_iterator<type_t>
        { lis.data.begin() } ;
    }

    template <
        typename type_t>
    constexpr thodd::string_iterator<type_t> const 
    begin (thodd::string<type_t> && lis)
    {
        return 
        thodd::string_iterator<type_t>
        { lis.data.begin() } ;
    }

    template <
        typename type_t>
    constexpr thodd::string_iterator<type_t> 
    end (thodd::string<type_t> & lis)
    {
        return 
        thodd::string_iterator<type_t>
        { lis.data.end() } ;
    }

    template <
        typename type_t>
    constexpr thodd::string_iterator<type_t> const
    end (thodd::string<type_t> const & lis)
    {
        return 
        thodd::string_iterator<type_t>
        { lis.data.end() } ;
    }

    template <
        typename type_t>
    constexpr thodd::string_iterator<type_t> const
    end (thodd::string<type_t> && lis)
    {
        return 
        thodd::string_iterator<type_t>
        { lis.data.end() } ;
    }
}

#endif