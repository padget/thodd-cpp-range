#ifndef __THODD_RANGE_STEP_HPP__
#  define __THODD_RANGE_STEP_HPP__ 

namespace
thodd
{
    template <
        typename iterator_t, 
        typename stepper_t>
    struct lazy_step_iterator 
    {
        iterator_t begin_it ;
        iterator_t it ;
        stepper_t stepper ;

        using value_type = std::decay_t<decltype(stepper(*it))> ;

        constexpr auto & operator ++ () { return (++it, *this) ; }
        constexpr auto const & operator ++ () const { return (++it, *this) ; }

        constexpr auto operator * () -> decltype(auto) { return stepper(*it) ; }
        constexpr auto operator * () const -> decltype(auto) { return stepper(*it) ; }

        constexpr auto operator != (lazy_iterator const & other) const { return other.it != it ; }
    } ;

    template <typename iterator_t, typename stepper_t>
    lazy_iterator (iterator_t, iterator_t, stepper_t) -> lazy_iterator<iterator_t, stepper_t> ;

    inline constexpr auto 
    step = 
    [] (auto && container, auto && stepper) 
    {
        auto end = std::forward<decltype(container)>(container).end() ;
        auto begin = std::forward<decltype(container)>(container).begin() ;
        auto begin_step = lazy_step_iterator { begin, begin, std::forward<decltype(stepper)>(stepper)} ; 
        auto end_step = lazy_step_iterator { end, end, std::forward<decltype(stepper)>(stepper)} ; 
        return 
        range 
        { begin_step, end_step } ;
    } ;
}

#endif