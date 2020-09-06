#pragma once

#include <sdl2/SDL.h>
#include <cctype>

class Keyboard
{
	friend class Display;
public:
	bool KeyIsPressed( SDL_Keycode key ) const
	{
		return( keydown[key] );
	}
	bool KeyIsPressed( char key ) const
	{
		return( KeyIsPressed( tolower( key ) ) );
	}
private:
	void OnKeyPress( SDL_Keycode key )
	{
		if( key < 128 ) keydown[int( key )] = true;
	}
	void OnKeyRelease( SDL_Keycode key )
	{
		if( key < 128 ) keydown[int( key )] = false;
	}
private:
	bool keydown[128];
};