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
    to_std_list = 
    [] (auto && container)
    {
        std::list<typename decltype(std::forward<decltype(container)>(container).begin())::value_type> collected ;

        for (auto && item : std::forward<decltype(container)>(container))
            collected.push_back (std::forward<decltype(item)>(item)) ;

        return 
        collected ;
    } ;

    inline constexpr auto 
    to_std_vector = 
    [] (auto && container)
    {
        std::vector<typename std::decay_t<decltype(std::forward<decltype(container)>(container).begin())>::value_type> collected ;

        for (auto && item : std::forward<decltype(container)>(container))
            collected.push_back (std::forward<decltype(item)>(item)) ;

        return 
        collected ;
    } ;

    inline constexpr auto
    to_std_map = 
    [] (auto && key_map, auto && value_map)
    {
        return 
        [key_map, value_map] (auto && container)
        {
            using key_t = std::decay_t<decltype(key_map(*container.begin()))>;
            using value_t = std::decay_t<decltype(value_map(*container.begin()))>;
            std::map<key_t, value_t> collected ;

            for (auto && item : std::forward<decltype(container)>(container)) 
                collected[key_map(item)] = value_map(item) ;

            return 
            collected ;
        } ;
    } ;

    inline constexpr auto 
    to_map = 
    [] (auto && key_map, auto && value_map)
    {
        return 
        [key_map, value_map] (auto && container)
        {
            using key_t = std::decay_t<decltype(key_map(*container.begin()))>;
            using value_t = std::decay_t<decltype(value_map(*container.begin()))>;
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
        thodd::list<typename std::decay_t<decltype(container)>::value_type> collected ;

        for_each (
            std::forward<decltype(container)>(container),
            [&collected] (auto && item) 
            { push_back (collected, std::forward<decltype(item)>(item)) ; }) ;
        
        return collected ;
    } ;
}

#endif