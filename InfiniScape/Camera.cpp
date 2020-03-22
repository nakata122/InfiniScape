#include "Camera.h"

Camera::Camera()
{
	Projection = glm::perspective(glm::radians(initialFoV), 4.0f / 3.0f, 0.1f, 300.0f);

	// Camera matrix
	View = staticView = glm::lookAt(
		glm::vec3(0, 50, 0), // Camera is at (4,3,3), in World Space
		glm::vec3(100, 0, 100), // and looks at the origin
		glm::vec3(0, 1, 0)  // Head is up (set to 0,-1,0 to look upside-down)
	);
}

void Camera::computeMatrices(GLFWwindow* window)
{

	// glfwGetTime is called only once, the first time this function is called
	static double lastTime = glfwGetTime();

	// Compute time difference between current and last frame
	double currentTime = glfwGetTime();
	float deltaTime = float(currentTime - lastTime);

	// Get mouse position
	double xpos, ypos;
	glfwGetCursorPos(window, &xpos, &ypos);


	//Change direction
	if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS)
	{
		// Compute new orientation
		horizontalAngle += mouseSpeed * float(lastXpos - xpos);
		verticalAngle += mouseSpeed * float(lastYpos - ypos);
	}

	// Direction : Spherical coordinates to Cartesian coordinates conversion
	glm::vec3 direction(
		cos(verticalAngle) * sin(horizontalAngle),
		sin(verticalAngle),
		cos(verticalAngle) * cos(horizontalAngle)
	);

	// Right vector
	glm::vec3 right = glm::vec3(
		sin(horizontalAngle - 3.14f / 2.0f),
		0,
		cos(horizontalAngle - 3.14f / 2.0f)
	);

	// Up vector
	glm::vec3 up = glm::cross(right, direction);
	// Move forward
	if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS) 
	{
		position += direction * deltaTime * speed;
	}
	// Move backward
	if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS) 
	{
		position -= direction * deltaTime * speed;
	}
	// Strafe right
	if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS) 
	{
		position += right * deltaTime * speed;
	}
	// Strafe left
	if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS) 
	{
		position -= right * deltaTime * speed;
	}

	float FoV = initialFoV;

	// Projection matrix 
	Projection = glm::perspective(glm::radians(FoV), 4.0f / 3.0f, 0.1f, 300.0f);
	// Camera matrix
	View = glm::lookAt(
		position,           
		position + direction, 
		up                  
	);

	// Camera matrix
	staticView = glm::lookAt(
		glm::vec3(0, 50, 0),
		glm::vec3(0, 50, 0) + direction,
		up
	);

	lastTime = currentTime;
	lastXpos = xpos;
	lastYpos = ypos;
}

glm::mat4 Camera::getProjection() const
{
	return Projection;
}

glm::mat4 Camera::getView() const
{
	return View;
}

glm::mat4 Camera::getStaticView() const
{
	return staticView;
}