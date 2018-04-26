#include "Camera.h"

#include "glm\gtc\matrix_transform.hpp"

#include <iostream>

using namespace glm;

void Camera::updatePosition()
{
	float hOffset = m_Distance * cos(glm::radians(pitch));
	float vOffset = m_Distance * sin(glm::radians(pitch));
	float xOffset = hOffset * sin(glm::radians(m_AngleAround));
	float zOffset = hOffset * cos(glm::radians(m_AngleAround));
	if (target) {
		Position[0] = (*target)[0] * xOffset;
		Position[2] = (*target)[2] * zOffset;
		Position[1] = (*target)[1] * vOffset;
	}
}

Camera::Camera(glm::vec3 position): Position(position)
{
}


glm::mat4 Camera::initProjection(float fov, float ratio, float near, float far)
{
	m_Fov = fov;
	m_Ratio = ratio;
	m_Near = near;
	m_Far = far;
	m_Projection = glm::perspective(glm::radians(m_Fov), m_Ratio, m_Near, m_Far);

	return m_Projection;
}

glm::mat4 Camera::getProjection() {
	return m_Projection;
}

glm::mat4 Camera::getView()
{
	if (target) {
		glm::mat4 view(1.0f);
		view = glm::rotate(view, glm::radians(pitch), glm::vec3(1.0f, 0.0f, 0.0f) );
		view = glm::rotate(view, glm::radians(yaw), glm::vec3(0.0f, 1.0f, 0.0f) );
		view = glm::translate(view, Position );

		return view;
	}
	else {

	}
}

