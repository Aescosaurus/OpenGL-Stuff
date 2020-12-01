#pragma once

#include "Vertex.h"
#include <vector>
#include "Cube.h"
#include "Random.h"
#include <memory>
#include "Entity.h"

class Tree
	:
	public Entity
{
public:
	Tree( const std::vector<Vertex>& ground )
		:
		Entity( GenerateRandPos( ground ) + glm::vec3{ 0.0f,height / 2.0f,0.0f },
			glm::vec3{ girth,height,girth },glm::vec3{ 0.8f,0.2f,0.2f } )
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
};