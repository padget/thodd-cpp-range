#ifndef __THODD_RANGE_LAZY_FILTER_ITERATOR_HPP__
#  define __THODD_RANGE_LAZY_FILTER_ITERATOR_HPP__

#  include <type_traits>

namespace 
thodd 
{
    namespace detail
    {
        template <typename type_t>
        auto ref_or_value (type_t & t) -> type_t* 
        { return &t ; }

        template <typename type_t>
        auto ref_or_value (type_t const & t) -> type_t 
        { return t ; }
    }

    template <
        typename iterator_t, 
        typename predicate_t>
    struct lazy_filter_iterator 
    {
        iterator_t it ;  
        iterator_t end_it ;
        predicate_t predicate ;

        using value_type = std::decay_t<decltype(predicate(*it))> ;

        lazy_filter_iterator(iterator_t begin, iterator_t end, predicate_t pred) :
            it (begin), 
            end_it (end), 
            predicate (pred) 
        {
            if (it != end_it)
            {
                if constexpr (std::is_pointer_v<decltype(last_value)>)
                { if (!predicate(*(last_value = detail::ref_or_value(*it)))) ++ (*this) ; }
                else if (predicate(last_value = detail::ref_or_value(*it))) ++ (*this) ; 
            } 
        }

        lazy_filter_iterator(lazy_filter_iterator const &) = default ;
        lazy_filter_iterator(lazy_filter_iterator &&) = default ;
        ~lazy_filter_iterator() = default ;
        lazy_filter_iterator& operator = (lazy_filter_iterator const &) = default ;
        lazy_filter_iterator& operator = (lazy_filter_iterator &&) = default ;



        constexpr auto operator != (lazy_filter_iterator const & other) const { return other.it != it ; }

        constexpr auto & operator ++ () 
        { 
            while (it != end_it)
            {
                ++it ;

                if constexpr (std::is_pointer_v<decltype(last_value)>)
                { if (it != end_it && predicate(*(last_value = detail::ref_or_value(*it)))) break ; }
                else if (it != end_it && predicate(last_value = detail::ref_or_value(*it))) break ; 
            }

            return *this ;
        }

        constexpr auto const & operator ++ () const 
        { 
            while (it != end_it)
            {
                ++it ;

                if constexpr (std::is_pointer_v<decltype(last_value)>)
                { if (it != end_it && predicate(*(last_value = detail::ref_or_value(*it)))) break ; }
                else if (it != end_it && predicate(last_value = detail::ref_or_value(*it))) break ; 
            }

            return *this ;
        }
        
        // TODO faire la boucle retroactive
        constexpr auto & operator -- () 
        { 
            return (--it, *this) ; 
        }
        
        // TODO faire la boucle retroactive
        constexpr auto const & operator -- () const 
        { 
            return (--it, *this) ; 
        }

        constexpr auto operator * () 
        { 
            if constexpr (std::is_pointer_v<decltype(last_value)>)
                return *last_value ; 
            else return last_value ;
        }

        constexpr auto operator * () const 
        {        
            if constexpr (std::is_pointer_v<decltype(last_value)>)
                return *last_value ; 
            else return last_value ;
        }

    private:
        decltype(detail::ref_or_value(*it)) last_value ; 
    } ;

    constexpr auto
    make_lazy_filter_iterator (
        auto begin, auto end, auto predicate)
    {
        using iterator_t  = decltype(begin) ;
        using predicate_t = decltype(predicate) ;

        return lazy_filter_iterator<iterator_t, predicate_t> (begin, end, predicate) ;
    }
}

#endif