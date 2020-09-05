#include "Shader.h"
#include <fstream>
#include <iostream>

Shader::Shader( const std::string& filename )
{
	program = glCreateProgram();
	shaders[0] = CreateShader( LoadShader( filename + ".vs" ),GL_VERTEX_SHADER );
	shaders[1] = CreateShader( LoadShader( filename + ".ps" ),GL_FRAGMENT_SHADER );

	for( int i = 0; i < nShaders; ++i )
	{
		glAttachShader( program,shaders[i] );
	}

	glBindAttribLocation( program,0,"position" );
	glBindAttribLocation( program,1,"texCoord" );

	glLinkProgram( program );
	CheckShaderError( program,GL_LINK_STATUS,true,"Program failed to link!" );

	glValidateProgram( program );
	CheckShaderError( program,GL_VALIDATE_STATUS,true,"Program failed to validate!" );
}

Shader::~Shader()
{
	for( int i = 0; i < nShaders; ++i )
	{
		glDetachShader( program,shaders[i] );
		glDeleteShader( shaders[i] );
	}

	glDeleteProgram( program );
}

void Shader::Bind()
{
	glUseProgram( program );
}

std::string Shader::LoadShader( const std::string& filename )
{
	std::ifstream file;
	file.open( filename.c_str() );

	std::string output;
	std::string line;
	if( file.is_open() )
	{
		while( file.good() )
		{
			std::getline( file,line );
			output.append( line + '\n' );
		}
	}
	else
	{
		std::cerr << "Unable to load shader " << filename << '\n';
	}

	return( output );
}

void Shader::CheckShaderError( GLuint shader,GLuint flag,bool program,const std::string& msg )
{
	GLint success = 0;
	GLchar error[1024] = { 0 };

	if( program ) glGetProgramiv( shader,flag,&success );
	else glGetShaderiv( shader,flag,&success );

	if( success == GL_FALSE )
	{
		if( program ) glGetProgramInfoLog( shader,sizeof( error ),nullptr,error );
		else glGetShaderInfoLog( shader,sizeof( error ),nullptr,error );

		std::cerr << msg << ": " << error << '\n';
	}
}

GLuint Shader::CreateShader( const std::string& text,GLenum shaderType )
{
	GLuint shader = glCreateShader( shaderType );

	if( shader == 0 ) std::cerr << "Shader creation failed!\n";

	const GLchar* shaderSrc[1];
	GLint shaderSrcLen[1];
	shaderSrc[0] = text.c_str();
	shaderSrcLen[0] = GLuint( text.length() );

	glShaderSource( shader,1,shaderSrc,shaderSrcLen );
	glCompileShader( shader );

	CheckShaderError( shader,GL_COMPILE_STATUS,false,"Shader compilation failed!" );

	return( shader );
}
