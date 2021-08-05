#pragma once

#include "camera.h"
#include "matrix.h"

class camera
{
public:
	camera() = default;
	camera(camera& ptr) = default;
	~camera()=default;
	
	matrix4 computeProjection();

	matrix4 viewMatrix;
	matrix4 world;

private:

};

inline matrix4 computeProjectionMatrix(float screenW, float screenH, float FOV, float Near,float Far) 
{
	//calculate d
	float windowWidth = screenW;
	float windowHeight = screenH;

	//compute field of view
	float fov = degreesToRadians(FOV);
	float d = 1 / tanf(fov);

	//compute aspect ratio from window size
	float a = windowHeight / windowWidth;
	float d_Over_a = d / a;

	//compute scale
	float A = (Near + Far) / (Near - Far);
	float B = (2 * (Far * Near)) / (Near - Far);

	matrix4 result = matrix4(vector4(d_Over_a, 0, 0, 0), vector4(0, d, 0, 0), vector4(0, 0, A, -1), vector4(0, 0, B, 0));

	return result;
}

inline matrix4 computeOrthographicMatrix(float left,float right,float top, float bottom, float near, float far)
{
	//calculate d
	float m0 = 2 / (right - left);

	//compute field of view
	float m5 = 2 / (top - bottom);
	float m10 = -2 / (far - near);

	//compute aspect ratio from window size
	float m12 = -((right + left) / (right - left));
	float m13 = -((top + bottom) / (top - bottom));

	//compute scale
	float m14 = -((far + near) / (far - near));
	float m15 = 1;

	matrix4 result = matrix4(vector4(m0, 0, 0, 0), vector4(0, m5, 0, 0), vector4(0, 0, m10, 0), vector4(m12, m13, m14, m15));
	result = result * translationMat(left,top,0);
	return result;
}