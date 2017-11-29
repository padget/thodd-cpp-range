#ifndef __THODD_RANGE_COLLECTORS_HPP__
#  define __THODD_RANGE_COLLECTORS_HPP__

#  include <utility>
#  include <list>
#  include <vector>
#  include <map>
#  include <type_traits>

#  include <thodd/range/list.hpp>
#  include <thodd/range/map.hpp>

namespace
thodd 
{
    inline constexpr auto 
    to_map = 
    [] (auto && key_map, auto && value_map)
    {
        return 
        [key_map, value_map] (auto && container)
        {
            using key_t = std::decay_t<decltype(key_map(get(begin(container))))>;
            using value_t = std::decay_t<decltype(value_map(get(begin(container))))>;
            thodd::map<key_t, value_t> collected ;

            for_each (
                std::forward<decltype(container)>(container), 
                [key_map, value_map, &collected] (auto && item) 
                { push (collected, 
                        key_map(std::forward<decltype(item)>(item)), 
                        value_map(std::forward<decltype(item)>(item))) ; } ) ;

            return 
            collected ;
        } ;
    } ;

    inline constexpr auto 
    to_list = 
    [] (auto && container) 
    {
        thodd::list<typename std::decay_t<decltype(get(begin(container)))>> collected ;

        for_each (
            std::forward<decltype(container)>(container),
            [&collected] (auto && item) 
            { push_back (collected, std::forward<decltype(item)>(item)) ; }) ;
        
        return collected ;
    } ;

    inline constexpr auto 
    to_set = 
    [] (auto && container) 
    {
        thodd::set<typename std::decay_t<decltype(get(begin(container)))>> collected ;

        for_each (
            std::forward<decltype(container)>(container),
            [&collected] (auto && item) 
            { insert (collected, std::forward<decltype(item)>(item)) ; }) ;
        
        return collected ;
    } ;
}

#endif