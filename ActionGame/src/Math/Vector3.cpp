#include "Vector3.h"

Vector3::Vector3()
{
	x = 0, y = 0, z = 0;
}

Vector3::Vector3(float x_, float y_ , float z_)
{
	x = x_, y = y_, z = z_;
}

Vector3::Vector3(VECTOR v)
{
	x = v.x, y = v.y, z = v.z;
}

float Vector3::Length() const
{
	return VSize(*this);
}

VECTOR Vector3::Normalize()
{
	return Normalize(*this);
}

VECTOR Vector3::Lerp(VECTOR & start, VECTOR & end, float amount)
{
	if (amount < 0.0f) {
		amount = 0.0f;
	}
	else if (amount > 1.0f) {
		amount = 1.0f;
	}
	return start * (1.0f - amount) + end * amount;
}

VECTOR Vector3::Normalize(VECTOR & v)
{
	float len = VSize(v);
	if (len != 0.0f)
	{
		v = v / len;
	}
	return v;
}

