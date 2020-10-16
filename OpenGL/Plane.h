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
		Plane( GetPoints( width,height,quality ),
			GetColors( GetPoints( width,height,quality ) ) )
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
			colors )
	{}
protected:
	virtual std::vector<Vertex> GetPoints( int width,int height,int quality ) const
	{
		std::vector<Vertex> vertices;
		const auto hWidth = width / 2;
		const auto hHeight = height / 2;

		// todo utilize indices
		for( int y = -hHeight; y < hHeight; y += quality )
		{
			for( int x = -hWidth; x < hWidth; x += quality )
			{
				for( const auto& v : GenerateSimplePlane( x,y,quality ) )
				{
					vertices.emplace_back( v );
				}
			}
		}

		return( vertices );
	}
	std::vector<Vertex> GenerateSimplePlane( int x,int y,int size ) const
	{
		std::vector<Vertex> vertices;
		constexpr int pointOrder[] =
		{
			0,2,3,
			0,3,1
		};

		for( int i = 0; i < 6; ++i )
		{
			vertices.emplace_back( points[pointOrder[i]] );
			vertices.back().pos += glm::vec3{ float( x ),float( y ),0.0f };
		}

		return( vertices );
	}
	virtual std::vector<glm::vec3> GetColors( const std::vector<Vertex>& vertices ) const
	{
		std::vector<glm::vec3> colors;
		for( auto& v : vertices )
		{
			colors.emplace_back( glm::vec3{ Random::Range( 0.0f,255.0f ),
				Random::Range( 0.0f,255.0f ),Random::Range( 0.0f,255.0f ) } );
		}
		return( colors );
	}
private:
	static constexpr Vertex points[] =
	{
		Vertex{ -1.0f,1.0f,0.0f },
		Vertex{ 1.0f,1.0f,0.0f },
		Vertex{ -1.0f,-1.0f,0.0f },
		Vertex{ 1.0f,-1.0f,0.0f }
	};
};