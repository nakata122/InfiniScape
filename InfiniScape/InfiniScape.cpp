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

	GLuint Texture = loadPNG_custom("grass.png");
	GLuint Texture2 = loadPNG_custom("hill.png");
	plane.addTexture(Texture);
	plane.addTexture(Texture2);

	renderer.addObject(&plane);

	do {

		renderer.renderGUI(&plane.subdivision, plane.noise);

		renderer.render();

		plane.updateVertices();
	}
	while (renderer.isClosed());

	glfwTerminate();

}
