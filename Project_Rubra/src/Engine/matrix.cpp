
#include "vector.h"
#include "matrix.h"

matrix4::matrix4()
{
	//identity matrix by default
	row0 = vector4(1.f, 0.f, 0.f, 0.f);
	row1 = vector4(0.f, 1.f, 0.f, 0.f);
	row2 = vector4(0.f, 0.f, 1.f, 0.f);
	row3 = vector4(0.f, 0.f, 0.f, 1.f);

	_m0 = row0.x;
	_m1 = row0.y;
	_m2 = row0.z;
	_m3 = row0.w;

	_m4 = row1.x;
	_m5 = row1.y;
	_m6 = row1.z;
	_m7 = row1.w;

	_m8 = row2.x;
	_m9 = row2.y;
	_m10 = row2.z;
	_m11 = row2.w;

	_m12 = row3.x;
	_m13 = row3.y;
	_m14 = row3.z;
	_m15 = row3.w;
}

matrix4::matrix4(vector4 r0, vector4 r1, vector4 r2, vector4 r3)
{
	row0 = r0;
	row1 = r1;
	row2 = r2;
	row3 = r3;

	_m0 = row0.x;
	_m1 = row0.y;
	_m2 = row0.z;
	_m3 = row0.w;

	_m4 = row1.x;
	_m5 = row1.y;
	_m6 = row1.z;
	_m7 = row1.w;

	_m8 = row2.x;
	_m9 = row2.y;
	_m10 = row2.z;
	_m11 = row2.w;

	_m12 = row3.x;
	_m13 = row3.y;
	_m14 = row3.z;
	_m15 = row3.w;
}

matrix4::matrix4(vector4 pos)
{
	//identity matrix by default
	row0 = vector4(1.f, 0.f, 0.f, 0.f);
	row1 = vector4(0.f, 1.f, 0.f, 0.f);
	row2 = vector4(0.f, 0.f, 1.f, 0.f);
	row3 = vector4(pos.x, pos.y, pos.z, 1.f);
	_m0 = row0.x;
	_m1 = row0.y;
	_m2 = row0.z;
	_m3 = row0.w;

	_m4 = row1.x;
	_m5 = row1.y;
	_m6 = row1.z;
	_m7 = row1.w;

	_m8 = row2.x;
	_m9 = row2.y;
	_m10 = row2.z;
	_m11 = row2.w;

	_m12 = row3.x;
	_m13 = row3.y;
	_m14 = row3.z;
	_m15 = row3.w;
}

matrix4::matrix4(float x, float y, float z)
{
	//identity matrix by default
	row0 = vector4(1.f, 0.f, 0.f, 0.f);
	row1 = vector4(0.f, 1.f, 0.f, 0.f);
	row2 = vector4(0.f, 0.f, 1.f, 0.f);
	row3 = vector4(x, y, z, 1.0f);

	_m0 = row0.x;
	_m1 = row0.y;
	_m2 = row0.z;
	_m3 = row0.w;

	_m4 = row1.x;
	_m5 = row1.y;
	_m6 = row1.z;
	_m7 = row1.w;

	_m8 = row2.x;
	_m9 = row2.y;
	_m10 = row2.z;
	_m11 = row2.w;

	_m12 = row3.x;
	_m13 = row3.y;
	_m14 = row3.z;
	_m15 = row3.w;
}

vector4 matrix4::operator*(vector4& a)
{

	float m0 = vector4(_m0, _m4, _m8, _m12).dotProduct(vector4(a.x, a.y, a.z, a.w));
	float m1 = vector4(_m1, _m5, _m9, _m13).dotProduct(vector4(a.x, a.y, a.z, a.w));
	float m2 = vector4(_m2, _m6, _m10, _m14).dotProduct(vector4(a.x, a.y, a.z, a.w));
	float m3 = vector4(_m3, _m7, _m11, _m15).dotProduct(vector4(a.x, a.y, a.z, a.w));

	vector4 result = vector4(m0, m1, m2, m3);

	return result;
}

void matrix4::setPosition(vector4 pos)
{ 
	row3.x = pos.x;
	row3.y = pos.y;
	row3.z = pos.z;

	_m12 = row3.x;
	_m13 = row3.y;
	_m14 = row3.z;
	//dont change w lol why.... maybe I do need a vect3 class???
}

void matrix4::setPosition(float x, float y, float z)
{
	row3.x = x;
	row3.y = y;
	row3.z = z;

	_m12 = row3.x;
	_m13 = row3.y;
	_m14 = row3.z;
	//dont change w lol why.... maybe I do need a vect3 class???
}


matrix4 matrix4::operator*(float& a)
{

	matrix4 result = matrix4(vector4(_m0, _m1, _m2, _m3) * a, vector4(_m4, _m5, _m6, _m7)*a, vector4(_m8, _m9, _m10, _m11)*a, vector4(_m12, _m13, _m14, _m15)*a);

	return result;
}


matrix4 matrix4::operator*(matrix4 a)
{
	float m0 = vector4(_m0, _m4, _m8, _m12).dotProduct(vector4(a._m0, a._m1, a._m2, a._m3));
	float m4 = vector4(_m0, _m4, _m8, _m12).dotProduct(vector4(a._m4, a._m5, a._m6, a._m7));
	float m8 = vector4(_m0, _m4, _m8, _m12).dotProduct(vector4(a._m8, a._m9, a._m10, a._m11));
	float m12 = vector4(_m0, _m4, _m8, _m12).dotProduct(vector4(a._m12, a._m13, a._m14, a._m15));

	float m1 = vector4(_m1, _m5, _m9, _m13).dotProduct(vector4(a._m0, a._m1, a._m2, a._m3));
	float m5 = vector4(_m1, _m5, _m9, _m13).dotProduct(vector4(a._m4, a._m5, a._m6, a._m7));
	float m9 = vector4(_m1, _m5, _m9, _m13).dotProduct(vector4(a._m8, a._m9, a._m10, a._m11));
	float m13 = vector4(_m1, _m5, _m9, _m13).dotProduct(vector4(a._m12, a._m13, a._m14, a._m15));

	float m2 = vector4(_m2, _m6, _m10, _m14).dotProduct(vector4(a._m0, a._m1, a._m2, a._m3));
	float m6 = vector4(_m2, _m6, _m10, _m14).dotProduct(vector4(a._m4, a._m5, a._m6, a._m7));
	float m10 = vector4(_m2, _m6, _m10, _m14).dotProduct(vector4(a._m8, a._m9, a._m10, a._m11));
	float m14 = vector4(_m2, _m6, _m10, _m14).dotProduct(vector4(a._m12, a._m13, a._m14, a._m15));

	float m3 = vector4(_m3, _m7, _m11, _m15).dotProduct(vector4(a._m0, a._m1, a._m2, a._m3));
	float m7 = vector4(_m3, _m7, _m11, _m15).dotProduct(vector4(a._m4, a._m5, a._m6, a._m7));
	float m11 = vector4(_m3, _m7, _m11, _m15).dotProduct(vector4(a._m8, a._m9, a._m10, a._m11));
	float m15 = vector4(_m3, _m7, _m11, _m15).dotProduct(vector4(a._m12, a._m13, a._m14, a._m15));

	matrix4 result = matrix4(vector4(m0, m1, m2, m3), vector4(m4, m5, m6, m7), vector4(m8, m9, m10, m11), vector4(m12, m13, m14, m15));
	return result;
}