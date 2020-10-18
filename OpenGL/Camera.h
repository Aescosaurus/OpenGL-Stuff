#pragma once

#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>

// Camera to view our beautiful models.
class Camera
{
public:
	// Create perspective proj matm using fov, aspect ratio, and z planes.
	Camera( const glm::vec3& pos,float fov,float aspect,
		float zNear,float zFar )
		:
		perspective( glm::perspective( fov,aspect,zNear,zFar ) ),
		pos( pos ),
		forward( 0.0f,0.0f,1.0f ),
		up( 0.0f,1.0f,0.0f )
	{}

	void Translate( const glm::vec3& move )
	{
		// pos += ( rot * move );
		pos += move;
	}
	// Rotates forward and up vecs for getviewproj.
	void Rotate( const glm::mat3& rot )
	{
		forward = rot * forward;
		up = rot * up;
		this->rot = rot;
	}
	glm::vec3& GetPos()
	{
		return( pos );
	}

	// Apply to xforms and pass to shader.
	glm::mat4 GetViewProj() const
	{
		return( perspective * glm::lookAt( pos,pos + forward,up ) );
	}
	const glm::vec3& GetForward() const
	{
		return( forward );
	}
	glm::vec3 GetRight() const
	{
		auto temp = forward;
		std::swap( temp.x,temp.z );
		temp.x *= -1.0f;
		return( -temp );
		// return( glm::mat3( glm::rotate( 70.0f,glm::vec3{ 0.0f,1.0f,0.0f } ) ) * forward );
	}
	const glm::vec3& GetUp() const
	{
		return( up );
	}
	const glm::mat3& GetRot() const
	{
		return( rot );
	}
private:
	glm::mat4 perspective;
	glm::vec3 pos;
	glm::vec3 forward;
	glm::vec3 up;
	glm::mat3 rot;
};