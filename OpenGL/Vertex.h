#pragma once

#include <glm/glm.hpp>

// Represents a single vertex.
// TODO: Hold color in here?
class Vertex
{
public:
	Vertex() = default;
	constexpr Vertex( const glm::vec3& pos,const glm::vec2& texCoord = glm::vec2(),
		const glm::vec3& normal = glm::vec3{ 0.0f,0.0f,0.0f } )
		:
		pos( pos ),
		texCoord( texCoord ),
		normal( normal )
	{}
	constexpr Vertex( float x,float y,float z,float tx = 0.0f,float ty = 0.0f )
		:
		Vertex( glm::vec3{ x,y,z },glm::vec2{ tx,ty } )
	{}
public:
	glm::vec3 pos;
	glm::vec2 texCoord;
	glm::vec3 normal;
};