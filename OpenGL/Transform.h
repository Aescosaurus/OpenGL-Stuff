#pragma once

#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>

class Transform
{
public:
	Transform( const glm::vec3& pos = glm::vec3(),
		const glm::vec3& rot = glm::vec3(),
		const glm::vec3& scale = glm::vec3( 1.0f,1.0f,1.0f ) )
		:
		pos( pos ),
		rot( rot ),
		scale( scale )
	{}

	glm::mat4 GetModel() const
	{
		glm::mat4 posMat = glm::translate( pos );
		glm::mat4 rotXMat = glm::rotate( rot.x,glm::vec3( 1.0f,0.0f,0.0f ) );
		glm::mat4 rotYMat = glm::rotate( rot.y,glm::vec3( 0.0f,1.0f,0.0f ) );
		glm::mat4 rotZMat = glm::rotate( rot.z,glm::vec3( 0.0f,0.0f,1.0f ) );
		glm::mat4 scaleMat = glm::scale( scale );

		glm::mat4 rotMat = rotZMat * rotYMat * rotXMat;

		return( posMat * rotMat * scaleMat );
	}

	// Transform GetOverlay( const Transform& trans ) const
	// {
	// 	// todo rotate around point
	// 	auto temp = *this;
	// 	temp.scale *= trans.scale;
	// 	temp.rot += trans.rot;
	// 	temp.pos += trans.pos;
	// 	return( temp );
	// }
public:
	glm::vec3 pos;
	glm::vec3 rot;
	glm::vec3 scale;
};