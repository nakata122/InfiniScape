// InfiniScape.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>

// Include GLEW
#include <GL/glew.h>

// Include GLFW
#include <GLFW/glfw3.h>


#include "Renderer.h"


int main()
{
	Renderer renderer;

	renderer.addProgram("heightmap.vertexshader", "heightmap.fragmentshader");

	do {

		

		// Swap buffers
		glfwSwapBuffers(renderer.getWindow());
		glfwPollEvents();

	} // Check if the ESC key was pressed or the window was closed
	while (glfwGetKey(renderer.getWindow(), GLFW_KEY_ESCAPE) != GLFW_PRESS &&
		glfwWindowShouldClose(renderer.getWindow()) == 0);

}
