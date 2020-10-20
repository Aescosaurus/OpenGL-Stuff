#pragma once

#include "Plane.h"

class PolyHills
	:
	public Plane
{
public:
	PolyHills( int width,int height )
		:
		// Funcs called in reverse order, need smooth noise for color heightmap.
		Plane( GenerateColors( width,height,quality ),
			GeneratePoints( width,height,quality ) )
	{}

	const std::vector<Vertex>& GetPoints()
	{
		return( points );
	}
protected:
	std::vector<Vertex> GeneratePoints( int width,int height,int quality )
	{
		auto points = Plane::GetPoints( width,height,quality );

		const auto smooth = GenerateSmoothNoiseMap( width * 2,height * 2,quality );

		for( auto& p : points )
		{
			// const auto smoothLoc = p.pos + glm::vec3{ float( width ) / quality + 1.0f,float( height ) / quality + 1.0f,0.0f };
			const auto smoothLoc = glm::vec3{ p.pos.x + float( width ) / quality + 1.0f,
				p.pos.z + float( height ) / quality + 1.0f,
				0.0f };
			p.pos.y = smooth[int( smoothLoc.y ) * ( width / quality ) + int( smoothLoc.x )] * steepness;
		}

		// Generate normals cuz lighting is hard.
		glm::vec3 curNorm = glm::vec3{ 0.0f,0.0f,0.0f };
		for( int i = 0; i < int( points.size() ); ++i )
		{
			if( i % 3 == 0 )
			{
				const auto& p1 = points[i + 0].pos;
				const auto& p2 = points[i + 1].pos;
				const auto& p3 = points[i + 2].pos;
				curNorm = glm::normalize( glm::cross( p2 - p1,p3 - p1 ) );
			}
			points[i].normal = curNorm;
		}

		this->points = points;

		return( points );
	}
private:
	std::vector<float> GenerateSmoothNoiseMap( int width,int height,int quality )
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

		constexpr float colorRng = 30.0f;

		// for( int y = 0; y < height / quality; ++y )
		// {
		// 	for( int x = 0; x < width / quality; ++x )
		// 	{
		// 		for( int i = 0; i < 6; ++i ) // 6 dupe vertices
		// 		{
		// 			// colors.emplace_back( glm::vec3{
		// 			// 	Random::Range( 190.0f,255.0f ),
		// 			// 	Random::Range( 190.0f,255.0f ),
		// 			// 	Random::Range( 0.0f,100.0f ) } );
		// 			colors.emplace_back( glm::vec3{
		// 				( 160.0f + Random::Range( -colorRng,colorRng ) ) / 255.0f,
		// 				( 110.0f + Random::Range( -colorRng,colorRng ) ) / 255.0f,
		// 				( 30.0f + Random::Range( -colorRng,colorRng ) ) / 255.0f } );
		// 		}
		// 	}
		// }

		float min = 999.0f;
		float max = -999.0f;
		for( const auto& p : points )
		{
			if( p.pos.y < min ) min = p.pos.y;
			if( p.pos.y > max ) max = p.pos.y;
		}

		const auto grassCol = glm::vec3{ 84.0f,219.0f,84.0f } / 255.0f;
		const auto mountainCol = glm::vec3{ 156.0f,105.0f,32.0f } / 255.0f;

		colors.reserve( points.size() );
		for( const auto& point : points )
		{
			// colors.emplace_back( glm::vec3{
			// 	( 160.0f + Random::Range( -colorRng,colorRng ) ) / 255.0f,
			// 	( 110.0f + Random::Range( -colorRng,colorRng ) ) / 255.0f,
			// 	( 30.0f + Random::Range( -colorRng,colorRng ) ) / 255.0f } );
			const float interp = ( point.pos.y - min ) / ( max - min );
			colors.emplace_back( glm::mix( grassCol,mountainCol,interp ) );
		}

		return( colors );
	}
private:
	static constexpr int quality = 2;
	// Hill height.
	static constexpr float steepness = 10.0f;
	// Random map smoothness.
	static constexpr int passes = 3;
	std::vector<Vertex> points;
};