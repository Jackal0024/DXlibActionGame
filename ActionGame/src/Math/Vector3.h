#ifndef VECTOR3_H_
#define VECTOR3_H_

#include"DxLib.h"

class Vector3 : public VECTOR
{
public:
	Vector3();
	Vector3(float x_ , float y_ , float z_);
	Vector3(const VECTOR& v);
	operator VECTOR() const {
		return{ x, y, z };
	}
	float Length() const;
	VECTOR Normalize();
	static VECTOR Lerp(VECTOR& start, VECTOR& end, float amount);
	static VECTOR Normalize(VECTOR& v);
};

#endif
