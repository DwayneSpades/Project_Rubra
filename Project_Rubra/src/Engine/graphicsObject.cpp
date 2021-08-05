#include "shaderBase.h"
#include "graphicsObject.h"
#include "stb_image.h"

//possible optimization: loading model data once and pulling that info to render onto multiple seperate objects

//NOTE: 
//- only one VAO is required to store the model data
//- individual graphics object require unique VBO's that will copy data from the VAO
graphicsObject::graphicsObject(shaderBase* s, unsigned int vao, unsigned int vbo, unsigned int ebo, vector4 pos)
{
	world.setPosition(pos);
	_shader = s;

	//store model data
	VAO = vao;
	VBO = vbo;
	EBO = ebo;

}


graphicsObject::graphicsObject(shaderBase* shader, vector<vertex> verts, vector<int> inds, vector4 pos, const char* s)
{
	//set data that's specific to the graphic object's shader type
	//process for drawing an object in openGL
	
	//set mesh data
	vertices = verts;
	indices = inds;

	//initialize the Vertex Buffer Object - it stores the vertices for objects
	world.setPosition(pos);

	_shader = shader;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);
	//initialize the Vertex Array Object - it stores vertex attirbute calls
	glBindVertexArray(VAO);

	//1: copy vertex data to a buffer to send to gpu
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(verts), &vertices[0], GL_STATIC_DRAW);

	//initialize Element Buffer Object - its purpose is to store the indices for the model
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(inds), &indices[0], GL_STATIC_DRAW);

	//2: set vertex attributes that the shader is going to use
	// 	this shader has two vertex attributes defined
	// 	   attirbute 0: vertex position
	// 	   attribute 1: vertex color
	
	//size of my custom vector class will have the correct size for the drawing data
	//linking vertex attributes
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(vect3), (void*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(vect3), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(vect3), (void*)(6 * sizeof(float)));
	glEnableVertexAttribArray(2);

	//do something about textures?????
	glGenTextures(1, &texture);

	//initialize texture so it can be loaded
	//unsigned int texture;
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);

	// set the texture wrapping/filtering options (on the currently bound texture object)
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	// load and generate the texture
	int width, height, nrChannels;
	unsigned char* data = stbi_load(s, &width, &height, &nrChannels, STBI_rgb_alpha);

	if (data)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		std::cout << "Failed to load texture" << std::endl;
	}
	stbi_image_free(data);


}

void graphicsObject::render(matrix4 projectionMatrix, matrix4 viewMatrix, float r,float g, float b, GLenum mode) 
{
	//3: activate shader program to use for rendering...
	// 	   its sort of like setting a shader to current context
	_shader->use(); 

	// draw the second triangle 
	matrix4 finalMatrix = projectionMatrix * viewMatrix * world;

	_shader->setVect3("myColor", r, g, b);
	_shader->setMat4("projectionMat", finalMatrix);
	
	//set drawing mode
	glPolygonMode(GL_FRONT_AND_BACK, mode);

	// draw mesh
	glBindVertexArray(VAO);
	glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
}

//may be able to draw multiple objects at once????
void graphicsObject::render(matrix4 projectionMatrix, matrix4 viewMatrix, matrix4 pos, float r, float g, float b, GLenum mode)
{
	//3: activate shader program to use for rendering...
	// 	   its sort of like setting a shader to current context
	_shader->use();

	// draw the second triangle 
	matrix4 finalMatrix = projectionMatrix * viewMatrix * pos;

	_shader->setVect3("myColor", r, g, b);
	_shader->setMat4("projectionMat", finalMatrix);

	

	// draw mesh
	
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	//bind the texture so it can display
	glBindTexture(GL_TEXTURE_2D,texture);

	//set drawing mode
	glPolygonMode(GL_FRONT_AND_BACK, mode);

	glBindVertexArray(VAO);

	glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
}
