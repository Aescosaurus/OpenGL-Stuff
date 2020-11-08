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
#include "Plane.h"
#include "PolyHills.h"
#include "PolyWorld.h"

int main( int argc,char* args[] )
{
	constexpr int width = 1200;
	constexpr int height = 800;

	Display wnd{ width,height,"Display" };

	Camera cam{ glm::vec3( 0.0f,0.0f,-4.0f ),70.0f,
		float( width ) / float( height ),0.01f,1000.0f };
	cam.Rotate( glm::rotate( float( glm::pi<float>() / 4.5f ),cam.GetRight() ) );
	cam.Translate( cam.GetForward() * ( -30.0f ) );

	Shader shader{ "Shaders/VSColor.glsl","Shaders/PSColor.glsl",cam };

	// PolyWorld world;
	std::vector<std::unique_ptr<PolyWorld>> world;
	world.emplace_back( std::make_unique<PolyWorld>() );

	// Plane plane{ 30,30,2 };
	// plane.xform.pos.y -= 5.0f;
	// plane.xform.rot.x -= glm::pi<float>() / 2.0f;

	// PolyHills hills{ 30,30 };
	// hills.xform.pos.y -= 5.0f;
	// hills.xform.rot.x -= glm::pi<float>() / 2.0f;

	glm::vec2 mousePos;
	constexpr float moveSpeed = 0.01f;
	constexpr float rotSpeed = 0.1f;
	constexpr float sens = 0.005f;
	constexpr float spd = 0.1f;
	constexpr float scrollSpd = 1.0f;

	while( !wnd.IsClosed() )
	{
		wnd.Clear( 0.0f,0.0f,0.0f );
		
		// plane.Draw( shader );
		// hills.Draw( shader );
		world[0]->Draw( shader );

		if( wnd.mouse.LeftIsPressed() )
		{
			const auto diff = mousePos - wnd.mouse.GetPos();

			// cam.Rotate( glm::rotate( float( -diff.y ) * sens,cam.GetRight() ) );
			cam.Rotate( glm::rotate( float( diff.x ) * sens,glm::vec3{ 0.0f,1.0f,0.0f } ) );
		}
		else if( wnd.mouse.RightIsPressed() )
		{
			const auto diff = mousePos - wnd.mouse.GetPos();
			const auto oldY = cam.GetPos().y;

			glm::vec3 move{ 0.0f,0.0f,0.0f };
			move.z = diff.y * spd;
			move.x = diff.x * spd;
			cam.Translate( cam.GetForward() * move.z + cam.GetRight() * move.x );
			cam.GetPos().y = oldY;
		}
		else if( wnd.mouse.GetScroll() != 0 )
		{
			cam.Translate( cam.GetForward() * float( wnd.mouse.GetScroll() ) * scrollSpd );
			wnd.mouse.ClearScroll();
		}

		if( wnd.kbd.KeyIsPressed( SDLK_r ) )
		{
			world.erase( world.begin() );
			world.emplace_back( std::make_unique<PolyWorld>() );
		}

		mousePos = wnd.mouse.GetPos();

		wnd.Update();
	}

	return( 0 );
}