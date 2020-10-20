#pragma once

#include "PolyHills.h"

// Handles every entity in the world.
class PolyWorld
{
public:
	PolyWorld()
		:
		ground( 30,30 )
	{
		ground.xform.pos.y -= 5.0f;
	}
private:
	PolyHills ground;
};