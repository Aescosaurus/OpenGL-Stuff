#pragma once

#include "Entity.h"
#include "Tree.h"

class Rabbit
	:
	public Entity
{
public:
	Rabbit( const std::vector<Vertex>& ground,const std::vector<float>& noise,int worldSize )
		:
		Entity( GenerateRandPos( ground ),size,color ),
		ground( &ground ),
		worldSize( worldSize )
	{}

	void RabbitUpdate( const std::vector<Tree>& trees,float dt )
	{
		GetPos().x += dt;

		GetPos().y = GetHeight( GetPos(),*ground,worldSize ) + size.y / 2.0f;
	}
private:
	static constexpr glm::vec3 size = { 0.3f,0.2f,0.4f };
	static constexpr glm::vec3 color = { 185.0f / 255.0f,122.0f / 255.0f,87.0f / 255.0f };
	const std::vector<Vertex>* ground;
	int worldSize;
};