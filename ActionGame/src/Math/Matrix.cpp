#include "Matrix.h"

Matrix::Matrix(float m11_, float m12_, float m13_, float m14_, float m21_, float m22_, float m23_, float m24_, float m31_, float m32_, float m33_, float m34_, float m41_, float m42_, float m43_, float m44_)
{
	m[0][0] = m11_, m[0][1] = m12_, m[0][2] = m13_, m[0][3] = m14_;
	m[1][0] = m21_, m[1][1] = m22_, m[1][2] = m23_, m[1][3] = m24_;
	m[2][0] = m31_, m[2][1] = m32_, m[2][2] = m33_, m[2][3] = m34_;
	m[3][0] = m41_, m[3][1] = m42_, m[3][2] = m43_, m[3][3] = m44_;
}

Matrix::Matrix(MATRIX m_)
{
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			m[i][j] = m_.m[i][j];
		}
	}
}

VECTOR Matrix::GetPosition() const
{
	return VGet(m[3][0], m[3][1], m[3][2]);
}

VECTOR Matrix::GetLeft() const
{
	return VGet(m[0][0], m[0][1], m[0][2]);
}

VECTOR Matrix::GetForward() const
{
	return VGet(m[2][0], m[2][1], m[2][2]);
}

VECTOR Matrix::GetUp() const
{
	return VGet(m[1][0], m[1][1], m[1][2]);
}

MATRIX Matrix::SetPosition(VECTOR pos)
{
	m[3][0] = pos.x;
	m[3][1] = pos.y;
	m[3][2] = pos.z;
	return *this;
}

MATRIX Matrix::Translate(VECTOR v) const
{
	MATRIX result = {
		1.0f, 0.0f, 0.0f, 0.0f,
		0.0f, 1.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 1.0f, 0.0f,
		v.x, v.y, v.z, 1.0f
	};
	return result;
}

VECTOR Matrix::Transform(VECTOR v) const
{
	float w = v.x * m[0][3] + v.y * m[1][3] + v.z * m[2][3] + m[3][3];
	VECTOR result = {
		(v.x * m[0][0] + v.y * m[1][0] + v.z * m[2][0] + m[3][0]) / w,
		(v.x * m[0][1] + v.y * m[1][1] + v.z * m[2][1] + m[3][1]) / w,
		(v.x * m[0][2] + v.y * m[1][2] + v.z * m[2][2] + m[3][2]) / w
	};
	return result;
}

VECTOR Matrix::GetScale() const
{
	return VECTOR(VGet(VSize(GetLeft()), VSize(GetUp()), VSize(GetForward())));
}

MATRIX Matrix::SetScale(VECTOR scale)
{
	m[0][0] = scale.x;
	m[1][1] = scale.y;
	m[2][2] = scale.z;
	return *this;
}
