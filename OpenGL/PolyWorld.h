#pragma once

#include "PolyHills.h"
#include "Tree.h"
#include "Timer.h"
#include "FrameTimer.h"

// Handles every entity in the world.
class PolyWorld
{
public:
	PolyWorld();

	void Update();
	void Draw( Shader& shader );
private:
	void GenerateTree();
private:
	FrameTimer ft;
	static constexpr int worldSize = 100;
	static constexpr int treeCount = 20; // from 40
	PolyHills ground;
	std::vector<Tree> trees;
	Timer treeSpawnRate = 5.0f;
};