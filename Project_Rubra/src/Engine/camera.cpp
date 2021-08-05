#include "camera.h"
#include <math.h>
#include "matrix.h"

matrix4 camera::computeProjection()
{
	//calculate d
	float windowWidth = 800;
	float windowHeight = 800;

	//field of view
	float fov = degreesToRadians(45);
	float d = 1 / tanf(fov);

	//compute aspect ratio from window size
	float a = windowHeight / windowWidth;

	float d_Over_a = d/a;

	//compute scale
	float near = .1f;
	float far = 1000.0f;

	float A = (near+far) / (near - far);
	float B = (2*(far*near)) / (near -far);
	
	matrix4 result = matrix4(vector4(d_Over_a, 0, 0, 0), vector4(0, d, 0, 0), vector4(0, 0, A, -1), vector4(0, 0, B, 0));

	return result;
}

