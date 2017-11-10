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
        return 
        make_range(
            make_lazy_iterator(
                begin(std::forward<decltype(container)>(container)), 
                std::forward<decltype(projector)>(projector)), 
            make_lazy_iterator(
                end(std::forward<decltype(container)>(container)), 
                std::forward<decltype(projector)>(projector))) ; 
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