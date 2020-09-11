#pragma once

#include <vector>

namespace aesc
{
	// Give length of a vector in bytes.
	template<typename T>
	int vec_bytes( std::vector<T> vec )
	{
		return( int( vec.size() * sizeof( vec[0] ) ) );
	}
}