#include "vector.h"
#include <math.h>

//VECTOR - 2 ------------------------------------------------------------------------------

vector2::vector2(float _x,float _y) 
{
	x = _x;
	y = _y;
}
 
vector2& vector2::operator+=(vector2& ptr)
{
	this->x += ptr.x;
	this->y += ptr.y;

	return *this;
}

vector2& vector2::operator-=(vector2& ptr)
{
	this->x -= ptr.x;
	this->y -= ptr.y;

	return *this;
}

vector2 vector2::operator+ (const vector2& ptr) const
{
	return vector2(this->x + ptr.x, this->y + ptr.y);
}

vector2 vector2::operator - (const vector2& ptr) const
{
	return vector2(this->x - ptr.x, this->y - ptr.y);
}

vector2 vector2::operator * (const vector2& ptr) const
{
	return vector2(this->x * ptr.x, this->y * ptr.y);
}

vector2 vector2::operator * (const float num) const
{
	return vector2(this->x * num, this->y * num);
}

vector2 vector2::operator / (const vector2& ptr) const
{
	return vector2(this->x / ptr.x, this->y / ptr.y);
}

vector2 vector2::operator / (const float num) const
{
	return vector2(this->x / num, this->y / num);
}

float vector2::dotProduct(vector2 a, vector2 b)
{
	return ((a.x * b.x) + (b.y * a.y));
}

float vector2::crossProduct(vector2 a, vector2 b)
{
	return ((a.x * b.y) - (a.y * b.x));
}

float vector2::magnitude()
{
	return sqrtf((this->x * this->x) + (this->y * this->y));
}

vector2 vector2::normalize()
{
	return *this / magnitude();
}

//VECTOR - 4 ------------------------------------------------------------------------------

vector4::vector4(float _x, float _y,float _z,float _w)
{
	x = _x;
	y = _y;
	z = _z;
	w = _w;
}

vector4 vector4::operator=(const vector4& ptr)
{
	x = ptr.x;
	y = ptr.y;
	z = ptr.z;
	w = ptr.w;

	return *this;
}

vector4& vector4::operator+=(vector4& ptr)
{
	this->x += ptr.x;
	this->y += ptr.y;
	this->z += ptr.z;
	this->w += ptr.w;

	return *this;
}

vector4& vector4::operator-=(vector4& ptr)
{
	this->x -= ptr.x;
	this->y -= ptr.y;
	this->z -= ptr.z;
	this->w -= ptr.w;

	return *this;
}

vector4 vector4::operator+ (const vector4& ptr) const
{
	return vector4(this->x + ptr.x, this->y + ptr.y, this->z + ptr.z);
}

vector4 vector4::operator - (const vector4& ptr) const
{
	return vector4(this->x - ptr.x, this->y - ptr.y, this->z - ptr.z);
}

vector4 vector4::operator * (const vector4& ptr) const
{
	return vector4(this->x * ptr.x, this->y * ptr.y, this->z * ptr.z, this->w * ptr.w);
}

vector4 vector4::operator * (const float num) const
{
	return vector4(this->x * num, this->y * num, this->z * num, this->w * num);
}

vector4 vector4::operator / (const vector4& ptr) const
{
	return vector4(this->x / ptr.x, this->y / ptr.y, this->z / ptr.z, this->w / ptr.w);
}

vector4 vector4::operator / (const float num) const
{
	return vector4(this->x / num, this->y / num, this->z / num, this->w / num);
}

float vector4::dotProduct(vector4 b)
{
	return ((this->x * b.x) + (this->y * b.y) + (this->z* b.z) + (this->w * b.w));
}

vector4 vector4::crossProduct(vector4 b)
{
	return vector4(((this->y * b.z) - (this->z*b.y)), -((this->x*b.z) - (this->z*b.x)), ((this->x*b.y) - (this->y*b.x)));
}

float vector4::magnitude()
{
	return sqrtf((this->x * this->x) + (this->y * this->y) + (this->z * this->z) + (this->w * this->w));
}

vector4 vector4::normalize()
{
	return *this / magnitude();
}

