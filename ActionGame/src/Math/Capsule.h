/*
*�J�v�Z���N���X
*�T�v�F�J�v�Z���̓����蔻��N���X
*/
#ifndef CAPSULE_H_
#define CAPSULE_H_

#include"Line.h"
#include"Matrix.h"

class Capsule
{
public:
	//�R���X�g���N�^
	Capsule(const Line& line, const float radius);
	//�R���X�g���N�^��������J�v�Z�������
	Capsule(const Vector3 length,const float radius);
	//�f�X�g���N�^
	~Capsule();
	//�ڐG����
	bool Intersects(const Capsule& other) const;
	//�ړ�����
	Capsule Move(const Vector3& position) const;
	//�ړ������Q
	Capsule Translate(const Vector3& position) const;
	//�ړ���]����
	Capsule Transform(const Matrix& matrix)const;
	//�f�o�b�O�\��
	void Draw() const;

public:
	Line mLine;
	float mRadius;
	bool isAlive;
	
public:
	bool CollisionCapsuleAndCapsule(const Capsule & other) const;

};

#endif
