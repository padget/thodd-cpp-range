#ifndef __THODD_RANGE_ARRAY_HPP__
#  define __THODD_RANGE_ARRAY_HPP__

#  include <utility>

namespace 
thodd
{

    template <
        typename type_t, 
        size_t size_c>
    struct array
    {
        type_t data[size_c];
    } ;

    template <
        typename type_t>
    struct array_iterator
    {
        mutable type_t* ptr { nullptr } ; 
    } ;


    constexpr auto
    make_array (auto && first, auto && ... item)
    {
        return 
        thodd::array<
            std::decay_t<decltype(first)>, 
            1 + sizeof...(item)>
        {
            std::forward<decltype(first)>(first), 
            std::forward<decltype(item)>(item)...
        } ;
    }

  
    constexpr array_iterator<auto> & 
    next (array_iterator<auto> & it)
    { return (++ it.ptr, it) ; }

    constexpr array_iterator<auto> const & 
    next (array_iterator<auto> const & it)
    { return (++ it.ptr, it) ; }
    
    constexpr array_iterator<auto> && 
    next (array_iterator<auto> && it)
    { return (++ it.ptr, it) ; }

    constexpr auto & 
    get (array_iterator<auto> & it)
    { return *it.ptr ; }

    constexpr auto const & 
    get (array_iterator<auto> const & it)
    { return *it.ptr ; }
    
    constexpr auto && 
    get (array_iterator<auto> && it)
    { return *it.ptr ; }

    constexpr bool
    not_equals (
        array_iterator<auto> const & lit, 
        array_iterator<auto> const & rit)
    { return lit.ptr != rit.ptr ; }

    
    template <
        typename type_t,
        size_t size_c>
    constexpr thodd::array_iterator<type_t> 
    begin (thodd::array<type_t, size_c> & arr)
    {
        return 
        thodd::array_iterator<type_t>
        { arr.data } ;
    }

    template <
        typename type_t,
        size_t size_c>
    constexpr thodd::array_iterator<type_t> const 
    begin (thodd::array<type_t, size_c> const & arr)
    {
        return 
        thodd::array_iterator<type_t>
        { arr.data } ;
    }
    
    template <
        typename type_t,
        size_t size_c>
    constexpr thodd::array_iterator<type_t> const 
    begin (thodd::array<type_t, size_c> && arr)
    {
        return 
        thodd::array_iterator<type_t>
        { arr.data } ;
    }

    

    template <
        typename type_t,
        size_t size_c>
    constexpr thodd::array_iterator<type_t> 
    end (thodd::array<type_t, size_c> & arr)
    {
        return 
        thodd::array_iterator<type_t>
        { arr.data + size_c } ;
    }

    template <
        typename type_t,
        size_t size_c>
    constexpr thodd::array_iterator<type_t> const
    end (thodd::array<type_t, size_c> const & arr)
    {
        return 
        thodd::array_iterator<type_t>
        { arr.data + size_c } ;
    }
    
    template <
        typename type_t,
        size_t size_c>
    constexpr thodd::array_iterator<type_t> const
    end (thodd::array<type_t, size_c> && arr)
    {
        return 
        thodd::array_iterator<type_t>
        { arr.data + size_c } ;
    }
}

#endif