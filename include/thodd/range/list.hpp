#ifndef __thodd_range_list2_hpp__
#  define __thodd_range_list2_hpp__

#  include <type_traits>
#  include <utility>
#  include <memory>
#  include <iostream>
#  include <thodd/optional.hpp>

namespace
thodd
{
  template <
    typename type_t>
  struct list
  {
    std::unique_ptr<type_t> item ;
    std::unique_ptr<list<type_t>> next ;
  } ;

  template <
    typename type_t>
  inline auto 
  make_list () 
  { return list<type_t> {} ; }

  template <
    typename type_t>
  inline auto 
  push_back (
    list<type_t> & li, 
    auto && item) 
  -> list<type_t> &
  {
    auto * cursor = &li ;
    
    while (has_value(cursor->item) && has_value (cursor->next))
      cursor = cursor->next.get() ;

    cursor->item.reset(new type_t { std::forward<decltype(item)>(item) }) ;
    cursor->next.reset(new list<type_t>{}) ;

    return li ;
  } ;

  inline auto
  make_list (auto && first, auto && ... next) 
  -> list<std::decay_t<decltype(first)>>
  {
    auto l = make_list<std::decay_t<decltype(first)>>() ;
    (push_back(l, first), (push_back(l, next), ...)) ;

    return l;
  }

  template <
    typename type_t>
  struct list_iterator
  {
    list<type_t> * data { nullptr } ;
  } ;


  template <
    typename type_t>
  constexpr auto 
  begin (list<type_t> & l)
  -> decltype(auto)
  { return list_iterator<type_t> { &l } ; }

  template <
    typename type_t>
  constexpr auto 
  end (list<type_t> & l)
  -> decltype(auto)
  { return list_iterator<type_t> { } ; }

  template <
    typename type_t>
  constexpr auto
  next (list_iterator<type_t> & li)
  {
    li.data = (li.data != nullptr && has_value(li.data->next->item)) ? li.data->next.get() : nullptr ;
  }
    
  template <
    typename type_t>
  constexpr auto
  value_of (list_iterator<type_t> & li)
  { return *li.data->item ; }

  not_equals (
    list_iterator<auto> const & l, 
    list_iterator<auto> const & r)
  { return l.data != r.data ; }
  
  
  template <
    typename type_t>
  struct list_const_iterator
  {
    list<type_t> const * data { nullptr } ;
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
  next (list_const_iterator<type_t> & li)
  {
    li.data = (li.data != nullptr && has_value(li.data->next->item)) ? li.data->next.get() : nullptr ; 
  }

  template <
    typename type_t>
  constexpr auto
  value_of (list_const_iterator<type_t> & li)
  -> decltype(auto)
  { return *li.data->item ; }

  not_equals (
    list_const_iterator<auto> const & l, 
    list_const_iterator<auto> const & r)
  { return l.data != r.data ; }
}

#endif