#pragma once

#include "GLObject.h"
class Renderer
{
	GLFWwindow* window;
	GLuint programID[10];
	GLuint currentProgram;
	int numPrograms = 0;


	glm::mat4 Projection;
	glm::mat4 View;
	GLuint MatrixID;

	GLObject objects[10];
	int numObjects;
public:
	Renderer();
	void render();
	void addProgram(const char* vertShader, const char* fragShader);
	GLuint getProgram(int index);
	void addObject(GLObject obj);
	GLFWwindow* getWindow();
};

