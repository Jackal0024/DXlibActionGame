/*
*�S�[�����U���N���X
*�T�v�F�S�[�����̍U������N���X
*/
#pragma once
#include"../../Base/Actor.h"

class EnemyArrack : public Actor
{
public:
	EnemyArrack(IWorld* world, const Vector3& position,Vector3 mVelocity,float Atk);
	void onUpdate(float deltaTime) override;
	void onDraw() const override;
	void onCollide(Actor& othr) override;

private:
	float mTimer;
	float mAtk;
	Vector3 mVelocity;
};
