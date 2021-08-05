#include "stb_image.h"

#include "shaderBase.h"
#include "opengl_app.h"
#include "graphicsObject.h"
#include "model.h"
#include "camera.h"

void opengl_app::load() 
{
	//------------------------------------GLFW Initialization---------------------------------------------------------------------
	// ideally all of this rendering code is going to abstracted into it's own dll's???????
	//initialize glfw
	glfwInit();
	//initialize GLFW window context information
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	//initialize GLFW window
	//------------------------------------Window Initialization---------------------------------------------------------------------
	window = new window_settings(1080, 720, "Project Rubra");

	gladLoadGL();

	//check if GLAD was initialized correctly
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		printf("failed to initialize GLAD\n");
		//throw error
	}

	//set window size
	glViewport(0, 0, window->getWidth(), window->getHeight());
	//set clear color
	glClearColor(0.0f, 0.5f, 0.5f, 1.0f);

	//compile shader code
	shaderProgram = new shaderBase("Assets/Shaders/myShader.vs", "Assets/Shaders/myShader_f.fs");

	//load sprite or geometry data to load
	// 
	
	//convert into a usable graphicObject class
	//it needs to be able to move around on screen
	//triangle shape
	
	vector<vertex> vertices = {
		vertex(vect3(-1.0f,  -1.0f,  0.f, 1.f,  1.f, 1.f, 0.0f,  0.0f)),
		vertex(vect3(1.0f, -1.0f, 0.f, 1.f,  1.f, 1.f, 1.0f,0.0f)),
		vertex(vect3(1.0f, 1.0f, 0.f, 1.f,  1.f, 1.f, 1.0f,1.0f)),
		vertex(vect3(-1.0f, 1.0f, 0.f, 1.f,  1.f, 1.f, 0.0f, 1.0f))
	};

	vector<int> indices = {  // note that we start from 0!
		0, 1, 2,   // first triangle
		3, 0, 2  
	};

	triWorld = matrix4(vector4(0, 0, -10, 1));
	triWorld2 = matrix4(vector4(32+16, 32+16, 0, 1));
	triWorld3 = matrix4(vector4(-10, 0, -10, 1));
	
	triWorld2 = triWorld2 * scaleMat(32, 32, 1);
	triWorld3 = triWorld2 * scaleMat(32, 32, 1);

	gObj = new graphicsObject(shaderProgram,vertices,indices,vector4(0,0,0,1),"Assets/Sprites/test_0.png");

	 
	//gObj2 = new graphicsObject(shaderProgram, gObj->VAO, gObj->VBO, gObj->EBO, vector4(5, 5, -10,1));
	
	cam = new camera();;

	perspectiveMatrix = computeProjectionMatrix(window->getWidth(),window->getHeight(),45.f,0.1f,1000.0f);
	
}

void key_callback(GLFWwindow* win, int key, int scanCode, int action, int mods)
{
	if (key == GLFW_KEY_W && action == GLFW_PRESS)
	{
		printf("W key pressed -\n");
	}

	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
	{
		printf("game closed\n");
		glfwSetWindowShouldClose(win, 1);
	} 
}


void opengl_app::update()
{
	//The main loop for the game....
	//perhaps if i was using SDL I would repalce this with an SDL call
	//I want to make a graphics toolset with opengl to call from engine code
	
	//NOTE: -------------------------------------------------------------------
	//opengl while loop is not required to draw objects
	//
	//when I want to bring over the graphisc library
	//I will have to place   opengl rendering calls in the game engine loop
	//and clean up the opengl data when the game closes


	glfwPollEvents();
}

void opengl_app::draw()
{
	//TODO: encapsulate open gl render commands into their own function outside of loop
	//have a function that calls swapbuffer and clear color
	while (!glfwWindowShouldClose(window->getWindow()))
	{
		update();

		glClear(GL_COLOR_BUFFER_BIT);
		shaderProgram->use();

		//glBindVertexArray(VAO);
		float time = glfwGetTime();
		float colorValue = (sin(time) / 2);
		float colorValue2 = (cos(time) / 2);

		vector4 cameraPos = vector4(0, 0, -1, 1);
		vector4 cameraFWD = vector4(0, 0, -1, 0.0f);

		float cameraPitch = 0;
		float cameraYaw = 0;
		float cameraRoll = 0;

		matrix4 viewMatrix = translationMat(cameraPos) * rotateXMat(cameraPitch) * rotateYMat(cameraYaw) * rotateZMat(cameraRoll);

		matrix4 orthoView;
		float orthoAspectRatio = window->getWidth() / window->getHeight();
		matrix4 orthoPersp = computeOrthographicMatrix(0, window->getWidth(), 0, window->getHeight(), 0.1f, 10.0f);

		//gObj->render(orthoPersp, viewMatrix, triWorld2, colorValue, -colorValue, colorValue2, GL_FILL);

		float sprtOffset = 64;
		
		for (int i = 0; i < 13; i++)
		{
			gObj->render(orthoPersp, viewMatrix, matrix4(sprtOffset, sprtOffset + (96 * i), 0.0f) * scaleMat(64, 64, 0), 0.5, 0.5, 0.5, GL_FILL);
		}
		//gObj->render(perspectiveMatrix, viewMatrix, colorValue, -colorValue, colorValue2, GL_FILL);

		glfwSetKeyCallback(window->getWindow(), key_callback);

		glfwSwapBuffers(window->getWindow());
	}
}


void opengl_app::terminate()
{
	//closes the glad window
	glfwDestroyWindow(window->getWindow());
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

	//delete objects
	delete window;

	//terminate glfw
	glfwTerminate();
	delete shaderProgram;
	//destroy object
	delete this;
}