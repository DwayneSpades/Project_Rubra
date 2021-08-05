#pragma once

#include "matrix.h"
#include "vector.h"
#include <vector>

class shaderBase;
class model;

//this is a base class for the graphics objects
//each graphics object will be created per shader to ensure each graphic element can 
//have their vertex attribute data be consistant


class graphicsObject 
{

public:
	//bigfour
	graphicsObject() = default;
	//copy data
	graphicsObject(shaderBase* shader, unsigned int vao, unsigned int vbo, unsigned int ebo, vector4 pos);
	
	//instantiate new model data	
	graphicsObject(shaderBase* shader, vector<vertex> verts, vector<int> inds, vector4 pos,const char* s);

	//methods
	void render(matrix4 projectionMatrix, matrix4 viewMatrix, float r, float g, float b, GLenum mode);

	void render(matrix4 projectionMatrix, matrix4 viewMatrix, matrix4 pos, float r, float g, float b, GLenum mode);

	//store the world matrix of the object
	matrix4 world;
	
	//store the vertices and indices used by the object

	//store a reference to the shader the graphics object uses for rendering
	

private:
	vector<vertex> vertices;
	vector<int> indices;
	
	shaderBase* _shader;

	//stor texture
	unsigned int texture;
	//store VAO 
	unsigned int VAO;
	//store VBO
	unsigned int VBO;
	//store EBO
	unsigned int EBO;

	
	
};