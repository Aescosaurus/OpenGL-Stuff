#pragma once

#include <vector>
#include "Vertex.h"
#include "Mesh.h"

class Model
{
public:
	Model( const std::vector<Vertex>& vertices,
		const std::vector<unsigned int>& indices )
		:
		vertices( vertices ),
		mesh( vertices,indices )
	{}
private:
	std::vector<Vertex> vertices;
	Mesh mesh;
};