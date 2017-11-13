#ifndef __THODD_RANGE_GENERATE_HPP__
#  define __THODD_RANGE_GENERATE_HPP__

#  include <array>
#  include <algorithm>
#  include <utility>
#  include <type_traits>

namespace 
thodd
{
    template <
        size_t size_c, 
        typename type_t, 
        typename generator_t>
    struct generator_iterator 
    {
        std::array<type_t, size_c> previous ;
        generator_t generator ;
    } ;

    template <typename ender_t>
    struct generator_end_iterator 
    {
        ender_t ender ;
    } ;


    template<size_t size_c>
    constexpr auto 
    next (generator_iterator<size_c, auto, auto> & it)
    -> decltype(auto)
    { 
        std::rotate(
            it.previous.begin(), 
            it.previous.begin() + 1, 
            it.previous.end()) ;

        it.previous[size_c - 1] = 
            std::apply(
                [&it] (auto && ... previous) 
                { return it.generator (std::forward<decltype(previous)>(previous)...) ; },  it.previous) ;

        return it ;
    }

    template<size_t size_c>
    constexpr auto 
    next (generator_iterator<size_c, auto, auto> const & it)
    -> decltype(auto)
    { 
        std::rotate(
            it.previous.begin(), 
            it.previous.begin() + 1, 
            it.previous.end()) ;

        it.previous[size_c - 1] = 
            std::apply(
                [&it] (auto && ... previous) 
                { return it.generator (std::forward<decltype(previous)>(previous)...) ; },  it.previous) ;
      
        return it ;
    }

    template<size_t size_c>
    constexpr auto 
    next (generator_iterator<size_c, auto, auto> && it)
    -> decltype(auto)
    { 
        std::rotate(
            it.previous.begin(), 
            it.previous.begin() + 1, 
            it.previous.end()) ;

        it.previous[size_c - 1] = 
            std::apply(
                [&it] (auto && ... previous) 
                { return it.generator (std::forward<decltype(previous)>(previous)...) ; },  it.previous) ;
            
        return it ;
    }

    template<size_t size_c>
    constexpr auto 
    get (generator_iterator<size_c, auto, auto> & it)
    -> decltype(auto)
    {  return it.previous[size_c - 1] ; }

    template<size_t size_c>
    constexpr auto 
    get (generator_iterator<size_c, auto, auto> const & it)
    -> decltype(auto)
    { return it.previous[size_c - 1] ; }


    template<size_t size_c>
    constexpr auto 
    get (generator_iterator<size_c, auto, auto> && it)
    -> decltype(auto)
    { return it.previous[size_c - 1] ; }

    template<size_t size_c>
    constexpr bool
    not_equals (
        generator_iterator<size_c, auto, auto> const & lit, 
        generator_iterator<size_c, auto, auto> const & rit)
    { return lit.it != rit.it ; }

    template<size_t size_c>
    constexpr bool
    not_equals (
        generator_iterator<size_c, auto, auto> const & lit, 
        generator_end_iterator<auto> const & rit)
    { return std::apply(rit.ender, lit.previous) ; }


    constexpr auto
    generate (
        auto && generator, 
        auto && ender, 
        auto && initial, 
        auto && ... initials)
    {
        return 
        thodd::make_range (
            generator_iterator <
                sizeof...(initials) + 1, 
                std::decay_t<decltype(initial)>, 
                std::decay_t<decltype(generator)>> 
            { std::array{std::forward<decltype(initial)>(initial), std::forward<decltype(initials)>(initials)... }, std::forward<decltype(generator)>(generator) }, 
            generator_end_iterator <
                std::decay_t<decltype(ender)>>
            { std::forward<decltype(ender)>(ender) } ) ;
    
    }
}

#endif