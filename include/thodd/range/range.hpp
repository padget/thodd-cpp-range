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

        constexpr auto 
        begin () 
        {
            return 
            begin_it ;
        }
    
        constexpr auto
        begin () const 
        {
            return 
            begin_it ;
        }
    
        constexpr auto 
        end ()
        {
            return 
            end_it ;
        }
    
        constexpr auto
        end () const
        {
            return 
            end_it ;
        }
    } ;

    template <typename iterator_t>
    range (iterator_t, iterator_t) -> range<iterator_t> ;
    

    
}


#endif