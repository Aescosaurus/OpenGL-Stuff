#pragma once

#include <vector>
#include "Vertex.h"
#include "Mesh.h"
#include "Transform.h"

class Model
{
public:
	Model( const std::string& filename )
		:
		mesh( filename )
	{}

	Model( const std::vector<Vertex>& vertices,
		const std::vector<unsigned int>& indices )
		:
		mesh( vertices,indices )
	{}
	Model( const std::vector<Vertex>& vertices )
		:
		mesh( vertices,GetDefaultIndices( vertices ) )
	{}
	
	void Draw()
	{
		mesh.Draw();
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
private:
	Mesh mesh;
};