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
  struct array 
  {
    type_t data[size_c] ;
  } ;

  template <
    size_t sizel_c, 
    size_t sizer_c>
  constexpr auto
  copy (
    array<auto, sizel_c> const & l, 
    array<auto, sizer_c> & r)
    -> decltype(r)
  {
    static_assert (sizel_c < sizer_c) ;

    for (auto i = 0u ; i < sizel_c ; ++i)
      r.data[i] = l.data[i] ;

    return r ;
  }

  template <
    size_t sizel_c, 
    size_t sizer_c>
  constexpr auto
  copy (
    array<auto, sizel_c> && l, 
    array<auto, sizer_c> & r)
    -> decltype(r)
  {
    static_assert (sizel_c < sizer_c) ;

    for (auto i = 0u ; i < sizel_c ; ++i)
      r.data[i] = std::move(l.data[i]) ;

    return r ;
  }

  template <
    typename type_t, 
    size_t size_c>
  constexpr auto 
  push_back (
    array<type_t, size_c> const & a, 
    auto && item)
  {
    array<type_t, size_c + 1> res {} ;
    copy(a, res).data[size_c] = std::forward<decltype(item)>(item) ;

    return res ;
  }

  template <
    typename type_t, 
    size_t size_c>
  constexpr auto 
  push_back (
    array<type_t, size_c> && a, 
    auto && item)
  {
    array<type_t, size_c + 1> res {} ;
    copy(a, res).data[size_c] = std::forward<decltype(item)>(item) ;
    
    return res ;
  }

  constexpr auto
  make_array (
    auto && first, 
    auto && ... item)
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

  template <
    typename type_t>
  struct array_iterator
  {
    type_t * data { nullptr };
  } ;


  template <
    typename type_t, 
    size_t size_c>
  constexpr auto 
  begin (array<type_t, size_c> & a)
  -> decltype(auto)
  { return array_iterator<type_t> { a.data } ; }

  template <
    typename type_t, 
    size_t size_c>
  constexpr auto 
  end (array<type_t, size_c> & a)
  -> decltype(auto)
  { return array_iterator<type_t> { a.data + size_c } ; }

  template <
    typename type_t>
  constexpr auto
  next (array_iterator<type_t> & ai)
  { ++ai.data ; }
    
  template <
    typename type_t>
  constexpr auto
  value_of (array_iterator<type_t> & ai)
  -> decltype(auto)
  { return *ai.data ; }

  template <
    typename type_t>
  constexpr auto
  value_of (array_iterator<type_t> const & ai)
  -> decltype(auto)
  { return *ai.data ; }

  constexpr bool
  not_equals (
    array_iterator<auto> const & l, 
    array_iterator<auto> const & r)
  { return l.data != r.data ; }
  
  
  template <
    typename type_t>
  struct array_const_iterator
  {
    type_t const * data { nullptr };
  } ;

  template <
    typename type_t, 
    size_t size_c>
  constexpr auto 
  begin (array<type_t, size_c> const & a)
  -> decltype(auto)
  { return array_const_iterator<type_t> { a.data } ; }

  template <
    typename type_t, 
    size_t size_c>
  constexpr auto 
  end (array<type_t, size_c> const & a)
  -> decltype(auto)
  { return array_const_iterator<type_t> { a.data + size_c } ; }

  template <
    typename type_t>
  constexpr auto
  next (array_const_iterator<type_t> & ai)
  { ++ai.data ; }
    
  template <
    typename type_t>
  constexpr auto
  value_of (array_const_iterator<type_t> & ai)
  -> decltype(auto)
  { return *ai.data ; }

  template <
    typename type_t>
  constexpr auto
  value_of (array_const_iterator<type_t> const & ai)
  -> decltype(auto)
  { return *ai.data ; }

  constexpr bool
  not_equals (
    array_const_iterator<auto> const & l, 
    array_const_iterator<auto> const & r)
  { return l.data != r.data ; }
}

#endif