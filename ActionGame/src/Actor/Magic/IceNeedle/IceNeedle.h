/*
*�A�C�X�j�[�h���N���X
*�T�v�F�n�ʂ���˂��グ��X�̖��@
*/
#pragma once

#include"../../Base/Actor.h"
#include"../../../Effect/Base/Effect.h"

class IceNeedle : public Actor
{
public:
	//�R���X�g���N�^
	IceNeedle(IWorld* world, Vector3 position,Vector3 velocity,int num,Tag tag, float atk);

private:
	//�X�V����
	void onUpdate(float deltaTime) override;
	//�`�揈��
	void onDraw() const override;
	//�ڐG���̏���
	void onCollide(Actor& other) override;

private:
	Vector3 mVelocity;
	Vector3 mDestination; //�ړI�n
	float mLifeTimer_;
	int mNum;
	int mModelHandle;
	float mAtkPower;
	bool isNext;
	bool mHit = false;
	IEffect mIceEffect;

private:
	//���@���̂̍U����
	const float MAGICPOWER = 20;

};