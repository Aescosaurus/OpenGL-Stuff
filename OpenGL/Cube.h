#pragma once

#include "Model.h"
#include <cassert>

class Cube
	:
	public Model
{
public:
	Cube( const glm::vec3& scale = glm::vec3{ 1.0f,1.0f,1.0f },
		const glm::vec3& color = glm::vec3{ 255.0f,0.0f,255.0f } )
		:
		Model( GetPoints( scale ),color )
	{}
private:
	std::vector<Vertex> GetPoints( const glm::vec3& scale )
	{
		assert( scale.x >= 0.0f );
		assert( scale.y >= 0.0f );
		assert( scale.z >= 0.0f );

		std::vector<Vertex> vertices;

		constexpr auto zero = glm::vec2{ 0.0f,0.0f };
		constexpr auto one = glm::vec2{ 1.0f,1.0f };
		constexpr auto up = glm::vec2{ 0.0f,0.0f };
		constexpr auto down = glm::vec2{ 0.0f,1.0f };
		constexpr auto left = glm::vec2{ 0.0f,0.0f };
		constexpr auto right = glm::vec2{ 1.0f,0.0f };
		constexpr auto ul = up + left;
		constexpr auto ur = up + right;
		constexpr auto dl = down + left;
		constexpr auto dr = down + right;

		constexpr int mappings[] =
		{
			// front
			0,2,3,
			0,3,1,
			// right
			1,3,7,
			1,7,5,
			// left
			4,6,2,
			4,2,0,
			// back
			5,7,6,
			5,6,4,
			// top
			4,0,1,
			4,1,5,
			// bot
			2,6,7,
			2,7,3
		};

		constexpr glm::vec2 texCoords[] =
		{
			ul,dl,dr,
			ul,dr,ur,

			ul,dl,dr,
			ul,dr,ur,

			ul,dl,dr,
			ul,dr,ur,

			ul,dl,dr,
			ul,dr,ur,

			ul,dl,dr,
			ul,dr,ur,

			ul,dl,dr,
			ul,dr,ur
		};

		constexpr glm::vec3 normals[] =
		{
			glm::vec3{ 0.0f,0.0f,1.0f },
			glm::vec3{ 1.0f,0.0f,0.0f },
			glm::vec3{ -1.0f,0.0f,0.0f },
			glm::vec3{ 0.0f,0.0f,-1.0f },
			glm::vec3{ 0.0f,1.0f,0.0f },
			glm::vec3{ 0.0f,-1.0f,0.0f }
		};

		vertices.resize( sizeof( mappings ) / sizeof( mappings[0] ) );
		for( int i = 0; i < sizeof( mappings ) / sizeof( mappings[0] ); ++i )
		{
			vertices[i] = points[mappings[i]];

			vertices[i].pos.x *= scale.x;
			vertices[i].pos.y *= scale.y;
			vertices[i].pos.z *= scale.z;

			vertices[i].texCoord = texCoords[i];
			vertices[i].normal = normals[i / 6];
		}

		return( vertices );
	}
private:
	static constexpr Vertex points[] =
	{
		Vertex{ -1.0f,1.0f,1.0f },
		Vertex{ 1.0f,1.0f,1.0f },
		Vertex{ -1.0f,-1.0f,1.0f },
		Vertex{ 1.0f,-1.0f,1.0f },
		Vertex{ -1.0f,1.0f,-1.0f },
		Vertex{ 1.0f,1.0f,-1.0f },
		Vertex{ -1.0f,-1.0f,-1.0f },
		Vertex{ 1.0f,-1.0f,-1.0f }
	};
};