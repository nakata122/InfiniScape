// InfiniScape.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>

// Include GLEW
#include <GL/glew.h>

// Include GLFW
#include <GLFW/glfw3.h>

#include "Renderer.h"
#include "Plane.h"
#include "HeightMap.h"
#include "texture.h"



int main()
{
	Renderer renderer;

	HeightMap program;

	Plane plane(100000, 10);
	renderer.addProgram(&program);

	GLuint Texture = loadPNG_custom("grass.png");
	GLuint Texture2 = loadPNG_custom("snow.png");
	plane.addTexture(Texture);
	plane.addTexture(Texture2);

	renderer.addObject(&plane);


	// For speed computation
	double lastTime = glfwGetTime();
	int nbFrames = 0;

	do {
		// Measure speed
		double currentTime = glfwGetTime();
		nbFrames++;
		if (currentTime - lastTime >= 1.0) {
			printf("%f ms/frame\n", 1000.0 / double(nbFrames));
			nbFrames = 0;
			lastTime += 1.0;
		}

		// Clear the screen
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		renderer.render();

		// Swap buffers
		glfwSwapBuffers(renderer.getWindow());
		glfwPollEvents();

	} // Check if the ESC key was pressed or the window was closed
	while (glfwGetKey(renderer.getWindow(), GLFW_KEY_ESCAPE) != GLFW_PRESS &&
		glfwWindowShouldClose(renderer.getWindow()) == 0);

}
