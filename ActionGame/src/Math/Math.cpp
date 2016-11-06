#include "Math.h"

float Math::lerp(float a, float b, float t)
{
	return a + t * (b - a);
}

float Math::ToRad(float deg)
{
	return deg * (DX_PI / 180);
}

float Math::ToDeg(float rad)
{
	return rad * (180 / DX_PI);
}
