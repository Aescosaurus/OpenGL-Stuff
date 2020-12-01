#pragma once

#include "Vertex.h"
#include <vector>
#include "Cube.h"
#include "Random.h"
#include <memory>
#include <algorithm>

#undef max

class Entity
{
public:
	virtual void Update( float dt )
	{

	}

	virtual void Draw( Shader& shader ) const
	{
		model->Draw( shader );
	}

	glm::vec3& GetPos()
	{
		return( model->xform.pos );
	}
protected:
	Entity( const glm::vec3& pos,const glm::vec3& scale,const glm::vec3& color )
		:
		model( std::make_unique<Cube>( scale,color ) )
	{
		model->xform.pos = pos;
	}

	// returns normal of triangle that contains pos
	// glm::vec3 GetNormal( const glm::vec3& pos ) const
	// {
	// 
	// }

	// returns triangle height at pos
	float GetHeight( const glm::vec3& pos,const std::vector<Vertex>& ground,int worldSize ) const
	{
		auto get_vertex = [&]( int x,int y )
		{
			// this is not getting the right pos from xy
			// x += worldSize / 2 + 1;
			// y += worldSize / 2 + 1;
			// return( noise[y * worldSize + x] );

			// this is super inefficient try to make the other one work
			for( const auto& v : ground )
			{
				if( abs( v.pos.x - x ) < 2 &&
					abs( v.pos.z - y ) < 2 )
				{
					return( v.pos.y );
				}
			}

			return( 0.0f );
		};

		const auto bl = get_vertex( int( floor( pos.x ) ),int( floor( pos.z ) ) );
		const auto br = get_vertex( int( ceil( pos.x ) ),int( floor( pos.z ) ) );
		const auto tl = get_vertex( int( floor( pos.x ) ),int( ceil( pos.z ) ) );
		const auto tr = get_vertex( int( ceil( pos.x ) ),int( ceil( pos.z ) ) );

		const float xPercent = pos.x - floor( pos.x );
		const float yPercent = pos.y - floor( pos.y );

		const auto lMix = glm::mix( tl,bl,yPercent );
		const auto rMix = glm::mix( tr,br,yPercent );
		const auto tMix = glm::mix( tl,tr,xPercent );
		const auto bMix = glm::mix( bl,br,xPercent );

		// const float result = ( lMix + rMix + tMix + bMix ) / 4.0f;
		const float result = std::max( std::max( std::max( tl,tr ),bl ),br );

		return( result );
	}

	static glm::vec3 GenerateRandPos( const std::vector<Vertex>& ground )
	{
		std::vector<glm::vec3> posList;
		auto randIndex = Random::RangeI( 3,int( ground.size() ) );
		while( randIndex % 3 != 0 ) --randIndex;
		for( int i = 0; i < 3; ++i ) posList.emplace_back( ground[randIndex++].pos );

		auto tempPos = glm::mix( posList[0],posList[1],0.5f );
		tempPos = glm::mix( tempPos,posList[2],0.5f );

		// temp.model->xform.pos = tempPos + glm::vec3{ 0.0f,height / 2.0f,0.0f };
		return( tempPos );
	}
private:
	std::unique_ptr<Cube> model;
};