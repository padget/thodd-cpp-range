#ifndef __THODD_RANGE_STRING_HPP__
#  define __THODD_RANGE_STRING_HPP__

#  include <string>
#  include <algorithm>

namespace 
thodd
{
  template <
    typename char_t>
  struct string 
  {
    std::basic_string<char_t> str ;
  } ;

  template <typename char_t>
  constexpr auto 
  make_string (
    const char_t * chrs)
  {
    return 
    thodd::string<char_t> { chrs } ;
  }

  template <
    typename type_t>
  struct string_iterator
  {
    size_t idx { -1u } ;
    thodd::string<type_t> * data { nullptr } ; 
  } ;


  template <
    typename type_t>
  constexpr auto 
  begin (string<type_t> & l)
  -> decltype(auto)
  { return string_iterator<type_t> { 0u, &l } ; }

  template <
    typename type_t>
  constexpr auto 
  end (string<type_t> & l)
  -> decltype(auto)
  { return string_iterator<type_t> { -1u, &l } ; }

  template <
    typename type_t>
  constexpr auto
  next (string_iterator<type_t> & si)
  -> decltype(si)
  {
    si.idx = si.idx < si.data->str.size() ? si.idx + 1u : -1u ;
    return (si) ;
  }

  template <
    typename type_t>
  constexpr auto
  value_of (string_iterator<type_t> & li)
  -> decltype((li.data->str[li.idx]))
  { return (li.data->str[li.idx]) ; }

  template <
    typename type_t>
  constexpr auto
  value_of (string_iterator<type_t> const & li)
  -> decltype((li.data->str[li.idx]))
  { return (li.data->str[li.idx]) ; }

  constexpr auto
  not_equals (
    string_iterator<auto> const & l, 
    string_iterator<auto> const & r)
  { return l.idx != r.idx ; }



  template <
    typename type_t>
  struct string_const_iterator
  {
    size_t idx { -1u } ;
    thodd::string<type_t> const * data { nullptr } ; 
  } ;


    template <
    typename type_t>
  constexpr auto 
  begin (string<type_t> const & l)
  -> decltype(auto)
  { return string_const_iterator<type_t> { 0u, &l } ; }

  template <
    typename type_t>
  constexpr auto 
  end (string<type_t> const & l)
  -> decltype(auto)
  { return string_const_iterator<type_t> { -1u, &l } ; }

  template <
    typename type_t>
  constexpr auto
  next (string_const_iterator<type_t> & si)
  -> decltype(si)
  {
    si.idx = si.idx < si.data->str.size() ? si.idx + 1u : -1u ;
    return (si) ;
  }
    
  template <
    typename type_t>
  constexpr auto
  value_of (string_const_iterator<type_t> & li)
  -> decltype((li.data->str[li.idx]))
  { return (li.data->str[li.idx]) ; }

  template <
    typename type_t>
  constexpr auto
  value_of (string_const_iterator<type_t> const & li)
  -> decltype((li.data->str[li.idx]))
  { return (li.data->str[li.idx]) ; }

  constexpr auto
  not_equals (
    string_const_iterator<auto> const & l, 
    string_const_iterator<auto> const & r)
  { return l.idx != r.idx ; }
}

#endif