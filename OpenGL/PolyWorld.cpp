#include "PolyWorld.h"

PolyWorld::PolyWorld()
	:
	ground( worldSize,worldSize )
{
	for( int i = 0; i < treeCount; ++i ) GenerateTree();
	for( int i = 0; i < rabbitCount; ++i ) GenerateRabbit();
}

void PolyWorld::Update()
{
	const auto dt = ft.Mark();

	if( treeSpawnRate.Update( dt ) )
	{
		treeSpawnRate.Reset();

		GenerateTree();
	}

	for( auto& r : rabbits ) r.RabbitUpdate( trees,dt );
}

void PolyWorld::Draw( Shader& shader )
{
	ground.Draw( shader );

	for( const auto& tree : trees ) tree.Draw( shader );

	for( const auto& rabbit : rabbits ) rabbit.Draw( shader );
}

void PolyWorld::GenerateTree()
{
	trees.emplace_back( Tree{ ground.GetPoints() } );
}

void PolyWorld::GenerateRabbit()
{
	// rabbits.emplace_back( Rabbit{ ground.GetPoints(),ground.GetCachedSmooth(),worldSize } );
}
