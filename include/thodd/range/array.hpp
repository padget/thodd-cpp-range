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
  next (typename array<auto>::iterator & it)
  -> decltype(auto)
  { return ++it ; }

  constexpr auto 
  next (typename array<auto>::const_iterator & it)
  -> decltype(auto)
  { return ++it ; }
  
  constexpr auto 
  next (typename array<auto>::iterator && it)
  -> decltype(auto)
  { return ++it ; }

  constexpr auto 
  next (typename array<auto>::const_iterator && it)
  -> decltype(auto)
  { return ++it ; }
  

  constexpr auto
  get (typename array<auto>::iterator & it)
  -> decltype(auto)
  { return *it.ptr ; }

  constexpr auto 
  get (typename array<auto>::const_iterator & it)
  -> decltype(auto)
  { return *it.ptr ; }

  constexpr auto
  get (typename array<auto>::iterator && it)
  -> decltype(auto)
  { return *it.ptr ; }

  constexpr auto 
  get (typename array<auto>::const_iterator && it)
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
  constexpr auto
  begin (array<type_t, size_c> & arr)
  -> decltype(auto)
  {
    return 
    arr.begin() ;
  }

  template <
    typename type_t,
    size_t size_c>
  constexpr auto 
  begin (array<type_t, size_c> const & arr)
  -> decltype(auto)
  {
    return 
    arr.begin() ;
  }
  
  template <
    typename type_t,
    size_t size_c>
  constexpr auto 
  begin (array<type_t, size_c> && arr)
  -> decltype(auto)
  {
    return 
    arr.begin() ;
  }

  

  template <
    typename type_t,
    size_t size_c>
  constexpr auto 
  end (array<type_t, size_c> & arr)
  -> decltype(auto)
  {
    return 
    arr.end() ;
  }

  template <
    typename type_t,
    size_t size_c>
  constexpr auto
  end (array<type_t, size_c> const & arr)
  -> decltype(auto)
  {
    return 
    arr.end() ;
  }
  
  template <
    typename type_t,
    size_t size_c>
  constexpr auto
  end (thodd::array<type_t, size_c> && arr)
  {
    return 
    arr.end() ;
  }


  template <
    typename type_t,
    size_t size_c>
  constexpr auto
  size(array<type_t, size_c> const &)
  { return size_c ; }
}

#endif