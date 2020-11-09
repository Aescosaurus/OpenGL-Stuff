#pragma once

#include "Vertex.h"
#include <vector>
#include "Cube.h"
#include "Random.h"
#include <memory>

class Tree
{
public:
	// Generate a tree at a random location at ground level.
	static Tree Generate( const std::vector<Vertex>& ground )
	{
		Tree temp;

		// const auto randPos = ground[Random::RangeI( 0,int( ground.size() ) )];
		// temp.model->xform.pos = randPos.pos + glm::vec3{ 0.0f,height / 2.0f,0.0f };

		std::vector<glm::vec3> posList;
		auto randIndex = Random::RangeI( 3,int( ground.size() ) );
		while( randIndex % 3 != 0 ) --randIndex;
		for( int i = 0; i < 3; ++i ) posList.emplace_back( ground[randIndex++].pos );

		auto tempPos = glm::mix( posList[0],posList[1],0.5f );
		tempPos = glm::mix( tempPos,posList[2],0.5f );

		temp.model->xform.pos = tempPos + glm::vec3{ 0.0f,height / 2.0f,0.0f };

		return( temp );
	}

	void Draw( Shader& shader ) const
	{
		model->Draw( shader );
	}
private:
	Tree()
		:
		model( std::make_unique<Cube>( glm::vec3{ girth,height,girth },RandColor() ) )
	{}

	glm::vec3 RandColor()
	{
		return( glm::vec3{ Random::Range( 0.0f,0.1f ),
			Random::Range( 0.7f,0.96f ),
			Random::Range( 0.05f,0.3f ) } );
	}
private:
	static constexpr float girth = 0.3f;
	static constexpr float height = 1.0f;
	std::unique_ptr<Cube> model;
};