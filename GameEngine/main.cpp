#define GLFW_INCLUDE_NONE
#define DEBUG_MODE

#include <GLFW/glfw3.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#include "Graphics.h"

#include "print.h"

Graphics* gfx;

static void error_callback(int error, const char* description)
{
	fprintf(stderr, "Error: %s\n", description);
}

static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GLFW_TRUE);
}

int Init()
{
	srand(time(NULL));

	GLFWwindow* window;
	glfwSetErrorCallback(error_callback);
	if (!glfwInit())
		GLFWAPI::exit(EXIT_FAILURE);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
	glfwWindowHint(GLFW_SAMPLES, 4);
	window = glfwCreateWindow(800, 620, "Simple example", NULL, NULL);
	if (!window)
	{
		glfwTerminate();
		GLFWAPI::exit(EXIT_FAILURE);
	}
	glfwSetKeyCallback(window, key_callback);
	glfwMakeContextCurrent(window);
	gladLoadGL();
	glfwSwapInterval(1);

	gfx = new Graphics(window);

	gfx->init();
	while (!glfwWindowShouldClose(window))
	{
		gfx->preRender();
		gfx->render();
		gfx->postRender();

		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	glfwDestroyWindow(window);
	glfwTerminate();
	GLFWAPI::exit(EXIT_SUCCESS);
	return 0;
}

#if defined _WIN32 && !defined DEBUG_MODE
#include <Windows.h>
int WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
	PSTR lpCmdLine, INT nCmdShow) {
	return Init();
}
#else
int main()
{
	return Init();
}
#endif
