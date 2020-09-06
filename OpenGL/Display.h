#pragma once

#include <string>
#include <sdl2/SDL.h>
#include "Keyboard.h"

class Display
{
public:
	Display( int width,int height,const std::string& title );
	Display( const Display& ) = delete;
	Display& operator=( const Display& ) = delete;
	~Display();

	void Update();
	void Clear( float r,float g,float b,float a = 1.0f );

	bool IsClosed() const;
public:
	Keyboard kbd;
private:
	SDL_Window* pWnd;
	SDL_GLContext glCtx;
	bool closed = false;
};