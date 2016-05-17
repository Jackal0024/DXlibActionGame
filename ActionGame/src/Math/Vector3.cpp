#include "Vector3.h"

Vector3::Vector3(float x_, float y_, float z_)
{
	x = x_, y = y_, z = z_;
}

Vector3::Vector3(VECTOR v)
{
	x = v.x, y = v.y, z = v.z;
}
