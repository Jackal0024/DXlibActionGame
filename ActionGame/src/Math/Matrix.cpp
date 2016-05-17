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
	for (int i = 0; i < sizeof(m_.m) / sizeof(m_.m[0]); i++)
	{
		for (int j = 0; j < sizeof(m_.m) / sizeof(m_.m[0][0]); i++)
		{
			m[i][j] = m_.m[i][j];
		}
	}
}