#include "Transform.h"

#include "glm\gtc\matrix_transform.hpp"

Transform::Transform():position(glm::vec3(0.0f)),yaw(0.0f),pitch(0.0f),roll(0.0f),scale(glm::vec3(1.0f))
{
}

glm::mat4 Transform::getMatrix()
{
	glm::mat4 lMatrix(1.0f);
	lMatrix = glm::rotate(lMatrix, glm::radians(pitch), glm::vec3(1.0f, 0.0f, 0.0f));
	lMatrix = glm::rotate(lMatrix, glm::radians(yaw), glm::vec3(0.0f, 1.0f, 0.0f));
	lMatrix = glm::rotate(lMatrix, glm::radians(roll), glm::vec3(0.0f, 0.0f, 1.0f));
	lMatrix = glm::translate(lMatrix, position);
	lMatrix = glm::scale(lMatrix, scale);
	return lMatrix;
}
