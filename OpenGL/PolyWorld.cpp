#include "PolyWorld.h"

PolyWorld::PolyWorld()
	:
	ground( worldSize,worldSize )
{
	for( int i = 0; i < treeCount; ++i )
	{
		GenerateTree();
	}
}

void PolyWorld::Update()
{
	const auto dt = ft.Mark();

	if( treeSpawnRate.Update( dt ) )
	{
		treeSpawnRate.Reset();

		GenerateTree();
	}
}

void PolyWorld::Draw( Shader& shader )
{
	ground.Draw( shader );

	for( const auto& tree : trees )
	{
		tree.Draw( shader );
	}
}

void PolyWorld::GenerateTree()
{
	trees.emplace_back( Tree::Generate( ground.GetPoints() ) );
}
