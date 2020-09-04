#pragma once

#include <glm/glm.hpp>

class Vertex
{
public:
	Vertex( const glm::vec3& pos )
		:
		pos( pos )
	{}
	Vertex( float x,float y,float z )
		:
		pos( glm::vec3( x,y,z ) )
	{}
public:
	glm::vec3 pos;
};