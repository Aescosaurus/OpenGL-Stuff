#pragma once

#include "Vertex.h"
#include <GL/glew.h>
#include "obj_loader.h"
#include <vector>

class Mesh
{
public:
	Mesh( const std::vector<Vertex>& vertices,
		const std::vector<unsigned int>& indices,
		const std::vector<glm::vec3>& colors = {} );
	Mesh( const std::string& filename );

	Mesh( const Mesh& ) = delete;
	Mesh& operator=( const Mesh& ) = delete;
	~Mesh();

	void Draw() const;
private:
	void InitMesh( const IndexedModel& model,
		const std::vector<glm::vec3>& colors = {} );
private:
	enum
	{
		POSITION_VB,
		TEXCOORD_VB,
		NORMAL_VB,
		COLOR_VB,

		INDEX_VB,

		NUM_BUFFERS
	};

	GLuint vertexArrayObj;
	GLuint vertexArrayBuffers[NUM_BUFFERS];
	int drawCount;
	static constexpr glm::vec3 defaultColor = { 150.0f,0.0f,150.0f };
};