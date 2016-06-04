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
	//���W��Ԃ�
	VECTOR GetPosition() const;
	//�������̃x�N�g����Ԃ�
	VECTOR GetLeft() const;
	//�O�����̃x�N�g����Ԃ�
	VECTOR GetForward() const;
	//������̃x�N�g����Ԃ�
	VECTOR GetUp() const;
	//���W��������
	void   SetPosition(VECTOR pos);
	//���W����ꂽ�s���Ԃ�
	MATRIX Translate(VECTOR pos) const;
	//�����ϊ��Ή��̍��W�ϊ�
	VECTOR Transform(VECTOR v) const;
	//�X�P�[���̎擾
	VECTOR GetScale() const;
};