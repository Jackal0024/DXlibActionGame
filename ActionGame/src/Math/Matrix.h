#pragma once
#include"DxLib.h"

class Matrix : public MATRIX
{
public:
	Matrix(float m11_, float m12_, float  m13_, float m14_,
		float  m21_, float  m22_, float  m23_, float  m24_, 
		float  m31_, float  m32_, float  m33_, float  m34_, 
		float  m41_, float  m42_, float  m43_, float  m44_
		);
	Matrix(MATRIX m);
};