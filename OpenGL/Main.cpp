#include <iostream>
#include "Display.h"
#include <GL/glew.h>
#include "Shader.h"
#include "Mesh.h"
#include "Texture.h"
#include "Transform.h"
#include "Camera.h"
#include "Model.h"
#include "Cube.h"

int main( int argc,char* args[] )
{
	const int width = 800;
	const int height = 600;

	Display display{ width,height,"Display" };

	Shader shader{ "Shaders/VertexShader.glsl","Shaders/PixelShader.glsl" };
	Texture tex{ "Images/Bricks2.bmp" };
	Camera cam{ glm::vec3( 0.0f,0.0f,-4.0f ),70.0f,
		float( width ) / float( height ),0.01f,1000.0f };

	// Model cube{ "Models/Cube.obj" };
	Cube cube{ glm::vec3{ 1.1f,0.5f,0.5f } };

	while( !display.IsClosed() )
	{
		display.Clear( 0.0f,1.0f,1.0f );

		shader.Bind();
		tex.Bind( 0 );
		shader.Update( cube.xform,cam );
		cube.Draw();

		cube.xform.rot.x = 0.4f;
		cube.xform.rot.y += 0.02f;

		display.Update();
	}

	return( 0 );
}