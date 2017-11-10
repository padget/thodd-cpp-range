#ifndef __THODD_RANGE_RANGE_HPP__
#  define __THODD_RANGE_RANGE_HPP__ 

#  include <utility>
#  include <type_traits>

namespace thodd 
{
    template <
        typename begin_t, 
        typename end_t >
    struct range 
    {
        begin_t begin_it ;
        end_t end_it ;
    } ;

    
    constexpr auto
    make_range (
        auto && begin_it, 
        auto && end_it)
    {
        return 
        range <
            std::decay_t<decltype(begin_it)>, 
            std::decay_t<decltype(end_it)>> 
        { std::forward<decltype(begin_it)>(begin_it), 
          std::forward<decltype(end_it)>(end_it) } ; 
    }



    constexpr auto
    begin (thodd::range<auto, auto> & lis)
    { return lis.begin_it ; }

    constexpr auto const
    begin (thodd::range<auto, auto> const & lis)
    { return lis.begin_it ; }

    constexpr auto
    begin (thodd::range<auto, auto> && lis)
    { return lis.begin_it ; }

    

    constexpr auto
    end (thodd::range<auto, auto> & lis)
    { return lis.end_it ; }

    constexpr auto
    end (thodd::range<auto, auto> const & lis)
    { return lis.end_it ; }

    constexpr auto
    end (thodd::range<auto, auto> && lis)
    { return lis.end_it ; }
}


#endif