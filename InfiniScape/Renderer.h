#pragma once

#include "Program.h"
#include "GLObject.h"
class Renderer
{
	GLFWwindow* window;
	Program *programs[10];
	int programCount = 0;


	glm::mat4 Projection;
	glm::mat4 View;

	GLObject *objects[10];
	int objectCount;
public:
	Renderer();
	void render();
	void addProgram(Program *p);
	GLuint getProgram(int index);
	void addObject(GLObject *obj);
	GLFWwindow* getWindow();
};

