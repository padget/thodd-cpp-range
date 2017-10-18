#ifndef __THODD_RANGE_SORT_HPP__
#  define __THODD_RANGE_SORT_HPP__

#  include <utility>
#  include <vector>
#  include <memory>

#  include <thodd/range/collect.hpp>
#  include <thodd/range/collectors.hpp>

namespace 
thodd
{
    template <
        typename iterator_t, 
        typename orderer_t>
    struct lazy_sort_iterator 
    {
        iterator_t it ; 
        iterator_t end_it ;
        orderer_t orderer ; 

        using value_type = typename decltype(it)::value_type ;

        lazy_sort_iterator(iterator_t begin, iterator_t end, orderer_t ord) :
            it (begin), 
            end_it (end), 
            orderer (ord) 
        {}

        lazy_sort_iterator(lazy_sort_iterator const &) = default ;
        lazy_sort_iterator(lazy_sort_iterator &&) = default ;
        ~lazy_sort_iterator() = default ;
        lazy_sort_iterator& operator = (lazy_sort_iterator const &) = default ;
        lazy_sort_iterator& operator = (lazy_sort_iterator &&) = default ;


        constexpr auto & operator ++ () { return (++it, *this) ; }
        constexpr auto const & operator ++ () const { return (++it, *this) ; }

        constexpr auto operator * () -> decltype(auto) { sort(); return *it ; }
        constexpr auto operator * () const -> decltype(auto) { sort(); return *it ; }

        constexpr auto operator != (lazy_sort_iterator const & other) const { return other.it != it ; }

    private:
        std::shared_ptr<std::vector<value_type>> sorted ;

        constexpr void 
        sort () 
        {
            if (!sorted) 
            {
                sorted.reset(new std::vector<value_type>(std::move(collect(range { it, end_it }, to_std_vector)))) ;
                std::sort(sorted->begin(), sorted->end(), orderer) ;   
                it = sorted->begin(); 
                end_it = sorted->end() ;
            }
        }
    } ;

    template <
        typename iterator_t, 
        typename orderer_t>
    lazy_sort_iterator (iterator_t, iterator_t, orderer_t) -> lazy_sort_iterator<iterator_t, orderer_t> ; 
    


    inline constexpr auto 
    sort = 
    [] (auto && container, auto && orderer)
    {   
        auto begin = std::forward<decltype(container)>(container).begin() ;
        auto end = std::forward<decltype(container)>(container).end() ;  

        return 
        range 
        { lazy_sort_iterator { begin, end, std::forward<decltype(orderer)>(orderer) }, 
          lazy_sort_iterator { end, end, std::forward<decltype(orderer)>(orderer) } } ;
    } ;
}

#endif