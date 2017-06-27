/*
*�S�u�����U���N���X
*�T�v�F�S�u�����̍U������̃N���X
*/
#pragma once

#include"../../Base/Actor.h"

class GoblinAttack : public Actor
{
public:
	//�R���X�g���N�^
	GoblinAttack(IWorld* world, const Vector3& position,Vector3 velocity,float delay,float Atk);
	//�X�V����
	void onUpdate(float deltaTime) override;
	//�`�揈��
	void onDraw() const override;
	//�ڐG���̏���
	void onCollide(Actor& othr) override;

private:
	float mDelay;
	float mTimer;
	float mAtk;
	Vector3 mVelocity;
};
