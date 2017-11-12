#include <thodd/range.hpp>
#include <thodd/functional.hpp>
#include <vector>
#include <iostream>
#include <optional>

#include <cxxabi.h>


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
            { return it.generator (previous...) ; },  it.previous) ;

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
            { return it.generator (previous...) ; },  it.previous) ;
  
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
            { return it.generator (previous...) ; },  it.previous) ;
        
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
generate (auto && generator, auto && ender, auto && initial, auto && ... initials)
{
    return 
    thodd::make_range (
        generator_iterator <
            sizeof...(initials) + 1, 
            std::decay_t<decltype(initial)>, 
            std::decay_t<decltype(generator)>> 
        { std::array{initial, initials... }, generator }, 
        generator_end_iterator <
            std::decay_t<decltype(ender)>>
        { ender } ) ;
 
}


template<
    typename T>
std::string type_name()
{
    int status;
    std::string tname = typeid(T).name();
    char *demangled_name = abi::__cxa_demangle(tname.c_str(), NULL, NULL, &status);
    
    if(status == 0) 
    {
        tname = demangled_name;
        std::free(demangled_name);
    } 

    return tname;
}


struct address 
{
    int numero ;
    std::string rue ;  
} ;

struct person
{
    std::string prenom, nom ; 
    address addr ;
} ;

int main()
{
    auto annuaire = thodd::make_list( 
        person { "george", "washinton", { 2, "rue des champignon" } } , 
        person { "denzel", "washinton", { 5, "rue des purée" } } ) ;
        

    thodd::for_each(
        thodd::project(
            annuaire, 
            [] (auto && p) -> decltype(auto) { return p.addr.rue ; }), 
        [] (auto && rue) { std::cout << rue << std::endl ; }) ;
    
    std::cout << "filters" << std::endl ;
    auto nums = thodd::make_list(0, 1, 2, 3, 4, 5, 6) ;
    thodd::for_each(
        thodd::filter (nums, [] (auto && num) { return num % 2 == 0 ; } ),
        [] (auto && num) { std::cout << 'c' << num << std::endl ; }) ;

    std::cout << "sizes" << std::endl ;

    auto sizes = 
        thodd::filter(
            thodd::project(
                thodd::project(
                    thodd::project(
                        annuaire, 
                        [] (auto && person) { return person.addr ; }), 
                    [] (auto && addr) { return addr.rue ; }), 
                [] (auto && rue) { return rue.size() ; }), 
            [] (auto && size) { return size > 10 ; }) ;
    
    thodd::for_each (
        sizes, 
        [](auto && size) { std::cout << "size " << size << std::endl ; }) ;
        

    auto sum = thodd::reduce (sizes, 0, [] (auto acc, auto item) { return acc + item ; });
    std::cout << "sum " << sum << std::endl ;

    std::cout << "sizes2" << std::endl ;

    auto sizes2 = 
        thodd::filter(
            thodd::projects (
                annuaire, 
                [] (auto && person) { return person.addr ; }, 
                [] (auto && addr) { return addr.rue ; }, 
                [] (auto && rue) { return rue.size() ; }),
            [] (auto && size) { return size > 10 ; });
    
    thodd::for_each (sizes2, [] (auto && size) { std::cout << "size " << size << std::endl ; }) ;

    auto sum2 = thodd::reduce (sizes2, 0, [] (auto acc, auto item) { return acc + item ; });
    std::cout << sum2 << std::endl ;

    std::cout << "count " << thodd::count (sizes2, 18) << std::endl ;
    std::cout << "count " << thodd::count_if (sizes2, thodd::equal(thodd::val(1), thodd::$0)) << std::endl ;

    auto nums2 = thodd::make_array(0, 1, 2, 3, 4, 5, 6, 7, 8, 9) ;
    
    constexpr auto onlypair = [] (auto && item) { return item % 2 == 0 ; } ;
    constexpr auto threeless = [] (auto && item) { return item <= 3 ; } ;

    std::cout << "filters" << std::endl ;

    thodd::for_each (
        thodd::filters(nums2, threeless, onlypair), 
        [] (auto && num) {std::cout << num << std::endl ; }) ;

    std::cout << "count_if pair " << thodd::count_if(nums2, onlypair) << std::endl ;

    std::cout << "collect " << std::endl ;
    thodd::for_each (
        thodd::collect(nums2, thodd::to_list), 
        [] (auto && num) { std::cout << num << std::endl ; }) ;

    std::cout << "map collect" << std::endl ;
    thodd::for_each (
        thodd::collect(nums2, thodd::to_map(thodd::$0, thodd::sum(thodd::$0, thodd::val(2)))), 
        [] (auto && pair) { std::cout << pair.first << ' ' << pair.second << '\n' ; }) ;
        

    std::cout << "find_first" << std::endl ;
    thodd::if_exists(
        thodd::find_first(
            nums2, 
            [](auto const & item) { return item == 2 ;}), 
        [] (auto const & item) { std::cout << item << std::endl ; }) ;
    
    std::cout << "array + arrayiterator + for_each \n" ;
    thodd::for_each(
        thodd::for_each(
            thodd::make_array(1, 2, 3, 4, 5, 6, 7, 8, 9), 
            [] (auto && n) { n++ ; }),
        [] (auto && n) { std::cout << n << std::endl ; }) ;

    std::cout << "list + list_iterator + for_each \n" ;
    thodd::for_each(
        thodd::for_each(
            thodd::make_list(1, 2, 3, 4, 5, 6, 7, 8, 9), 
            [] (auto && n) { n++ ; }),
        thodd::lshift(thodd::ref(std::cout), thodd::$0)) ;

    std::cout << "\nmap + map_iterator + for_each \n" ;
    thodd::map<int, int> m {{std::pair {1,2}}} ;
    thodd::push(m, 2, 2);
    thodd::push(m, 3, 2);
    thodd::push(m, 4, 2);

    thodd::for_each(m, [](auto && kv) {std::cout << kv.second << std::endl ; });


    std::cout << "generate\n" ;
    
    auto toot = generate (
        [](auto && n_1) { return n_1 + 1 ; }, 
        [](auto && n_n) { return n_n < 10 ; }, 0) ;

    thodd::for_each (toot, [](auto && item) { std::cout << item << std::endl ; }) ;

    std::cout << "set" << std::endl ;
    auto oneset = thodd::make_set(1, 2, 3, 4, 4, 5, 5, 5, 6, 7, 8, 9) ;
    thodd::for_each(oneset, [] (auto && item) { std::cout << item << std::endl ; } ) ;

    std::cout << "step" << std::endl ;
    thodd::for_each(
        thodd::step (
            oneset, 
            [] (auto && it, auto && end_it) -> decltype(auto) 
            { 
                if(thodd::not_equals(it, end_it))
                    next(it) ;
                
                if(thodd::not_equals(it, end_it))
                    next(it) ;

                return it ;
             }),
        [] (auto && item) { std::cout << thodd::get(item.it) << std::endl ; }) ;

    std::cout << "steps" << std::endl ;
    std::cout << "prototype of split string function by a delimiter char\n" ;

    auto input = thodd::make_array('u','n',' ','m','o','t',' ','c','o','u','p','e') ;

    std::cout << "il me faut une fonction fasse du step par un délimiter\n" ;
    constexpr auto advance_while = 
    [] (auto && predicate) 
        {
            return 
            [predicate] (auto && it, auto const & end_it) 
            {
                while (thodd::not_equals (it, end_it) && predicate (it))
                {
                    std::cout << "step " << thodd::get(it) << std::endl ;
                    thodd::next (it) ;
                    std::cout << "end_step " << thodd::get(it) << std::endl ;
                }
            } ;
        } ;

    constexpr auto advance_if = 
    [] (auto && predicate) 
    {
        return 
        [predicate] (auto && it, auto const & end_it) 
        {
            if (thodd::not_equals (it, end_it) && predicate (it))
                thodd::next (it) ;
        } ;
    } ;
    
    constexpr auto splitter_step = 
        [delimiter = ' '] (auto && begin_it, auto && end_it)
        {
            auto predicate = 
                [delimiter] (auto && begin_it) 
                { return thodd::get(begin_it) != delimiter ; } ;
            advance_while (predicate) (
                std::forward<decltype(begin_it)>(begin_it), 
                std::forward<decltype(end_it)>(end_it)) ;
            advance_if (thodd::val(true)) (
                std::forward<decltype(begin_it)>(begin_it), 
                std::forward<decltype(end_it)>(end_it)) ;
        } ; 

    thodd::for_each (
        thodd::step (input, splitter_step), 
        [] (auto && step_it) {
            std::cout << "resultat [" 
                      << thodd::get(step_it.begin_it) 
                      << '-' 
                      << thodd::get(step_it.it) 
                      << '[' << std::endl ;
            thodd::for_each (
                thodd::make_range (step_it.begin_it, step_it.it),
                [] (auto && c) { std::cout << c ; }) ; 
            std::cout << std::endl ; }) ;
    
}
