#include <iostream>
#include "Display.h"
#include <GL/glew.h>
#include "Shader.h"
#include "Mesh.h"
#include "Texture.h"

int main( int argc,char* args[] )
{
	Display display{ 800,600,"Display" };

	Vertex vertices[] =
	{
		Vertex( -0.5f,-0.5f,0.0f,0.0f,0.0f ),
		Vertex( 0.0f,0.5f,0.0f,0.5f,1.0f ),
		Vertex( 0.5f,-0.5f,0.0f,1.0f,0.0f )
	};

	Mesh mesh{ vertices,sizeof( vertices ) / sizeof( vertices[0] ) };
	Shader shader{ "Shaders/BasicShader" };
	Texture tex{ "Images/Bricks2.bmp" };

	while( !display.IsClosed() )
	{
		display.Clear( 0.0f,1.0f,1.0f );
		tex.Bind( 0 );
		shader.Bind();

		mesh.Draw();

		display.Update();
	}

	return( 0 );
}