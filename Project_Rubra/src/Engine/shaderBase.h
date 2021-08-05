#ifndef SHADER_BASE_H
#define SHADER_BASE_H

#pragma once

#include <iostream>
#include <assert.h>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
class matrix4;

using namespace std;

class shaderBase 
{
public:
	//big four
	shaderBase() = default;
	shaderBase(shaderBase& ptr) = default;
	shaderBase& operator = (shaderBase& ptr) = default;
	~shaderBase() = default; 


unsigned int ID;
	
	shaderBase(const char* vertexPath, const char* fragmentPath);

	//activation for shader
	void use();

	//utility uniform functions
	void setBool(const string& name, bool value) const;
	void setInt(const string& name, int value) const;
	void setFloat(const string& name, float value) const;

	void setVect3(const string& name, float x, float y, float z);
	void setVect4(const string& name, float x, float y, float z, float w);

	void setMat4(const string& name, matrix4);

private:
	

};

#endif