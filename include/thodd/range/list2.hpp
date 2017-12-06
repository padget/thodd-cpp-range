#ifndef __thodd_range_list2_hpp__
#  define __thodd_range_list2_hpp__

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
    else return maybe_of() ;
  }
}

namespace
thodd
{
  template <
    typename type_t>
  struct list
  {
    type_t item ;
    std::unique_ptr<list<type_t>> next ;
  } ;

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
  next (list_iterator<type_t> li)
  -> decltype(auto)
  {
    li.data = li.data != nullptr ? li.data.next : li.data ;
    return li ;
  }
  
  template <
    typename type_t>
  constexpr auto
  next (const_list_iterator<type_t> li)
  -> decltype(auto)
  {
    li.data = li.data != nullptr ? li.data.next : li.data ;
    return li ;
  }

  template <typename type_t>
  constexpr auto
  value_of (list_iterator<type_t> & li)
  { 
    return 
    maybe_if (
      li.data,  
      [] (auto * data) { return data != null ; }, 
      [] (auto * data) { return (data.item) ; }) ; 
  }
}

#endif