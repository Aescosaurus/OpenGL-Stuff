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

	Display wnd{ width,height,"Display" };

	Shader shader{ "Shaders/VertexShader.glsl","Shaders/PixelShader.glsl" };
	Texture tex{ "Images/Bricks2.bmp" };
	Camera cam{ glm::vec3( 0.0f,0.0f,-4.0f ),70.0f,
		float( width ) / float( height ),0.01f,1000.0f };

	// Model cube{ "Models/Cube.obj" };
	Cube cube{ glm::vec3{ 1.1f,0.5f,0.5f } };

	glm::ivec2 mousePos;
	constexpr float moveSpeed = 0.01f;
	constexpr float rotSpeed = 0.008f;

	while( !wnd.IsClosed() )
	{
		wnd.Clear( 0.0f,1.0f,1.0f );

		shader.Bind();
		tex.Bind( 0 );
		shader.Update( cube.xform,cam );
		cube.Draw();

		if( wnd.kbd.KeyIsPressed( 'A' ) ) cube.xform.rot.x += 0.02f;

		if( wnd.mouse.LeftIsPressed() )
		{
			const auto diff = mousePos - wnd.mouse.GetPos();

			cube.xform.rot.x += float( diff.y ) * rotSpeed;
			cube.xform.rot.y += float( diff.x ) * rotSpeed;
		}
		if( wnd.mouse.RightIsPressed() )
		{
			const auto diff = mousePos - wnd.mouse.GetPos();

			cam.GetPos().x -= float( diff.x ) * moveSpeed;
			cam.GetPos().y -= float( diff.y ) * moveSpeed;
		}

		mousePos = wnd.mouse.GetPos();

		wnd.Update();
	}

	return( 0 );
}