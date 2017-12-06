#ifndef __thodd_range_list2_hpp__
#  define __thodd_range_list2_hpp__

#  include <type_traits>
#  include <utility>
#  include <memory>

namespace 
thodd
{
  template <typename type_t>
  struct maybe 
  {
    type_t* data { nullptr } ;
  } ;

  template <typename type_t>
  constexpr auto 
  maybe_of (type_t * data) 
  { return maybe<type_t> { data } ; }


  template <typename type_t>
  constexpr auto 
  maybe_of () 
  { return maybe<type_t> {} ; }


  constexpr auto 
  maybe_if (
    auto && something, 
    auto && predicate, 
    auto && transform)
  -> decltype(auto)
  {
    if (std::forward<decltype(predicate)>(predicate)(std::forward<decltype(something)>(something)))
      return maybe_of(std::forward<decltype(transform)>(transform)(std::forward<decltype(something)>(something))) ;
    else 
      return maybe_of<std::decay_t<decltype(std::forward<decltype(transform)>(transform)(std::forward<decltype(something)>(something)))>>() ;
  }


  constexpr bool
  has_value (maybe<auto> const & mb) 
  { return mb.data != nullptr ; }


  constexpr auto 
  value_of (maybe<auto> & mb)
  -> decltype(auto)
  { return *mb.data ; }

  constexpr auto 
  value_of (maybe<auto> const & mb)
  -> decltype(auto)
  { return *mb.data ; }

  constexpr auto 
  value_of (maybe<auto> && mb)
  -> decltype(auto)
  { return *mb.data ; }


  if_exists (
    maybe<auto> & mb,
    auto && todo)
  {
    if (has_value (mb)) 
      std::forward<decltype(todo)>(todo)(value_of(mb)) ; 
  }

  if_exists (
    maybe<auto> const & mb,
    auto && todo)
  {
    if (has_value (mb)) 
      std::forward<decltype(todo)>(todo)(value_of(mb)) ; 
  }

  if_exists (
    maybe<auto> && mb,
    auto && todo)
  {
    if (has_value (mb)) 
      std::forward<decltype(todo)>(todo)(value_of(mb)) ; 
  }
}

namespace 
thodd
{
  constexpr bool
  has_value (std::unique_ptr<auto> const & u) 
  { return (bool) u ; }


  constexpr auto 
  value_of (std::unique_ptr<auto> & u)
  -> decltype(auto)
  { return *u ; }

  constexpr auto 
  value_of (std::unique_ptr<auto> const & u)
  -> decltype(auto)
  { return *u ; }

  constexpr auto 
  value_of (std::unique_ptr<auto> && u)
  -> decltype(auto)
  { return *u ; }


  if_exists (
    std::unique_ptr<auto> & u,
    auto && todo)
  {
    if (has_value (u)) 
      std::forward<decltype(todo)>(todo) (value_of(u)) ; 
  }

  if_exists (
    std::unique_ptr<auto> const & u,
    auto && todo)
  {
    if (has_value (u)) 
      std::forward<decltype(todo)>(todo) (value_of(u)) ; 
  }

  if_exists (
    std::unique_ptr<auto> && u,
    auto && todo)
  {
    if (has_value (u)) 
      std::forward<decltype(todo)>(todo) (value_of(u)) ; 
  }

  if_not_exists (
    std::unique_ptr<auto> & u,
    auto && todo)
  {
    if (!has_value (u)) 
      std::forward<decltype(todo)>(todo) (u) ; 
  }

  if_not_exists (
    std::unique_ptr<auto> const & u,
    auto && todo)
  {
    if (!has_value (u)) 
      std::forward<decltype(todo)>(todo) (u) ; 
  }

  if_not_exists (
    std::unique_ptr<auto> && u,
    auto && todo)
  {
    if (!has_value (u)) 
      std::forward<decltype(todo)>(todo) (u) ; 
  }
}

namespace
thodd
{
  template <
    typename type_t>
  struct list
  {
    std::unique_ptr<type_t> item ;
    std::unique_ptr<list<type_t>> next ;
    thodd::maybe<list<type_t>> last ;
  } ;

  template <
    typename type_t>
  inline auto 
  make_list () 
  { return list<type_t> {} ; }


  make_list (auto && first, auto && ... next) 
  {
    
    constexpr auto push_back = 
    [] (auto & li, auto && item) 
    {
      using type_t = std::decay_t<decltype(item)> ;

      auto * cursor = &li ;
      
      while (has_value(cursor->item) && has_value (cursor->next))
        cursor = cursor->next.get() ;

      cursor->item.reset(new type_t { std::forward<decltype(item)>(item) }) ;
      cursor->next.reset(new list<type_t>{}) ;
    } ;

    auto l = make_list<std::decay_t<decltype(first)>>() ;



    return l ; 
  }

  template <
    typename type_t>
  struct list_iterator
  {
    list<type_t> * data ;
  } ;

  template <
    typename type_t>
  struct list_const_iterator
  {
    list<type_t> const * data ;
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
  { return list_iterator<type_t> { nullptr } ; }

  template <
    typename type_t>
  constexpr auto
  next (list_iterator<type_t> li)
  -> decltype(auto)
  {
    li.data = li.data != nullptr ? li.data.next : li.data ;
    return li ;
  }
    
  template <
    typename type_t>
  constexpr auto
  value_of (list_iterator<type_t> li)
  { 
    return 
    maybe_if (
      li.data,  
      [] (auto * data) { return data != nullptr ; }, 
      [] (auto * data) -> decltype(auto) { return (data.item) ; }) ; 
  }
  
  

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
    li.data = li.data != nullptr ? li.data.next : li.data ;
    return li ;
  }

  template <
    typename type_t>
  constexpr auto
  value_of (list_const_iterator<type_t> li)
  { 
    return 
    maybe_if (
      li.data,  
      [] (auto * data) { return data != nullptr ; }, 
      [] (auto * data) -> decltype(auto) { return (data.item) ; }) ; 
  }

  not_equals (
    list_iterator<auto> const & l, 
    list_iterator<auto> const & r)
  {
    return
    l.data != r.data ;
  }
}

#endif