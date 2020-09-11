#pragma once

#include <string>
#include <GL/glew.h>
#include "Surface.h"

class Texture
{
public:
	Texture( const Surface& surf );
	Texture( const std::string& fileName );
	~Texture();

	void Bind( unsigned int unit );
private:
	GLuint texture;
};