#include "Display.h"
#include <GL/glew.h>
#include <iostream>

Display::Display( int width,int height,const std::string& title )
{
	// sdl+opengl boilerplate.
	SDL_Init( SDL_INIT_EVERYTHING );

	SDL_GL_SetAttribute( SDL_GL_RED_SIZE,8 );
	SDL_GL_SetAttribute( SDL_GL_GREEN_SIZE,8 );
	SDL_GL_SetAttribute( SDL_GL_BLUE_SIZE,8 );
	SDL_GL_SetAttribute( SDL_GL_ALPHA_SIZE,8 );
	SDL_GL_SetAttribute( SDL_GL_BUFFER_SIZE,32 );
	SDL_GL_SetAttribute( SDL_GL_DEPTH_SIZE,16 );
	SDL_GL_SetAttribute( SDL_GL_DOUBLEBUFFER,1 );

	pWnd = SDL_CreateWindow( title.c_str(),
		SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED,
		width,height,
		SDL_WINDOW_OPENGL );
	glCtx = SDL_GL_CreateContext( pWnd );

	GLenum status = glewInit();

	if( status != GLEW_OK ) std::cerr << "Glew failed to initialize!\n";

	closed = false;

	glEnable( GL_DEPTH_TEST );

	glEnable( GL_CULL_FACE );
	glCullFace( GL_BACK );
}

Display::~Display()
{
	SDL_GL_DeleteContext( glCtx );
	SDL_DestroyWindow( pWnd );
	SDL_Quit();
}

void Display::Update()
{
	SDL_GL_SwapWindow( pWnd );

	// Handle input for mouse/keyboard.
	SDL_Event e;
	while( SDL_PollEvent( &e ) )
	{
		switch( e.type )
		{
		case SDL_KEYDOWN:
			kbd.OnKeyPress( e.key.keysym.sym );
			break;
		case SDL_KEYUP:
			kbd.OnKeyRelease( e.key.keysym.sym );
			break;
		case SDL_MOUSEMOTION:
			mouse.SetPos( e.motion.x,e.motion.y );
			break;
		case SDL_MOUSEBUTTONDOWN:
			mouse.SetDown( e.button.button == 1,true );
			mouse.SetPos( e.button.x,e.button.y );
			break;
		case SDL_MOUSEBUTTONUP:
			mouse.SetDown( e.button.button == 1,false );
			mouse.SetPos( e.button.x,e.button.y );
			break;
		case SDL_MOUSEWHEEL:
			mouse.SetScroll( e.wheel.y );
			break;
		case SDL_QUIT:
			closed = true;
			break;
		}
	}
}

void Display::Clear( float r,float g,float b,float a )
{
	glClearColor( r,g,b,a );
	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
}

bool Display::IsClosed() const
{
	return( closed );
}
