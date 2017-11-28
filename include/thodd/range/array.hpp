#ifndef __THODD_RANGE_ARRAY_HPP__
#  define __THODD_RANGE_ARRAY_HPP__

#  include <utility>
#  include <array>

namespace 
thodd
{
  template <
    typename type_t, 
    size_t size_c>
  using array = std:array<type_t, size_c> ;



  constexpr auto
  make_array (auto && first, auto && ... item)
  {
    return 
    thodd::array<
      std::decay_t<decltype(first)>, 
      1 + sizeof...(item)>
    {
      { std::forward<decltype(first)>(first), 
        std::forward<decltype(item)>(item)... }
    } ;
  }


  constexpr auto 
  next (array_iterator<auto> & it)
  -> decltype(auto)
  { return (++ it.ptr, it) ; }

  constexpr auto 
  next (array_iterator<auto> const & it)
  -> decltype(auto)
  { return (++ it.ptr, it) ; }
  
  constexpr auto
  next (array_iterator<auto> && it)
  -> decltype(auto)
  { return (++ it.ptr, it) ; }


  constexpr auto
  get (typename array<auto>::iterator it)
  -> decltype(auto)
  { return *it.ptr ; }

  constexpr auto 
  get (typename array<auto>::const_iterator it)
  -> decltype(auto)
  { return *it.ptr ; }


  constexpr bool
  not_equals (
    typename array<auto>::iterator const & lit, 
    typename array<auto>::iterator const & rit)
  { return lit.ptr != rit.ptr ; }

  
  constexpr bool
  not_equals (
    typename array<auto>::const_iterator const & lit, 
    typename array<auto>::const_iterator const & rit)
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


  template <
    typename type_t,
    size_t size_c>
  constexpr auto
  size(thodd::array<type_t, size_c> const & arr)
  { return size_c ; }
}

#endif