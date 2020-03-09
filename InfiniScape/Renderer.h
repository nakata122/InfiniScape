#pragma once
class Renderer
{
	GLFWwindow* window;
	GLuint programID[10];
	int maxProgram = 0;
public:
	Renderer();
	void render();
	void addProgram(const char* vertShader, const char* fragShader);
	GLFWwindow* getWindow();
};

