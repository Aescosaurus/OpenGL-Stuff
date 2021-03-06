#pragma once

#include "Model.h"
#include <cassert>
#include "Random.h"

class Plane
	:
	public Model
{
public:
	// Quality = distance between points, must be multiple of width and height.
	// todo fix getpoints nonsense
	Plane( int width,int height,int quality )
		:
		// Model( GetPoints( width,height,quality ),
		// Model::GetDefaultIndices( GetPoints( width,height,quality ) ),
		// GetColors( GetPoints( width,height,quality ) ) )
		Plane( GeneratePoints( width,height,quality ),
			GetColors( GeneratePoints( width,height,quality ) ) )
	{
		assert( quality < width );
		assert( quality < height );
		assert( width % quality == 0 );
		assert( height % quality == 0 );
	}
	Plane( const std::vector<Vertex>& points,
		const std::vector<glm::vec3>& colors )
		:
		Model( points,
			Model::GetDefaultIndices( points ),
			colors ),
		cachedPoints( points )
	{}
	// Weird initialization order stuff.
	Plane( const std::vector<glm::vec3>& colors,
		const std::vector<Vertex>& points )
		:
		Plane( points,colors )
	{}
	const std::vector<Vertex>& GetPoints()
	{
		return( cachedPoints );
	}
protected:
	virtual std::vector<Vertex> GeneratePoints( int width,int height,int quality )
	{
		std::vector<Vertex> vertices;
		const auto hWidth = width / 2;
		const auto hHeight = height / 2;

		// todo utilize indices
		for( int y = 0; y < height; y += quality )
		{
			for( int x = 0; x < width; x += quality )
			{
				for( const auto& v : GenerateSimplePlane( x,y,quality ) )
				{
					vertices.emplace_back( v );
					vertices.back().normal = glm::normalize( glm::vec3{ 0.0f,1.0f,0.0f } );
				}
			}
		}

		return( vertices );
	}
	std::vector<Vertex> GenerateSimplePlane( int x,int y,int size ) const
	{
		std::vector<Vertex> vertices;
		// constexpr int pointOrder[] =
		// {
		// 	0,2,3,
		// 	0,3,1
		// };
		constexpr int pointOrder[] =
		{
			0,3,2,
			0,1,3
		};

		for( int i = 0; i < 6; ++i )
		{
			vertices.emplace_back( points[pointOrder[i]] );
			vertices.back().pos += glm::vec3{ float( x ),0.0f,float( y ), };
		}

		return( vertices );
	}
	virtual std::vector<glm::vec3> GetColors( const std::vector<Vertex>& vertices ) const
	{
		std::vector<glm::vec3> colors;
		for( auto& v : vertices )
		{
			colors.emplace_back( glm::vec3{
				Random::Range( 0.0f,1.0f ),
				Random::Range( 0.0f,1.0f ),
				Random::Range( 0.0f,1.0f )
				} );
		}
		return( colors );
	}
protected:
	std::vector<Vertex> cachedPoints = std::vector<Vertex>{};
private:
	static constexpr Vertex points[] =
	{
		Vertex{ -1.0f,0.0f,1.0f },
		Vertex{ 1.0f,0.0f,1.0f },
		Vertex{ -1.0f,0.0f,-1.0f },
		Vertex{ 1.0f,0.0f,-1.0f }
	};
};