#pragma once

#include "PolyHills.h"
#include "Tree.h"

// Handles every entity in the world.
class PolyWorld
{
public:
	PolyWorld()
		:
		ground( worldSize,worldSize )
	{
		for( int i = 0; i < treeCount; ++i )
		{
			trees.emplace_back( Tree::Generate( ground.GetPoints() ) );
		}
	}

	void Update()
	{

	}

	void Draw( Shader& shader )
	{
		ground.Draw( shader );

		for( const auto& tree : trees )
		{
			tree.Draw( shader );
		}
	}
private:
	static constexpr int worldSize = 100;
	static constexpr int treeCount = 40;
	PolyHills ground;
	std::vector<Tree> trees;
};