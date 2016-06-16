#ifndef VECTOR3_H_
#define VECTOR3_H_

#include"DxLib.h"

class Vector3 : public VECTOR
{
public:
	Vector3();
	Vector3(float x_ , float y_ , float z_);
	Vector3(VECTOR v);
	float Length() const;
};

#endif
