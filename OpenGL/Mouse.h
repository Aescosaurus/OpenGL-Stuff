#pragma once

#include <glm/glm.hpp>

// Handles mouse input (screw glm).
class Mouse
{
	friend class Display;
public:
	void ClearScroll()
	{
		scroll = 0;
	}

	bool LeftIsPressed() const
	{
		return( leftDown );
	}
	bool RightIsPressed() const
	{
		return( rightDown );
	}
	// ivec2 is impossible to convert so just use floats idc.
	const glm::vec2& GetPos() const
	{
		return( pos );
	}
	int GetX() const
	{
		return( int( pos.x ) );
	}
	int GetY() const
	{
		return( int( pos.y ) );
	}
	int GetScroll() const
	{
		return( scroll );
	}
private:
	void SetPos( int x,int y )
	{
		pos.x = float( x );
		pos.y = float( y );
	}
	void SetDown( bool left,bool down )
	{
		if( left ) leftDown = down;
		else rightDown = down;
	}
	void SetScroll( int amount )
	{
		scroll = amount;
	}
private:
	glm::vec2 pos = glm::vec2{ 0.0f,0.0f };
	bool leftDown = false;
	bool rightDown = false;
	int scroll = 0;
};