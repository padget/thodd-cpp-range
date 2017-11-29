#ifndef __THODD_RANGE_FOREACH_HPP__
#  define __THODD_RANGE_FOREACH_HPP__

#  include <utility>

namespace
thodd 
{
    constexpr auto
    for_each (
        auto && container, 
        auto && todo)
    -> decltype(auto)
    {
        auto cursor = begin (std::forward<decltype(container)>(container)) ;
        auto const end_it = end (std::forward<decltype(container)>(container)) ;

        while (not_equals(cursor, end_it))
        {
            std::forward<decltype(todo)>(todo) (get(cursor)) ;
            next(cursor) ;
        }

        return 
        (container) ;
    }

    constexpr auto 
    for_eachi (
      auto && container, 
      auto && todo)
    {
      size_t index = 0u ; 
      return 
      thodd::for_each (
        std::forward<decltype(container)>(container), 
        [&index, &todo] (auto && item) 
        { todo(std::forward<decltype(item)>(item), index++) ; }) ;
    }

    constexpr auto 
    for_each_initially (
        auto && container, 
        auto && todo, 
        auto && initially)
    {
        std::forward<decltype(initially)>(initially)() ;

        for_each(
            std::forward<decltype(container)>(container),
            std::forward<decltype(todo)>(todo)) ;
    }

    constexpr auto 
    for_each_finally (
        auto && container, 
        auto && todo, 
        auto && finally)
    {
        for_each(
            std::forward<decltype(container)>(container),
            std::forward<decltype(todo)>(todo)) ;

        std::forward<decltype(finally)>(finally)() ;
    }

    constexpr auto 
    for_each_inifinally (
        auto && container, 
        auto && todo, 
        auto && initially,
        auto && finally)
    {
        std::forward<decltype(initially)>(initially)() ;

        for_each(
            std::forward<decltype(container)>(container),
            std::forward<decltype(todo)>(todo)) ;

        std::forward<decltype(finally)>(finally)() ;
    }
}

#endif