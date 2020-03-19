#pragma once

// Include GLFW
#include <GLFW/glfw3.h>

// Include GLM
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>


class Camera
{
	glm::mat4 Projection;
	glm::mat4 View;

	float horizontalAngle = 264.662f;
	float verticalAngle = -57.044f;
	float initialFoV = 45.0f;

	float speed = 30.0f; 
	float mouseSpeed = 0.002f;

	double lastXpos=1;
	double lastYpos=1;

public:
	glm::vec3 position = glm::vec3(-8, 50, -8);

	Camera();

	void computeMatrices(GLFWwindow* window);
	glm::mat4 getProjection();
	glm::mat4 getView();

};

