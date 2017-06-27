/*
*�g���b�v�X�s�A�[�N���X
*�T�v�F�g���b�v�X�s�A�[�̊Ǘ�������N���X
*/
#pragma once

#include"../../Base/Actor.h"

class BlackSpear : public Actor
{
public:
	//�R���X�g���N�^
	BlackSpear(IWorld * world, Vector3 position, Tag tag,float atk);
	//�f�X�g���N�^
	~BlackSpear();
private:
	//�X�V����
	void onUpdate(float deltaTime) override;
	//�`�揈��
	void onDraw() const override;
	//�����������̔���
	void onCollide(Actor& other) override;

private:
	Vector3 mToPos; //�ړI�̏ꏊ
	Vector3 mFromPos;
	int mModelHandle;
	float mTimer;
	float mAtkPower;
	bool mHit;

private:
	//���@���̂̍U����
	const float MAGICPOWER = 20;

};
