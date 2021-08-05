#pragma once

struct vect3
{
	vect3() = default;
	vect3(float _x, float _y, float _z, float _r, float _g, float _b, float _u, float _v)
	{
		x = _x;
		y = _y;
		z = _z;
		r = _r;
		g = _g;
		b = _b;
		u = _u;
		v = _v;
	}

	float x;
	float y;
	float z;
	float r;
	float g;
	float b;
	float u;
	float v;
};

struct vertex
{
	vertex() = default;
	vertex(float _x, float _y, float _z, float _r, float _g, float _b, float _u, float _v) 
	{
		pos = vect3(_x, _y, _z, _r, _g, _b, _u, _v);
	}

	vertex(vect3 p)
	{
		pos = p;
		//color = c;
	}
	vect3 pos;
	//vect3 color;
};

class vector2 
{
public:
	//Big Four
	vector2() = default;
	vector2(float x, float y);
	//vector2(vector2& ptr) = default;
	vector2& operator = (vector2& ptr) = default;
	~vector2()=default;

	

	
//math operators

	//addition - subtraction
	vector2& operator += (vector2& ptr);
	vector2& operator -= (vector2& ptr);
	vector2 operator + (const vector2& ptr) const;
	vector2 operator - (const vector2& ptr) const;

	//multiplication
	vector2 operator * (const vector2& ptr) const;
	vector2 operator * (const float num) const;
	//division
	vector2 operator / (const vector2& ptr) const;
	vector2 operator / (const float num) const;

	//linear algebra functions

	//dot product
	float dotProduct(vector2 a, vector2 b);
	//cross product
	float crossProduct(vector2 a, vector2 b);
	//magnitude
	float magnitude();
	//normalize
	vector2 normalize();
	
	//position
	float x;
	float y;
	
private:


};

class vector4
{
public:
	//Big Four
	vector4() = default;
	vector4(float x, float y, float z, float w = 0);
	//vector2(vector2& ptr) = default;
	//vector4& operator = (vector4& ptr) = default;
	vector4 operator = (const vector4& ptr);
	~vector4()=default;

	//math operators

	//addition - subtraction
	vector4& operator += (vector4& ptr);
	vector4& operator -= (vector4& ptr);
	vector4 operator + (const vector4& ptr) const;
	vector4 operator - (const vector4& ptr) const;

	//multiplication
	vector4 operator * (const vector4& ptr) const;
	vector4 operator * (const float num) const;
	//division
	vector4 operator / (const vector4& ptr) const;
	vector4 operator / (const float num) const;

	//linear algebra functions

	//dot product
	float dotProduct(vector4 b);
	//cross product
	vector4 crossProduct(vector4 b);
	//magnitude
	float magnitude();
	//normalize
	vector4 normalize();

	//position
	float x;
	float y;
	float z;
	float w;

private:


};