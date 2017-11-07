#ifndef __THODD_RANGE_FILTER_HPP__
#  define __THODD_RANGE_FILTER_HPP__

#  include <utility>
#  include <type_traits>

#  include <thodd/range/lazy_filter_iterator.hpp>
#  include <thodd/range/range.hpp>
#  include <thodd/functional.hpp>

namespace 
thodd 
{
    inline constexpr auto
    filter =  
    [] (auto && container, auto && predicate)
    {
        auto begin_filter = make_lazy_filter_iterator (begin(std::forward<decltype(container)>(container)), end(std::forward<decltype(container)>(container)), predicate) ;
        auto end_filter   = make_lazy_filter_iterator (end(std::forward<decltype(container)>(container)), end(std::forward<decltype(container)>(container)), predicate) ;
        
        return 
        range { begin_filter, end_filter } ;
    } ;


    inline constexpr auto 
    filters = 
    [] (auto && container, auto && ... predicates) 
    {
        return
        filter (
            std::forward<decltype(container)>(container), 
            and_(std::forward<decltype(predicates)>(predicates)...)) ;
    } ;
}

#endif