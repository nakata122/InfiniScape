#pragma once
#include <vector>

// Include GLM
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

// Include GLEW
#include <GL/glew.h>

#include "Camera.h"

class GLObject
{
	GLuint vertexbuffer;
	GLuint normalbuffer;
	GLuint indexbuffer;
	GLuint uvbuffer;

	GLuint programID = 0;
	std::vector<GLuint> textureID;

protected:
	std::vector<glm::vec3> vertices;
	std::vector<glm::vec3> normals;
	std::vector<glm::vec2> texCoords;
	std::vector<unsigned short> indices;
	Camera *currentCamera;
	glm::mat4 Model;
	glm::mat4 MVP;
	int numTriangles;

public:

	GLObject();

	~GLObject();

	virtual void draw();
	void generateBuffers();
	void updatePositionBuffers();

	void setMVP(Camera &camera);
	glm::mat4 getMVP();
	glm::mat4 getModel();
	GLuint getProgramID();
	std::vector<GLuint> &getTextures();
	void addTexture(GLuint texture);
};

