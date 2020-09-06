#pragma once

#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>

class Camera
{
public:
	Camera( const glm::vec3& pos,float fov,float aspect,
		float zNear,float zFar )
		:
		perspective( glm::perspective( fov,aspect,zNear,zFar ) ),
		pos( pos ),
		forward( 0.0f,0.0f,1.0f ),
		up( 0.0f,1.0f,0.0f )
	{}

	glm::mat4 GetViewProj() const
	{
		return( perspective * glm::lookAt( pos,pos + forward,up ) );
	}
private:
	glm::mat4 perspective;
	glm::vec3 pos;
	glm::vec3 forward;
	glm::vec3 up;
};