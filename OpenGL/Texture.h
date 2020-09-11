#pragma once

#include <string>
#include <GL/glew.h>
#include "Surface.h"

// This is dumb pls change this.
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