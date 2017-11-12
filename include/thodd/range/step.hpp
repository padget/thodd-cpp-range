#ifndef __THODD_RANGE_STEP_HPP__
#  define __THODD_RANGE_STEP_HPP__ 

namespace
thodd
{
    template <
        typename begin_t,
        typename end_t, 
        typename stepper_t>
    struct lazy_step_iterator 
    {
        begin_t begin_it ;
        begin_t it ;
        end_t end_it ;
        stepper_t stepper ;
        bool end_accessed { not_equals (it, end_it) } ;
    } ;

    template <
        typename begin_t,
        typename end_t, 
        typename stepper_t>
    lazy_step_iterator (begin_t, begin_t, end_t, stepper_t) -> lazy_step_iterator<begin_t, end_t, stepper_t> ;

    constexpr auto
    next (lazy_step_iterator<auto, auto, auto> & it)
    -> decltype(auto)
    { 
        it.begin_it = it.it ;
        
        if (not_equals(it.it, it.end_it))
            it.stepper(it.it, it.end_it) ; 
        else if (!it.end_accessed)
            it.end_accessed = true ;

        return it ;
    }

    constexpr auto
    next (lazy_step_iterator<auto, auto, auto> const & it)
    -> decltype(auto)
    { 
        it.begin_it = it.it ;
        
        if (not_equals(it.it, it.end_it))
            it.stepper(it.it, it.end_it) ;
        else if (!it.end_accessed)
            it.end_accessed = true ;

        return it ;
    }

    constexpr auto
    next (lazy_step_iterator<auto, auto, auto> && it)
    -> decltype(auto)
    { 
        it.begin_it = it.it ;
        
        if (not_equals(it.it, it.end_it))
            it.stepper(it.it, it.end_it) ;
        else if (!it.end_accessed)
            it.end_accessed = true ;

        return it ;
    }



    constexpr auto 
    get (lazy_step_iterator<auto, auto, auto> & it)
    -> decltype(auto)
    { return it ; }

    constexpr auto
    get (lazy_step_iterator<auto, auto, auto> const & it)
    -> decltype(auto)
    { return it ; }

    constexpr auto
    get (lazy_step_iterator<auto, auto, auto> && it)
    -> decltype(auto)
    { return it ; }



    constexpr bool
    not_equals (
        lazy_step_iterator<auto, auto, auto> const & lit, 
        lazy_step_iterator<auto, auto, auto> const & rit)
    { return not_equals(lit.it, rit.it) ; }



    inline constexpr auto 
    step = 
    [] (auto && container, auto && stepper) 
    {
        auto end_it = end(std::forward<decltype(container)>(container)) ;
        auto begin_it = begin(std::forward<decltype(container)>(container)) ;
        auto begin_step = lazy_step_iterator { begin_it, begin_it, end_it, std::forward<decltype(stepper)>(stepper)} ; 
        auto end_step = lazy_step_iterator { end_it, end_it, end_it, std::forward<decltype(stepper)>(stepper)} ; 
        
        std::cout << "step preparing ...\n" ; 
        next (begin_step) ;
        std::cout << "step prepared !\n" ;
        return 
        make_range (begin_step, end_step);
    } ;
}

#endif