#include <iostream>
#include "Display.h"
#include <GL/glew.h>
#include "Shader.h"
#include "Mesh.h"
#include "Texture.h"
#include "Transform.h"

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
	Transform xform;

	float counter = 0.0f;

	while( !display.IsClosed() )
	{
		display.Clear( 0.0f,1.0f,1.0f );

		xform.pos.x = sinf( counter );
		xform.rot.z = counter;
		xform.scale.x = cosf( counter );
		xform.scale.y = cosf( counter );
		xform.scale.z = cosf( counter );

		shader.Bind();
		tex.Bind( 0 );
		shader.Update( xform );
		mesh.Draw();

		display.Update();

		counter += 0.01f;
	}

	return( 0 );
}