/*
*�S�[�����U���N���X
*�T�v�F�S�[�����̍U������N���X
*/
#pragma once
#include"../../Base/Actor.h"

class EnemyArrack : public Actor
{
public:
	//�R���X�g���N�^
	EnemyArrack(IWorld* world, const Vector3& position,Vector3 mVelocity,float Atk);
	//�X�V����
	void onUpdate(float deltaTime) override;
	//�`�揈��
	void onDraw() const override;
	//�ڐG���̏���
	void onCollide(Actor& othr) override;

private:
	float mTimer;
	float mAtk;
	Vector3 mVelocity;
};
