#include "Mesh.h"
#include "AescUtils.h"

Mesh::Mesh( const std::vector<Vertex>& vertices,
	const std::vector<unsigned int>& indices,
	const std::vector<glm::vec3>& colors )
{
	IndexedModel model;

	for( int i = 0; i < int( vertices.size() ); ++i )
	{
		model.positions.emplace_back( vertices[i].pos );
		model.texCoords.emplace_back( vertices[i].texCoord );
		model.normals.emplace_back( vertices[i].normal );
	}

	for( int i = 0; i < int( indices.size() ); ++i )
	{
		model.indices.emplace_back( indices[i] );
	}

	// Colors must be from 0-1 or else shaders break.
	for( const auto& c : colors )
	{
		assert( c.r >= 0.0f && c.r <= 1.0f );
		assert( c.g >= 0.0f && c.g <= 1.0f );
		assert( c.b >= 0.0f && c.b <= 1.0f );
	}

	InitMesh( model,colors );
}

Mesh::Mesh( const std::string& filename )
{
	IndexedModel model = OBJModel{ filename }.ToIndexedModel();

	InitMesh( model,{} );
}

Mesh::~Mesh()
{
	glDeleteVertexArrays( 1,&vertexArrayObj );
}

void Mesh::Draw() const
{
	glBindVertexArray( vertexArrayObj );

	// glDrawArrays( GL_TRIANGLES,0,drawCount );
	glDrawElements( GL_TRIANGLES,drawCount,GL_UNSIGNED_INT,0 );

	glBindVertexArray( 0 );
}

void Mesh::InitMesh( const IndexedModel& model,
	const std::vector<glm::vec3>& colors )
{
	// Pass as attribs to vertex shader.
	const auto bind_buffer_vertex = [&]( int bufferPos,int vb,const void* arr,int arrSize,int elSize )
	{
		glBindBuffer( GL_ARRAY_BUFFER,vertexArrayBuffers[vb] );
		glBufferData( GL_ARRAY_BUFFER,arrSize,arr,GL_STATIC_DRAW );
		glEnableVertexAttribArray( bufferPos );
		glVertexAttribPointer( bufferPos,elSize,GL_FLOAT,GL_FALSE,0,0 );
	};

	std::vector<glm::vec3> tempColors = colors;
	if( tempColors.size() < 1 )
	{
		tempColors.reserve( model.positions.size() );
		for( int i = 0; i < int( model.positions.size() ); ++i )
		{
			tempColors.emplace_back( defaultColor );
		}
	}

	drawCount = int( model.indices.size() );

	glGenVertexArrays( 1,&vertexArrayObj );
	glBindVertexArray( vertexArrayObj );

	glGenBuffers( NUM_BUFFERS,vertexArrayBuffers );

	bind_buffer_vertex( 0,POSITION_VB,model.positions.data(),aesc::vec_bytes( model.positions ),3 );
	bind_buffer_vertex( 1,TEXCOORD_VB,model.texCoords.data(),aesc::vec_bytes( model.texCoords ),2 );
	bind_buffer_vertex( 2,NORMAL_VB,model.normals.data(),aesc::vec_bytes( model.normals ),3 );
	bind_buffer_vertex( 3,COLOR_VB,tempColors.data(),aesc::vec_bytes( tempColors ),3 );

	glBindBuffer( GL_ELEMENT_ARRAY_BUFFER,vertexArrayBuffers[INDEX_VB] );
	glBufferData( GL_ELEMENT_ARRAY_BUFFER,model.indices.size() * sizeof( model.indices[0] ),model.indices.data(),GL_STATIC_DRAW );

	glBindVertexArray( 0 );
}
