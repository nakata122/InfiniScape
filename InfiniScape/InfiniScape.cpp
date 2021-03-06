// InfiniScape.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>

// Include GLEW
#include <GL/glew.h>

// Include GLFW
#include <GLFW/glfw3.h>

// Include GUI
#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>

#include "Renderer.h"
#include "Plane.h"
#include "HeightMap.h"
#include "texture.h"

void widgetControler()
{
	static int counter = 0;

	ImGui::Text("Movement.");
	

	if (ImGui::Button("Button"))
		counter++;

	ImGui::SameLine();
	ImGui::Text("counter = %d", counter);
}

int main()
{
	Renderer renderer;

	HeightMap program;

	Plane plane(128 * 128);
	renderer.addProgram(&program);

	GLuint Texture = loadPNG_custom("soil.png");
	GLuint Texture2 = loadPNG_custom("hill.png");
	plane.addTexture(Texture);
	plane.addTexture(Texture2);

	renderer.addObject(&plane);
	bool renderGui = true;


	// For speed computation
	double lastTime = glfwGetTime();
	int nbFrames = 0;

	do {

		// Measure speed
		double currentTime = glfwGetTime();
		nbFrames++;
		if (currentTime - lastTime >= 1.0) { // If last prinf() was more than 1sec ago
			// printf and reset
			printf("%f ms/frame\n", 1000.0 / double(nbFrames));
			nbFrames = 0;
			lastTime += 1.0;
		}

		if(renderer.isChanged())
			plane.updateHeightMap();

		if(renderGui)
			renderer.renderGUI(&plane.subdivision, plane.noise, &renderGui);

		renderer.render();

	}
	while (renderer.isClosed());

	glfwTerminate();

}
