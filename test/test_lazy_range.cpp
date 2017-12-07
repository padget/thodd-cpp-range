#include <thodd/range.hpp>
#include <thodd/functional.hpp>
#include <vector>
#include <iostream>
#include <optional>

#include <cxxabi.h>





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
    /*auto annuaire = thodd::make_list( 
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
    
    auto toot = thodd::generate (
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

    auto input = thodd::make_string("un mot coupe") ;

    std::cout << "il me faut une fonction fasse du step par un délimiter\n" ;

    
    constexpr auto splitter_step = 
        [delimiter = ' '] (auto && begin_it, auto const & end_it)
        {
            auto predicate = 
                [delimiter] (auto && begin_it) 
                { return thodd::get(begin_it) != delimiter ; } ;

            thodd::next_while (predicate) (
                std::forward<decltype(begin_it)>(begin_it), 
                std::forward<decltype(end_it)>(end_it)) ;

            thodd::next_if (thodd::val(true)) (
                std::forward<decltype(begin_it)>(begin_it), 
                std::forward<decltype(end_it)>(end_it)) ;
        } ; 

    constexpr auto split = 
    [splitter_step] (auto && container) 
    {
        return 
        thodd::project (
            thodd::step (
                container, 
                splitter_step), 
            [] (auto && step_it) 
            {
                return 
                thodd::filter(
                    thodd::make_range (step_it.begin_it, step_it.it),
                        [] (auto && c) { return c != ' ' ; }) ; 
            }) ;
    } ;

    thodd::for_each(split(input), [] (auto && word) {
        std::cout << '"' ;
        thodd::for_each(word, [] (auto && c) {
            std::cout << c ;
        });
        std::cout << '"' << std::endl ;
    }) ;

    std::cout << "string" << std::endl ;
    auto str = thodd::make_string("coucou") ;
    thodd::for_each(
        str, [] (auto const & c) { std::cout << c << ' ' ; });
    std::cout << std::endl ;
    */

    int i = 1 ;

	thodd::if_exists (
		thodd::maybe_of(&i), 
		[] (auto && num) { std::cout << num << std::endl ;}) ; 
        
	thodd::if_exists (
		std::make_unique<int>(i), 
		[] (auto && num) { std::cout << num << std::endl ;}) ;

	thodd::for_each(
		thodd::make_list(1, 3, 5, 6, 4, 5, 58, 9), 
		[] (auto && item) { std::cout << item << std::endl ; }) ; 
}
