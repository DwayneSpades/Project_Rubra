#pragma once
#include "vector.h"
#include "matrix.h"

#include <iostream>
#include <assert.h>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <vector>
//wrapper classes
#include "window_settings.h"

class shaderBase;
class graphicsObject;
class camera;

class opengl_app
{

public:
	//Big Four
	opengl_app() = default;
	opengl_app(opengl_app& ptr) = default;
	opengl_app& operator = (opengl_app& ptr) = default;
	~opengl_app() = default;

	void load();
	void update();
	void draw();
	void terminate();

	vector4 tmp;
	shaderBase* shaderProgram = nullptr;
	graphicsObject* gObj =nullptr;
	graphicsObject* gObj2 = nullptr;
	
	camera* cam = nullptr;

	matrix4 perspectiveMatrix;

	matrix4 triWorld;
	matrix4 triWorld2;
	matrix4 triWorld3;

private:
	window_settings* window;
	unsigned int vertexShader;
	unsigned int fragmentShader;

};