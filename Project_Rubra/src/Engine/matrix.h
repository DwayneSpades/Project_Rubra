#pragma once

#include "vector.h"
#include <math.h>

class matrix4
{
public:
	matrix4();
	matrix4(vector4 r0, vector4 r1, vector4 r2, vector4 r3);
	matrix4(vector4 position);
	matrix4(float x, float y, float z);
	~matrix4() = default;

	//math operations

	vector4 operator * (vector4& ptr);
	matrix4 operator * (matrix4  ptr);
	matrix4 operator * (float& ptr);

	//math functions
	void setPosition(vector4 pos);
	void setPosition(float x, float y, float z);

	//matrix to vect
	
	//matrix container
	 
	vector4 row0;
	vector4 row1;
	vector4 row2;
	vector4 row3;

	float _m0;
	float _m1;
	float _m2;
	float _m3;
	float _m4;
	float _m5;
	float _m6;
	float _m7;
	float _m8;
	float _m9;
	float _m10;
	float _m11;
	float _m12;
	float _m13;
	float _m14;
	float _m15;
	
private:

};

inline float degreesToRadians(float deg)
{
	return deg * (3.1415926535f / 180.0f);
}

inline matrix4 translationMat(float x, float y, float z)
{
	return matrix4(vector4(1, 0, 0, 0), vector4(0, 1, 0, 0), vector4(0, 0, 1, 0), vector4(x, y, z, 1));
}

inline matrix4 translationMat(vector4 tran)
{
	return matrix4(vector4(1,0,0,0),vector4(0,1,0,0),vector4(0,0,1,0),vector4(tran.x,tran.y,tran.z,1));
}

inline matrix4 rotateXMat(float rad)
{
	float sinTheta = sinf(rad);
	float cosTheta = cosf(rad);

	return matrix4(
		vector4(1,0,0,0),
		vector4(0,cosTheta,sinTheta,0),
		vector4(0,-sinTheta,cosTheta,0),
		vector4(0,0,0,1));
}

inline matrix4 rotateYMat(float rad)
{
	float sinTheta = sinf(rad);
	float cosTheta = cosf(rad);

	return matrix4(
		vector4(cosTheta, 0, -sinTheta, 0), 
		vector4(0, 1, 0, 0),
		vector4(sinTheta, 0, cosTheta, 0), 
		vector4(0, 0, 0, 1));
}

inline matrix4 rotateZMat(float rad)
{
	float sinTheta = sinf(rad);
	float cosTheta = cosf(rad);

	return matrix4(
		vector4(cosTheta, sinTheta, 0, 0),
		vector4(-sinTheta, cosTheta, 0, 0), 
		vector4(0, 0, 1, 0), 
		vector4(0, 0, 0, 1));
}

inline matrix4 scaleMat(float scaleX, float scaleY, float scaleZ)
{
	return matrix4(
		vector4(scaleX, 0 ,0, 0),
		vector4(0, scaleY, 0, 0),
		vector4(0, 0, scaleZ, 0),
		vector4(0, 0, 0, 1));
}