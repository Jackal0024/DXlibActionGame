/*
*ゴブリン攻撃クラス
*概要：ゴブリンの攻撃判定のクラス
*/
#pragma once

#include"../../Base/Actor.h"

class GoblinAttack : public Actor
{
public:
	GoblinAttack(IWorld* world, const Vector3& position,Vector3 velocity,float delay,float Atk);
	void onUpdate(float deltaTime) override;
	void onDraw() const override;
	void onCollide(Actor& othr) override;

private:
	float mDelay;
	float mTimer;
	float mAtk;
	Vector3 mVelocity;
};
