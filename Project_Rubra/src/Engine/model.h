#pragma once

class model
{
public:
	model() =default;
	model(float* verts, float* ind);

		//pointer to arrays
	float* vertices;
	float* indices;
private:


};