#pragma once

#include <string>
#include <GL/glew.h>

class Shader
{
public:
	Shader( const std::string& filename );
	~Shader();

	void Bind();
private:
	static std::string LoadShader( const std::string& filename );
	static void CheckShaderError( GLuint shader,GLuint flag,bool program,const std::string& msg );
	static GLuint CreateShader( const std::string& text,GLenum shaderType );
private:
	static constexpr int nShaders = 2;

	GLuint program;
	GLuint shaders[nShaders];
};