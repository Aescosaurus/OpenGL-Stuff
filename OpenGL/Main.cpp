#include <iostream>
#include "Display.h"
#include <GL/glew.h>

int main( int argc,char* args[] )
{
	Display display{ 800,600,"Display" };

	while( !display.IsClosed() )
	{
		display.Clear( 0.0f,1.0f,1.0f );

		display.Update();
	}

	return( 0 );
}