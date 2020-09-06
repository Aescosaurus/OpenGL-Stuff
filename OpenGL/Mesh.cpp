#include "Mesh.h"
#include <vector>

Mesh::Mesh( Vertex* vertices,int nVertices,
	unsigned int* indices,int nIndices )
{
	IndexedModel model;

	for( int i = 0; i < nVertices; ++i )
	{
		model.positions.emplace_back( vertices[i].pos );
		model.texCoords.emplace_back( vertices[i].texCoord );
	}

	for( int i = 0; i < nIndices; ++i )
	{
		model.indices.emplace_back( indices[i] );
	}

	InitMesh( model );
}

Mesh::Mesh( const std::string& filename )
{
	IndexedModel model = OBJModel{ filename }.ToIndexedModel();

	InitMesh( model );
}

Mesh::~Mesh()
{
	glDeleteVertexArrays( 1,&vertexArrayObj );
}

void Mesh::Draw()
{
	glBindVertexArray( vertexArrayObj );

	// glDrawArrays( GL_TRIANGLES,0,drawCount );
	glDrawElements( GL_TRIANGLES,drawCount,GL_UNSIGNED_INT,0 );

	glBindVertexArray( 0 );
}

void Mesh::InitMesh( const IndexedModel& model )
{
	drawCount = int( model.indices.size() );

	glGenVertexArrays( 1,&vertexArrayObj );
	glBindVertexArray( vertexArrayObj );

	glGenBuffers( NUM_BUFFERS,vertexArrayBuffers );
	glBindBuffer( GL_ARRAY_BUFFER,vertexArrayBuffers[POSITION_VB] );
	glBufferData( GL_ARRAY_BUFFER,model.positions.size() * sizeof( model.positions[0] ),model.positions.data(),GL_STATIC_DRAW );

	glEnableVertexAttribArray( 0 );
	glVertexAttribPointer( 0,3,GL_FLOAT,GL_FALSE,0,0 );

	glBindBuffer( GL_ARRAY_BUFFER,vertexArrayBuffers[TEXCOORD_VB] );
	glBufferData( GL_ARRAY_BUFFER,model.texCoords.size() * sizeof( model.texCoords[0] ),model.texCoords.data(),GL_STATIC_DRAW );

	glEnableVertexAttribArray( 1 );
	glVertexAttribPointer( 1,2,GL_FLOAT,GL_FALSE,0,0 );

	glBindBuffer( GL_ELEMENT_ARRAY_BUFFER,vertexArrayBuffers[INDEX_VB] );
	glBufferData( GL_ELEMENT_ARRAY_BUFFER,model.indices.size() * sizeof( model.indices[0] ),model.indices.data(),GL_STATIC_DRAW );

	glBindVertexArray( 0 );
}
