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
  { return array_iterator<type_t> { &a.data } ; }

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
  next (array_iterator<type_t> ai)
  -> decltype(auto)
  {
    ++ai.data ;
    return ai ;
  }
    
  template <
    typename type_t>
  constexpr auto
  value_of (array_iterator<type_t> ai)
  { return *ai.data ; }

  not_equals (
    array_iterator<auto> const & l, 
    array_iterator<auto> const & r)
  { return l.data != r.data ; }
  /*
  
  template <
    typename type_t>
  struct list_const_iterator
  {
    list<type_t> const * data ;
  } ;

  template <
    typename type_t>
  constexpr auto 
  begin (list<type_t> const & l)
  -> decltype(auto)
  { return list_const_iterator<type_t> { &l } ; }

  template <
    typename type_t>
  constexpr auto 
  end (list<type_t> const & l)
  -> decltype(auto)
  { return list_const_iterator<type_t> { nullptr } ; }

  template <
    typename type_t>
  constexpr auto
  next (list_const_iterator<type_t> li)
  -> decltype(auto)
  {
    li.data = (li.data != nullptr && has_value(li.data->next->item)) ? li.data->next.get() : nullptr ; 
    return li ;
  }

  template <
    typename type_t>
  constexpr auto
  value_of (list_const_iterator<type_t> li)
  -> decltype(auto)
  { return *li.data->item ; }

  not_equals (
    list_const_iterator<auto> const & l, 
    list_const_iterator<auto> const & r)
  { return l.data != r.data ; } */
}

#endif