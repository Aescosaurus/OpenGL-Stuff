#pragma once

#include "PolyHills.h"

// Handles every entity in the world.
class PolyWorld
{
public:
	PolyWorld()
		:
		ground( worldSize,worldSize )
	{}

	void Draw( Shader& shader )
	{
		ground.Draw( shader );
	}
private:
	static constexpr int worldSize = 50;
	PolyHills ground; // How do I deal with ground collision???
};