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
        [] (auto && num) { std::cout << num << std::endl });

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
    
    thodd::for_each (sizes2, [] (auto && size) { std::cout << "size " << size << std::endl }) ;

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
        [] (auto && num) {std::cout << num << std::endl}) ;

    std::cout << "count_if pair " << thodd::count_if(nums2, onlypair) << std::endl ;

    std::cout << "collect " << std::endl ;
    thodd::for_each (
        thodd::collect(nums2, thodd::to_std_list), 
        [] (auto && num) { std::cout << num << std::endl ; }) ;

    std::cout << "map collect" << std::endl ;
    thodd::for_each (
        thodd::collect(nums2, thodd::to_std_map(thodd::$0, thodd::sum(thodd::$0, thodd::val(2)))), 
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
}