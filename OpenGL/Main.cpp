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

	Vertex vertices[] =
	{
		Vertex( -0.5f,-0.5f,0.0f,0.0f,0.0f ),
		Vertex( 0.0f,0.5f,0.0f,0.5f,1.0f ),
		Vertex( 0.5f,-0.5f,0.0f,1.0f,0.0f )
	};

	unsigned int indices[] = { 0,1,2 };

	Mesh mesh{ vertices,sizeof( vertices ) / sizeof( vertices[0] ),
		indices,sizeof( indices ) / sizeof( indices[0] ) };
	Mesh mesh2{ "Models/Monkey.obj" };
	Shader shader{ "Shaders/BasicShader" };
	Texture tex{ "Images/Bricks2.bmp" };
	Camera cam{ glm::vec3( 0.0f,0.0f,-4.0f ),70.0f,
		float( width ) / float( height ),0.01f,1000.0f };
	Transform xform;

	float counter = 0.0f;

	while( !display.IsClosed() )
	{
		display.Clear( 0.0f,1.0f,1.0f );

		xform.pos.x = sinf( counter );
		xform.pos.z = cosf( counter );
		xform.rot.x = counter;
		xform.rot.y = counter;
		xform.rot.z = counter;
		// xform.scale.x = cosf( counter );
		// xform.scale.y = cosf( counter );
		// xform.scale.z = cosf( counter );

		shader.Bind();
		tex.Bind( 0 );
		shader.Update( xform,cam );
		mesh2.Draw();

		display.Update();

		counter += 0.01f;
	}

	return( 0 );
}