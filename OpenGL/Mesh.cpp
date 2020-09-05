#include "Mesh.h"
#include <vector>

Mesh::Mesh( Vertex* vertices,int nVertices )
{
	drawCount = nVertices;

	glGenVertexArrays( 1,&vertexArrayObj );
	glBindVertexArray( vertexArrayObj );

	std::vector<glm::vec3> positions;
	std::vector<glm::vec2> texCoords;
	
	positions.reserve( nVertices );
	texCoords.reserve( nVertices );

	for( int i = 0; i < nVertices; ++i )
	{
		positions.emplace_back( vertices[i].pos );
		texCoords.emplace_back( vertices[i].texCoord );
	}

	glGenBuffers( NUM_BUFFERS,vertexArrayBuffers );
	glBindBuffer( GL_ARRAY_BUFFER,vertexArrayBuffers[POSITION_VB] );
	glBufferData( GL_ARRAY_BUFFER,nVertices * sizeof( positions[0] ),positions.data(),GL_STATIC_DRAW );

	glEnableVertexAttribArray( 0 );
	glVertexAttribPointer( 0,3,GL_FLOAT,GL_FALSE,0,0 );

	glBindBuffer( GL_ARRAY_BUFFER,vertexArrayBuffers[TEXCOORD_VB] );
	glBufferData( GL_ARRAY_BUFFER,nVertices * sizeof( texCoords[0] ),texCoords.data(),GL_STATIC_DRAW );

	glEnableVertexAttribArray( 1 );
	glVertexAttribPointer( 1,2,GL_FLOAT,GL_FALSE,0,0 );

	glBindVertexArray( 0 );
}

Mesh::~Mesh()
{
	glDeleteVertexArrays( 1,&vertexArrayObj );
}

void Mesh::Draw()
{
	glBindVertexArray( vertexArrayObj );

	glDrawArrays( GL_TRIANGLES,0,drawCount );

	glBindVertexArray( 0 );
}
