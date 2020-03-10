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
	GLuint uvbuffer;

	GLuint programID = 0;
	GLuint textureID[10];
	int texCount = 0;
	glm::mat4 MVP;

protected:
	std::vector<glm::vec3> vertices;
	std::vector<glm::vec2> texCoords;
	std::vector<unsigned short> indices;
	glm::mat4 Model;
	int numTriangles;

public:
	GLObject();

	~GLObject();

	virtual void draw();
	void updateBuffers();

	void setMVP(glm::mat4 Projection, glm::mat4 View);
	glm::mat4 getMVP();
	GLuint getProgramID();
	GLuint getTexture(int index);
	void addTexture(GLuint texture);
};

