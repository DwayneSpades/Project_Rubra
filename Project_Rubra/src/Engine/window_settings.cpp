#include "window_settings.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <assert.h>

window_settings::window_settings(float width,float height, const char* name) 
{
	_windowName = name;
	_width = width; 
	_height = height;

	//creates the window that can be set as a context
	_window = glfwCreateWindow(_width, _height, _windowName, nullptr, nullptr);
	assert(_window);

	/*
	//throw an error if window is null
	if(!window)
	{
		printf("failed to create window");
		glfwTerminate();
	}
	*/

	//initialize GLAD and create window
	glfwMakeContextCurrent(_window);
}
GLFWwindow* window_settings::getWindow() const
{ 
	return _window; 
}

void window_settings::setWindowName(const char* string)
{
	_windowName = string;
}

const char* window_settings::getWindowName()
{
	return _windowName;
}

float window_settings::getWidth()
{
	return _width;
}

float window_settings::getHeight()
{
	return _height;
}