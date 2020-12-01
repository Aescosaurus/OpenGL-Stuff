#pragma once

#include <vector>
#include "Random.h"
#include <cassert>

class MapGenerator
{
public:
	// Steepness = hill height, passes = terrain smoothness.
	static std::vector<float> SmoothNoise( float steepness = 10.0f,int passes = 5 )
	{
		std::vector<float> noise;
		std::vector<float> smooth;

		auto check_tile = [&]( int x,int y )
		{
			if( x < 0 || x >= ( width ) ||
				y < 0 || y >= ( width ) )
			{
				return( 0.5f );
			}
			// else
			// if( x < 0 ) x = width - x;
			// if( x >= ( width / quality ) ) x -= ( width / quality );
			// if( y < 0 ) y = height - y;
			// if( y >= ( height / quality ) ) y -= ( height / quality );

			{
				return( noise[y * ( width ) + x] );
			}
		};
		auto avg_3x3 = [&]( int checkX,int checkY )
		{
			std::vector<float> avgs;
			avgs.reserve( 3 * 3 );
			for( int y = checkY - 1; y < checkY + 1; ++y )
			{
				for( int x = checkX - 1; x < checkX + 1; ++x )
				{
					avgs.emplace_back( check_tile( x,y ) );
				}
			}

			float total = 0.0f;
			for( const auto val : avgs ) total += val;
			total /= float( avgs.size() );

			return( total );
		};

		// Fill array with random elements.
		for( int y = 0; y < height; ++y )
		{
			for( int x = 0; x < width; ++x )
			{
				noise.emplace_back( Random::Range( 0.0f,1.0f ) );
			}
		}

		smooth.resize( noise.size() );

		// Average elements for perlin noise type values.
		for( int i = 0; i < passes; ++i )
		{
			// for( int y = 0; y < height / quality; ++y )
			// {
			// 	for( int x = 0; x < width / quality; ++x )
			// 	{
			// 		smooth[y * ( width / quality ) + x] = avg_3x3( x,y );
			// 	}
			// }
			for( int xy = 0; xy < ( height ) * ( width ); ++xy )
			{
				const auto randX = Random::RangeI( 0,width );
				const auto randY = Random::RangeI( 0,height );
				smooth[randY * ( width ) + randX] = avg_3x3( randX,randY );
			}

			noise = smooth;
		}

		for( auto& s : smooth )
		{
			s *= steepness;
		}

		return( smooth );
	}

	static std::vector<float> Cells( int generations = 100,float cellDensity = 0.5,float spikyness = 0.6 )
	{
		std::vector<float> heights;
		std::vector<int> cells;
		heights.reserve( width * height );
		cells.reserve( width * height );

		const auto get_cell = [&]( int x,int y )
		{
			if( x < 0 ) x = 0;
			if( x >= width ) x = width - 1;
			if( y < 0 ) y = 0;
			if( y >= height ) y = height - 1;

			return( y * width + x );
		};
		const auto count_neighs = [&]( int x,int y )
		{
			int n = 0;
			for( int yy = y - 1; yy < y + 2; ++yy )
			{
				for( int xx = x - 1; xx < x + 2; ++xx )
				{
					if( cells[get_cell( x,y )] > 0 ) ++n;
				}
			}
			return( n );
		};

		for( int i = 0; i < width * height; ++i )
		{
			cells.emplace_back( Random::Range( 0.0f,1.0f ) < cellDensity ? 1 : 0 );
		}

		for( int i = 0; i < generations; ++i )
		{
			for( int y = 0; y < height; ++y )
			{
				for( int x = 0; x < width; ++x )
				{
					auto& curCell = cells[y * width + x];
					if( curCell > 0 )
					{
						const auto neighs = count_neighs( x,y );
						if( neighs > 4 )
						{
							curCell = neighs - 3;
						}
						else if( neighs < 4 )
						{
							curCell = 0;
						}
					}
				}
			}
		}
		
		for( auto& c : cells )
		{
			heights.emplace_back( float( c ) * spikyness );
		}

		return( heights );
	}

	static std::vector<float> Mountain( int radius = 20 )
	{
		std::vector<float> heights;
		heights.reserve( width * height );

		const auto radSq = radius * radius;
		const auto xCenter = width / 2;
		const auto yCenter = height / 2;

		const auto maxLen = float( std::sqrt( xCenter * xCenter + yCenter * yCenter ) );

		for( int y = 0; y < height; ++y )
		{
			for( int x = 0; x < width; ++x )
			{
				heights.emplace_back( 0.0f );
				
				const auto xDiff = x - xCenter;
				const auto yDiff = y - yCenter;
				const auto lenSq = float( xDiff * xDiff + yDiff * yDiff );
				// if( lenSq < radSq )
				{
					heights.back() = maxLen - std::sqrt( lenSq );
				}
			}
		}

		return( heights );
	}

	static std::vector<float> Combine( const std::vector<float>& map1,
		const std::vector<float>& map2,
		float weight1 = 1.0f,float weight2 = 1.0f )
	{
		assert( map1.size() == map2.size() );

		std::vector<float> result;
		result.reserve( map1.size() );

		for( int i = 0; i < int( map1.size() ); ++i )
		{
			result.emplace_back( map1[i] * weight1 + map2[i] * weight2 );
		}

		return( result );
	}

	static void SetDims( int width,int height,int quality );
private:
	static int width;
	static int height;
};