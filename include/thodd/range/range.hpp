#ifndef __THODD_RANGE_RANGE_HPP__
#  define __THODD_RANGE_RANGE_HPP__ 

namespace thodd 
{
    template <
        typename iterator_t>
    struct range 
    {
        iterator_t begin_it ;
        iterator_t end_it ;
    } ;

    template <typename iterator_t>
    range (iterator_t, iterator_t) -> range<iterator_t> ;

    
    constexpr auto
    make_range (
        auto && begin_it, 
        auto && end_it)
    {
        return 
        range {
            std::forward<decltype(begin_it)>(begin_it), 
            std::forward<decltype(end_it)>(end_it) } ; 
    }



    constexpr auto
    begin (thodd::range<auto> & lis)
    {
        return 
        lis.begin_it ;
    }

    constexpr auto const
    begin (thodd::range<auto> const & lis)
    {
        return 
        lis.begin_it ;
    }

    constexpr auto
    begin (thodd::range<auto> && lis)
    {
        return 
        lis.begin_it ;
    }

    

    constexpr auto
    end (thodd::range<auto> & lis)
    {
        return 
        lis.end_it ;
    }

    constexpr auto
    end (thodd::range<auto> const & lis)
    {
        return 
        lis.end_it ;
    }

    constexpr auto
    end (thodd::range<auto> && lis)
    {
        return 
        lis.end_it ;
    }
}


#endif