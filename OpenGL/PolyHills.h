#pragma once

#include "Plane.h"
#include "MapGenerator.h"

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
protected:
	std::vector<Vertex> GeneratePoints( int width,int height,int quality ) override
	{
		auto points = Plane::GeneratePoints( width,height,quality );

		const auto smooth = GenerateHeightMap( width * 2,height * 2,quality );
		assert( smooth.size() * 6 / 4 == points.size() );

		for( auto& p : points )
		{
			// const auto smoothLoc = p.pos + glm::vec3{ float( width ) / quality + 1.0f,float( height ) / quality + 1.0f,0.0f };
			const auto smoothLoc = glm::vec3{ p.pos.x + float( width ) / quality + 0.0f,
				p.pos.z + float( height ) / quality + 0.0f,
				0.0f };
			p.pos.y = smooth[int( smoothLoc.y ) * ( width / quality ) + int( smoothLoc.x )];
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

		cachedPoints = points;

		return( points );
	}
private:
	std::vector<float> GenerateHeightMap( int width,int height,int quality )
	{
		MapGenerator::SetDims( width,height,quality );

		typedef MapGenerator MG;
		
		return( MG::SmoothNoise() );
		// return( MG::Mountain() );
		// return( MG::Cells( 100,0.5f,1.0f ) );
		// return( MG::Combine( MG::Cells( 50,0.5f,0.8f ),MG::SmoothNoise(),
		// 	0.8f,0.8f ) );
		// return( MG::Combine( MG::Mountain( 10 ),MG::Cells(),
		// 	0.8f,1.0f ) );
		// return( MG::Combine( MG::Mountain(),MG::SmoothNoise(),
		// 	0.7f,1.0f ) );
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
		for( const auto& p : cachedPoints )
		{
			if( p.pos.y < min ) min = p.pos.y;
			if( p.pos.y > max ) max = p.pos.y;
		}

		if( min == max ) ++max;

		const auto grassCol = glm::vec3{ 84.0f,219.0f,84.0f } / 255.0f;
		const auto mountainCol = glm::vec3{ 156.0f,105.0f,32.0f } / 255.0f;

		colors.reserve( cachedPoints.size() );
		for( const auto& point : cachedPoints )
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
};