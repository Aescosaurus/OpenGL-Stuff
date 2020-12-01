#pragma once

#include "PolyHills.h"
#include "Tree.h"
#include "Timer.h"
#include "FrameTimer.h"
#include "Rabbit.h"

// Handles every entity in the world.
class PolyWorld
{
public:
	PolyWorld();

	void Update();
	void Draw( Shader& shader );
private:
	void GenerateTree();
	void GenerateRabbit();
private:
	FrameTimer ft;
	static constexpr int worldSize = 100;
	static constexpr int treeCount = 00; // from 40
	static constexpr int rabbitCount = 10;
	PolyHills ground;
	std::vector<Tree> trees;
	Timer treeSpawnRate = 5.0f;
	std::vector<Rabbit> rabbits;
};