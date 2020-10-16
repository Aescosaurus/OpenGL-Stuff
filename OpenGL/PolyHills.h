#pragma once

#include "Plane.h"

class PolyHills
	:
	public Plane
{
public:
	PolyHills( int width,int height )
		:
		Plane( GetPoints( width,height,quality ),
			GenerateColors( width,height,quality ) )
	{}
protected:
	std::vector<Vertex> GetPoints( int width,int height,int quality ) const override
	{
		auto points = Plane::GetPoints( width,height,quality );

		const auto smooth = GenerateSmoothNoiseMap( width * 2,height * 2,quality );

		for( auto& p : points )
		{
			const auto smoothLoc = p.pos + glm::vec3{ float( width ) / quality + 1.0f,float( height ) / quality + 1.0f,0.0f };
			p.pos.z = smooth[int( smoothLoc.y ) * ( width / quality ) + int( smoothLoc.x )] * steepness;
		}

		return( points );
	}
private:
	std::vector<float> GenerateSmoothNoiseMap( int width,int height,int quality ) const
	{
		std::vector<float> noise;
		std::vector<float> smooth;

		auto check_tile = [&]( int x,int y )
		{
			if( x < 0 || x >= ( width / quality ) ||
				y < 0 || y >= ( width / quality ) )
			{
				return( 0.5f );
			}
			else
			{
				return( noise[y * ( width / quality ) + x] );
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
		for( int y = 0; y < height / quality; ++y )
		{
			for( int x = 0; x < width / quality; ++x )
			{
				noise.emplace_back( Random::Range( 0.0f,1.0f ) );
			}
		}

		smooth.resize( noise.size() );

		// Average elements for perlin noise type values.
		for( int i = 0; i < passes; ++i )
		{
			for( int y = 0; y < height / quality; ++y )
			{
				for( int x = 0; x < width / quality; ++x )
				{
					smooth[y * ( width / quality ) + x] = avg_3x3( x,y );
				}
			}
			noise = smooth;
		}

		return( smooth );
	}
	std::vector<glm::vec3> GenerateColors( int width,int height,int quality ) const
	{
		std::vector<glm::vec3> colors;

		for( int y = 0; y < height / quality * 6; ++y )
		{
			for( int x = 0; x < width / quality * 6; ++x )
			{
				// colors.emplace_back( glm::vec3{
				// 	Random::Range( 190.0f,255.0f ),
				// 	Random::Range( 190.0f,255.0f ),
				// 	Random::Range( 0.0f,100.0f ) } );
				colors.emplace_back( glm::vec3{ 160.0f,110.0f,30.0f } );
			}
		}

		return( colors );
	}
private:
	static constexpr int quality = 2;
	static constexpr float steepness = 7.0f;
	static constexpr int passes = 3;
};