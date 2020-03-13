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

	glm::vec3 position = glm::vec3(0, 0, 5);
	float horizontalAngle = 3.14f;
	float verticalAngle = 0.0f;
	float initialFoV = 45.0f;

	float speed = 30.0f; 
	float mouseSpeed = 0.001f;

	double lastXpos=1;
	double lastYpos=1;

public:
	Camera();

	void computeMatrices(GLFWwindow* window);
	glm::mat4 getProjection();
	glm::mat4 getView();

};

