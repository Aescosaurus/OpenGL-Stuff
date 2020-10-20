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

		const auto randPos = ground[Random::RangeI( 0,int( ground.size() ) )];
		temp.model->xform.pos = randPos.pos + glm::vec3{ 0.0f,height / 2.0f,0.0f };

		return( temp );
	}

	void Draw( Shader& shader ) const
	{
		model->Draw( shader );
	}
private:
	Tree()
		:
		model( std::make_unique<Cube>( glm::vec3{ girth,height,girth },glm::vec3{ 0.0f,1.0f,0.0f } ) )
	{}
private:
	static constexpr float girth = 0.3f;
	static constexpr float height = 1.0f;
	std::unique_ptr<Cube> model;
};