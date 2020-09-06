#include "Texture.h"
#include <cassert>
#include <iostream>
#include "Surface.h"

Texture::Texture( const std::string& fileName )
{
	Surface image{ fileName };

	glGenTextures( 1,&texture );
	glBindTexture( GL_TEXTURE_2D,texture );

	glTexParameteri( GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_REPEAT );
	glTexParameteri( GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_REPEAT );

	glTexParameterf( GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR );
	glTexParameterf( GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR );

	glTexImage2D( GL_TEXTURE_2D,0,GL_RGBA,image.GetWidth(),image.GetHeight(),0,GL_BGR,
		GL_UNSIGNED_BYTE,image.GetPixels().data() );

	Bind( 0 ); // May cause problems later idc tho.
}

Texture::~Texture()
{
	glDeleteTextures( 1,&texture );
}

void Texture::Bind( unsigned int unit )
{
	assert( unit >= 0 );
	assert( unit <= 31 );

	glActiveTexture( GL_TEXTURE0 + unit );
	glBindTexture( GL_TEXTURE_2D,texture );
}
