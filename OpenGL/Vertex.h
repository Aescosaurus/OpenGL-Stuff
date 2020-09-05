#pragma once

#include <glm/glm.hpp>

class Vertex
{
public:
	Vertex( const glm::vec3& pos,const glm::vec2& texCoord )
		:
		pos( pos ),
		texCoord( texCoord )
	{}
	Vertex( float x,float y,float z,float tx,float ty )
		:
		Vertex( glm::vec3{ x,y,z },glm::vec2{ tx,ty } )
	{}
public:
	glm::vec3 pos;
	glm::vec2 texCoord;
};