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
	glm::mat4 staticView;

	float horizontalAngle = 264.662f;
	float verticalAngle = -57.044f;
	float initialFoV = 45.0f;

	float speed = 15.0f; 
	float mouseSpeed = 0.002f;

	double lastXpos=1;
	double lastYpos=1;

public:
	glm::vec3 position = glm::vec3(0, 50, 0);

	Camera();

	void computeMatrices(GLFWwindow* window);
	glm::mat4 getProjection() const;
	glm::mat4 getView() const;
	glm::mat4 getStaticView() const;
};

