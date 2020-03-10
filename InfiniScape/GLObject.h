#pragma once
#include <vector>

// Include GLM
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

// Include GLEW
#include <GL/glew.h>

class GLObject
{
	GLuint vertexbuffer;
	GLuint indexbuffer;

	GLuint textureID[10];
	GLuint programID = -1;
	glm::mat4 MVP;

protected:
	std::vector<glm::vec3> vertices;
	std::vector<unsigned short> indices;
	glm::mat4 Model;
	int numTriangles;

public:
	GLObject();
	virtual void draw(glm::mat4 Projection, glm::mat4 View, GLuint MatrixID);
	void updateBuffers();
	GLuint getProgramID();
	void setProgramID(GLuint id);
	void cleanUp();
};

