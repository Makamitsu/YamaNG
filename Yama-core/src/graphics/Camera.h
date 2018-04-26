#pragma once

#include <glm/glm.hpp>

class Camera {


private:
	float m_Fov;
	float m_Ratio;
	float m_Far;
	float m_Near;
	glm::mat4 m_Projection;


public:
	glm::vec3* target;
	float m_Distance = 30.0f;
	float m_AngleAround = 0.0f;

	void updatePosition();


	glm::vec3 Position;
	float pitch = 20;
	float yaw;
	float roll;

	Camera(glm::vec3 position);
	glm::mat4 initProjection(float fov, float ratio, float near, float far);
	glm::mat4 getProjection();

	glm::mat4 getView();

};