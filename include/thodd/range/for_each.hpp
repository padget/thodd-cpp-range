#ifndef __THODD_RANGE_FOREACH_HPP__
#  define __THODD_RANGE_FOREACH_HPP__

#  include <utility>

namespace
thodd 
{
	constexpr auto
	for_each (
		auto && container, 
		auto && todo)
	-> decltype(auto)
	{
		auto cursor = begin (std::forward<decltype(container)>(container)) ;
		auto const end_it = end (std::forward<decltype(container)>(container)) ;
		
		while (not_equals(cursor, end_it))
		{
			std::forward<decltype(todo)>(todo)(value_of(cursor)) ;
			next(cursor) ;
		}

		return 
		(container) ;
	}
}

#endif