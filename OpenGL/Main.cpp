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
#include "Compound.h"

int main( int argc,char* args[] )
{
	const int width = 800;
	const int height = 600;

	Display wnd{ width,height,"Display" };

	Camera cam{ glm::vec3( 0.0f,0.0f,-4.0f ),70.0f,
		float( width ) / float( height ),0.01f,1000.0f };
	// Shader shader{ "Shaders/VSTex.glsl","Shaders/PSTex.glsl",cam };
	Shader shader{ "Shaders/VSColor.glsl","Shaders/PSColor.glsl",cam };
	// Texture tex{ "Images/Bricks.bmp" };
	Texture tex{ Surface::FromColor( 0,100,100 ) };

	// Cube cube{ glm::vec3{ 1.1f,0.5f,0.5f } };
	// Model model2{ "Models/Monkey.obj" };
	Compound table{ "Models/Table.mikeobj" };

	glm::vec2 mousePos;
	constexpr float moveSpeed = 0.01f;
	constexpr float rotSpeed = 0.1f;
	constexpr float sens = 0.005f;
	constexpr float spd = 0.1f;

	shader.Bind();

	while( !wnd.IsClosed() )
	{
		wnd.Clear( 0.0f,1.0f,1.0f );
		
		// cube.Draw( shader );
		// model2.Draw( shader );
		table.Draw( shader );

		// if( wnd.mouse.LeftIsPressed() )
		// {
		// 	const auto diff = ( mousePos - wnd.mouse.GetPos() ) * rotSpeed;
		// 
		// 	// cube.xform.rot.x += float( diff.y ) * rotSpeed;
		// 	// cube.xform.rot.y -= float( diff.x ) * rotSpeed;
		// 	table.xform.rot.x += float( diff.y ) * rotSpeed;
		// 	table.xform.rot.y -= float( diff.x ) * rotSpeed;
		// }
		if( wnd.mouse.RightIsPressed() )
		{
			const auto diff = mousePos - wnd.mouse.GetPos();

			// TODO: Fix x/z mouse y rotation.
			cam.Rotate( glm::rotate( float( -diff.y ) * sens,glm::vec3{ 1.0f,0.0f,0.0f } ) );
			cam.Rotate( glm::rotate( float( diff.x ) * sens,glm::vec3{ 0.0f,1.0f,0.0f } ) );
		}

		glm::vec3 move{ 0.0f,0.0f,0.0f };
		if( wnd.kbd.KeyIsPressed( 'W' ) ) move.z += spd;
		if( wnd.kbd.KeyIsPressed( 'S' ) ) move.z -= spd;
		if( wnd.kbd.KeyIsPressed( 'A' ) ) move.x += spd;
		if( wnd.kbd.KeyIsPressed( 'D' ) ) move.x -= spd;
		if( wnd.kbd.KeyIsPressed( 'E' ) ) move.y += spd;
		if( wnd.kbd.KeyIsPressed( 'Q' ) ) move.y -= spd;
		cam.Translate( cam.GetForward() * move.z );
		cam.Translate( cam.GetRight() * move.x );
		cam.Translate( cam.GetUp() * move.y );

		mousePos = wnd.mouse.GetPos();

		wnd.Update();
	}

	return( 0 );
}