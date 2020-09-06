#pragma once

#include <string>
#include <GL/glew.h>
#include "Transform.h"
#include "Camera.h"

class Shader
{
public:
	Shader( const std::string& vsFilename,const std::string& fsFilename,const Camera& cam );
	Shader( const Shader& ) = delete;
	Shader& operator=( const Shader& ) = delete;
	~Shader();

	void Update( const Transform& transform ) const;
	void Bind();
private:
	static std::string LoadShader( const std::string& filename );
	static void CheckShaderError( GLuint shader,GLuint flag,bool program,const std::string& msg );
	static GLuint CreateShader( const std::string& text,GLenum shaderType );
private:
	enum
	{
		TRANSFORM_U,

		NUM_UNIFORMS
	};

	static constexpr int nShaders = 2;

	GLuint program;
	GLuint shaders[nShaders];
	GLuint uniforms[NUM_UNIFORMS];

	const Camera& cam;
};