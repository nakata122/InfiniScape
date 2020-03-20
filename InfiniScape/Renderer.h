#pragma once

#include "Program.h"
#include "GLObject.h"
#include "Noise.h"
#include "Camera.h"
class Renderer
{
	GLFWwindow* window;
	GLFWwindow* gui;
	Program *programs[10];
	int programCount = 0;

	Camera camera;

	GLObject *objects[10];
	int objectCount;
	bool change;
	void initWindow();
	void initGUI();
public:
	Renderer();
	void render();
	void renderGUI(int *subdivision, Noise &noise);
	void addProgram(Program *p);
	void addObject(GLObject *obj);
	bool isChanged();
	bool isClosed();
};

