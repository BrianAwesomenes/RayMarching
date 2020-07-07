#pragma once

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <glad/glad.h>

#include "Matrix.h"

class Graphics
{
	GLFWwindow* window;
public:
	Graphics(GLFWwindow* window) : window(window) {}

	void init();
	void end();

	void preRender();
	void render();
	void postRender();
};

