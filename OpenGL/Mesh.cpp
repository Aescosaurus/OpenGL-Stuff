#include "Mesh.h"

Mesh::Mesh( Vertex* vertices,int nVertices )
{
	drawCount = nVertices;

	glGenVertexArrays( 1,&vertexArrayObj );
	glBindVertexArray( vertexArrayObj );

	glGenBuffers( NUM_BUFFERS,vertexArrayBuffers );
	glBindBuffer( GL_ARRAY_BUFFER,vertexArrayBuffers[POSITION_VB] );
	glBufferData( GL_ARRAY_BUFFER,nVertices * sizeof( vertices[0] ),
		vertices,GL_STATIC_DRAW );

	glEnableVertexAttribArray( 0 );
	glVertexAttribPointer( 0,3,GL_FLOAT,GL_FALSE,0,0 );

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
