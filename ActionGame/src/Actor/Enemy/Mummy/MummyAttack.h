/*
*�}�~�[�U���N���X
*�T�v�F�}�~�[�̊i���U���̔�����Ǘ�
*/
#pragma once
#include"../../Base/Actor.h"

class MummyAttack : public Actor
{
public:
	MummyAttack(IWorld* world, const Vector3& position,float Atk);
	void onUpdate(float deltaTime) override;
	void onDraw() const override;
	void onCollide(Actor& othr) override;

private:
	float mTimer;
	float mAtk;
};
