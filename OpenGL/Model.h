#pragma once

#include <vector>
#include "Vertex.h"
#include "Mesh.h"
#include "Transform.h"
#include "Shader.h"

class Model
{
public:
	Model( const std::string& filename )
		:
		mesh( filename )
	{}
	Model( const std::vector<Vertex>& vertices,
		const std::vector<unsigned int>& indices,
		const glm::vec3& color = glm::vec3{ 255.0f,0.0f,255.0f } )
		:
		mesh( vertices,indices,GenColorVec( color,vertices.size() ) )
	{}
	Model( const std::vector<Vertex>& vertices,
		const glm::vec3& color = glm::vec3{ 255.0f,0.0f,255.0f } )
		:
		mesh( vertices,GetDefaultIndices( vertices ),GenColorVec( color,vertices.size() ) )
	{}
	
	void Draw( Shader& shader ) const
	{
		shader.Update( xform );
		mesh.Draw();
	}
protected:
	std::vector<glm::vec3> GenColorVec( const glm::vec3& col,size_t nIndices )
	{
		std::vector<glm::vec3> colors;
		colors.reserve( nIndices );
		for( int i = 0; i < int( nIndices ); ++i )
		{
			colors.emplace_back( col );
		}
		return( colors );
	}
private:
	std::vector<unsigned int> GetDefaultIndices( const std::vector<Vertex>& vertices )
	{
		std::vector<unsigned int> indices;
		
		for( int i = 0; i < int( vertices.size() ); ++i )
		{
			indices.emplace_back( unsigned int( i ) );
		}
		
		return( indices );
	}
public:
	Transform xform;
	Mesh mesh;
};