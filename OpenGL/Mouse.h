#pragma once

#include <glm/glm.hpp>

class Mouse
{
	friend class Display;
public:
	bool LeftIsPressed() const
	{
		return( leftDown );
	}
	bool RightIsPressed() const
	{
		return( rightDown );
	}
	const glm::ivec2& GetPos() const
	{
		return( pos );
	}
	int GetX() const
	{
		return( pos.x );
	}
	int GetY() const
	{
		return( pos.y );
	}
private:
	void SetPos( int x,int y )
	{
		pos.x = x;
		pos.y = y;
	}
	void SetDown( bool left,bool down )
	{
		if( left ) leftDown = down;
		else rightDown = down;
	}
private:
	glm::ivec2 pos = glm::ivec2{ 0,0 };
	bool leftDown = false;
	bool rightDown = false;
};