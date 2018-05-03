#pragma once

#include <glm\glm.hpp>

class Transform {
public:

	glm::vec3 position;
	float yaw;
	float pitch;
	float roll;
	glm::vec3 scale;

	Transform();

	glm::mat4 getMatrix();

};