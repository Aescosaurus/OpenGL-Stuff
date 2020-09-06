#pragma once

#include "Vertex.h"
#include <GL/glew.h>
#include "obj_loader.h"

class Mesh
{
public:
	Mesh( Vertex* vertices,int nVertices,
		unsigned int* indices,int nIndices );
	Mesh( const std::string& filename );

	Mesh( const Mesh& ) = delete;
	Mesh& operator=( const Mesh& ) = delete;
	~Mesh();

	void Draw();
private:
	void InitMesh( const IndexedModel& model );
private:
	enum
	{
		POSITION_VB,
		TEXCOORD_VB,

		INDEX_VB,

		NUM_BUFFERS
	};

	GLuint vertexArrayObj;
	GLuint vertexArrayBuffers[NUM_BUFFERS];
	int drawCount;
};