#ifndef __THODD_RANGE_PROJECTOR_HPP__
#  define __THODD_RANGE_PROJECTOR_HPP__

#  include <utility>

#  include <thodd/range/range.hpp>
#  include <thodd/range/lazy_iterator.hpp>

#  include <thodd/functional.hpp>

namespace 
thodd 
{
    inline constexpr auto 
    project = 
    [] (auto && container, auto && projector)
    { 
        return range 
        { lazy_iterator {std::forward<decltype(container)>(container).begin(), projector }, 
          lazy_iterator {std::forward<decltype(container)>(container).end(), projector } } ; 
    } ;

    inline constexpr auto 
    projects = 
    [] (auto && container, auto && ... projector)
    {
        return
        project (
            std::forward<decltype(container)>(container), 
            compose(std::forward<decltype(projector)>(projector)...)) ;
    } ;
}

#endif