#pragma once

#include "Vertex.h"
#include <GL/glew.h>

class Mesh
{
public:
	Mesh( Vertex* vertices,int nVertices );
	Mesh( const Mesh& ) = delete;
	Mesh& operator=( const Mesh& ) = delete;
	~Mesh();

	void Draw();
private:
	enum
	{
		POSITION_VB,
		TEXCOORD_VB,

		NUM_BUFFERS
	};

	GLuint vertexArrayObj;
	GLuint vertexArrayBuffers[NUM_BUFFERS];
	int drawCount;
};