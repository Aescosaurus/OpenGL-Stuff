#pragma once

#include <vector>

namespace aesc
{
	template<typename T>
	int vec_bytes( std::vector<T> vec )
	{
		return( int( vec.size() * sizeof( vec[0] ) ) );
	}
}