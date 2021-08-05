#include "shaderBase.h"
#include "matrix.h"

shaderBase::shaderBase(const char* vertexPath, const char* fragmentPath) 
{
	//retreive source code characters from shaders
	string vertexCode;
	string fragmentCode;
	ifstream vShaderFile;
	ifstream fShaderFile;

	//ensuer ifstream objects can throw exceptions
	vShaderFile.exceptions(ifstream::failbit | ifstream::badbit);
	fShaderFile.exceptions(ifstream::failbit | ifstream::badbit);
	try 
	{
		//openfile
		vShaderFile.open(vertexPath);
		fShaderFile.open(fragmentPath);
		stringstream vShaderStream, fShaderStream;

		//read the file buffers
		vShaderStream << vShaderFile.rdbuf();
		fShaderStream << fShaderFile.rdbuf();

		//close the files
		vShaderFile.close();
		fShaderFile.close();

		//convert strsam into string
		vertexCode = vShaderStream.str();
		fragmentCode = fShaderStream.str();
	}
	catch(ifstream::failure e)
	{
		printf("ERROR::UNABLE_TO_READ_SHADER_FILE\n");
	}

	const char* vShaderCode = vertexCode.c_str();
	const char* fShaderCode = fragmentCode.c_str();

	// compile the shaders

	unsigned int vertex, fragment;
	int success;
	const int numChar = 512;
	char infoLog[numChar];

	//veretex shader
	vertex = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertex, 1, &vShaderCode, nullptr);
	glCompileShader(vertex);

	glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);
	if(!success)
	{
		glGetShaderInfoLog(vertex, numChar, nullptr, infoLog);
		printf("ERROR - vertex shader failed compilation: %s\n", infoLog);
	}

	//fragment shader
	fragment = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragment, 1, &fShaderCode, nullptr);
	glCompileShader(fragment);

	glGetShaderiv(fragment, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(fragment, numChar, nullptr, infoLog);
		printf("ERROR - fragment shader failed compilation: %s\n", infoLog);
	}

	ID = glCreateProgram();
	glAttachShader(ID, vertex);
	glAttachShader(ID, fragment);
	glLinkProgram(ID);

	//print linking errors
	glGetProgramiv(ID, GL_LINK_STATUS, &success);
	if(!success)
	{
		glGetProgramInfoLog(ID, numChar, nullptr, infoLog);
		printf("Shader program failed to link : %s\n", infoLog);
	}

	//delete shaders since they are linked info the program now and are no longer needed
	glDeleteShader(vertex);
	glDeleteShader(fragment);

}

void shaderBase::use()
{
	glUseProgram(ID);
}

void shaderBase::setBool(const string &name, bool value) const
{
	glUniform1i(glGetUniformLocation(ID, name.c_str()), (int)value);
}

void shaderBase::setInt(const string& name, int value) const
{
	glUniform1i(glGetUniformLocation(ID, name.c_str()), value);
}

void shaderBase::setFloat(const string& name, float value) const
{
	glUniform1f(glGetUniformLocation(ID, name.c_str()),value);
}

void shaderBase::setVect3(const string& name, float x, float y, float z)
{
	glUniform3f(glGetUniformLocation(ID, name.c_str()), x, y, z);
}

void shaderBase::setVect4(const string& name, float x, float y, float z, float w) 
{
	glUniform4f(glGetUniformLocation(ID, name.c_str()), x, y, z, w);
}

void shaderBase::setMat4(const string& name, matrix4 mat)
{
	float matrx[4][4];
	matrx[0][0] = mat.row0.x;
	matrx[0][1] = mat.row0.y;
	matrx[0][2] = mat.row0.z;
	matrx[0][3] = mat.row0.w;

	matrx[1][0] = mat.row1.x;
	matrx[1][1] = mat.row1.y;
	matrx[1][2] = mat.row1.z;
	matrx[1][3] = mat.row1.w;

	matrx[2][0] = mat.row2.x;
	matrx[2][1] = mat.row2.y;
	matrx[2][2] = mat.row2.z;
	matrx[2][3] = mat.row2.w;

	matrx[3][0] = mat.row3.x;
	matrx[3][1] = mat.row3.y;
	matrx[3][2] = mat.row3.z;
	matrx[3][3] = mat.row3.w;

	glUniformMatrix4fv(glGetUniformLocation(ID, name.c_str()),1,false,(float*)matrx);
}