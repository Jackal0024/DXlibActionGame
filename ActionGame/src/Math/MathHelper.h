#pragma once
#include<dxlib.h>

class MathHelper
{
public:
	static float Rad2Deg();
	static float Deg2Rad();
	static float Rad2Deg(float rad);
	static float Deg2Rad(float deg);
};

float  MathHelper::Rad2Deg()
{
	return (180 / DX_PI);
}

float  MathHelper::Deg2Rad()
{
	return (DX_PI / 180);
}

float  MathHelper::Rad2Deg(float rad)
{
	return rad * (180 / DX_PI);
}

float  MathHelper::Deg2Rad(float deg)
{
	return deg * (DX_PI / 180);
}