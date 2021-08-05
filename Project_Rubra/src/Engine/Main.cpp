#include <iostream>
#include <assert.h>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

//wrapper classes
#include "opengl_app.h"
//shader code

//main loop for the engine

int main() 
{
	opengl_app* application = new opengl_app();

	application->load();

	application->update();

	application->draw();

	application->terminate();

	//print exit message
	printf("Project Rubra Closed\n");
	
	return 0;
}