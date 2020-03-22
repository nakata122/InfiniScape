#include "pch.h"

#include <iostream>
#include <vector>

// Include GLEW
#include <GL/glew.h>

// Include GLFW
#include <GLFW/glfw3.h>


// Include GUI
#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>


#include "shaders.h"
#include "Program.h"
#include "Renderer.h"


Renderer::Renderer()
{
	// Initialise GLFW
	if (!glfwInit())
	{
		fprintf(stderr, "Failed to initialize GLFW\n");
		getchar();
	}

	initWindow();
	initGUI();
	glfwMakeContextCurrent(window);


	glEnable(GL_PROGRAM_POINT_SIZE);

	// Enable depth test
	glEnable(GL_DEPTH_TEST);
	// Accept fragment if it closer to the camera than the former one
	glDepthFunc(GL_LESS);

	//glEnable(GL_CULL_FACE);

}

void Renderer::initWindow()
{

	glfwWindowHint(GLFW_SAMPLES, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// Open a window and create its OpenGL context
	window = glfwCreateWindow(1024, 768, "InfiniScape", NULL, NULL);
	if (window == NULL) {
		fprintf(stderr, "Failed to open GLFW window. If you have an Intel GPU, they are not 3.3 compatible.\n");
		getchar();
		glfwTerminate();
	}
	glfwMakeContextCurrent(window);

	// Initialize GLEW
	glewExperimental = true; // Needed for core profile
	if (glewInit() != GLEW_OK) {
		fprintf(stderr, "Failed to initialize GLEW\n");
		getchar();
		glfwTerminate();
	}

	// Ensure we can capture the escape key being pressed below
	glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);

	// Dark blue background
	glClearColor(0.0f, 0.0f, 0.4f, 1.0f);
}

void Renderer::initGUI()
{
	glfwWindowHint(GLFW_SAMPLES, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	gui = glfwCreateWindow(500, 720, "Settings", NULL, NULL);
	if (gui == NULL)
		std::cout << "Error could not render gui" << std::endl;
	glfwMakeContextCurrent(gui);
	// Setup Dear ImGui context
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;
	//io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
	//io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls

	// Setup Dear ImGui style
	ImGui::StyleColorsDark();
	//ImGui::StyleColorsClassic();

	// Setup Platform/Renderer bindings
	ImGui_ImplGlfw_InitForOpenGL(gui, true);
	ImGui_ImplOpenGL3_Init("#version 330 core");
}

void Renderer::render()
{
	glfwMakeContextCurrent(window);
	camera.computeMatrices(window);

	// Clear the screen
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	for (int i = 0; i < objectCount; i++)
	{
		objects[i]->setMVP(camera);
		programs[0]->bindProgram(*objects[i], camera);

		objects[i]->draw();
	}

	// Swap buffers
	glfwSwapBuffers(window);
	glfwPollEvents();
}

void Renderer::renderGUI(int *subdivision, Noise &noise, bool *visibility)
{

	glfwMakeContextCurrent(gui);

	glfwPollEvents();

	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	ImGui::NewFrame();

	change = false;
	{

		ImGui::Begin("Editor!");

		static int counter = 0;

		ImGui::Checkbox("Stop gui", visibility);
		//if (ImGui::SliderInt("Subdivision", subdivision, 1, 1000)) change = true;
		if (ImGui::SliderFloat("Elevation", &noise.elevation, 1, 5)) change = true;
		if (ImGui::SliderFloat("Frequency", &noise.frequency, 0, 1)) change = true;
		if (ImGui::SliderFloat("Amplitude", &noise.amplitude, 1, 100)) change = true;
		if (ImGui::SliderFloat("Persistence", &noise.persistence, 0, 1)) change = true;
		if (ImGui::SliderInt("Octaves", &noise.octaves, 1, 10)) change = true;


		if (ImGui::Button("Button"))
			counter++;

		ImGui::SameLine();
		ImGui::Text("counter = %d", counter);


		ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
		ImGui::End();
	}

	// Rendering
	ImGui::Render();
	int display_w, display_h;
	glfwGetFramebufferSize(gui, &display_w, &display_h);
	glViewport(0, 0, display_w, display_h);
	glClearColor(0, 0, 0, 1);
	glClear(GL_COLOR_BUFFER_BIT);
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

	glfwSwapBuffers(gui);
}

void Renderer::addObject(GLObject *obj)
{
	objects[objectCount++] = obj;
}

void Renderer::addProgram(Program *p)
{
	programs[programCount++] = p;
}

bool Renderer::isChanged()
{
	return change;
}

bool Renderer::isClosed()
{
	return glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS &&
			glfwWindowShouldClose(window) == 0 &&
			glfwWindowShouldClose(gui) == 0;
}