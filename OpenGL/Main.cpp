#include <iostream>
#include "Display.h"
#include <GL/glew.h>
#include "Shader.h"
#include "Mesh.h"
#include "Texture.h"
#include "Transform.h"
#include "Camera.h"

int main( int argc,char* args[] )
{
	const int width = 800;
	const int height = 600;

	Display display{ width,height,"Display" };

	Mesh mesh2{ "Models/Monkey.obj" };
	Shader shader{ "Shaders/VertexShader.glsl","Shaders/PixelShader.glsl" };
	Texture tex{ "Images/Bricks2.bmp" };
	Camera cam{ glm::vec3( 0.0f,0.0f,-4.0f ),70.0f,
		float( width ) / float( height ),0.01f,1000.0f };
	Transform xform;

	while( !display.IsClosed() )
	{
		display.Clear( 0.0f,1.0f,1.0f );

		shader.Bind();
		tex.Bind( 0 );
		shader.Update( xform,cam );
		mesh2.Draw();

		display.Update();
	}

	return( 0 );
}