/*
*マミー攻撃クラス
*概要：マミーの格闘攻撃の判定を管理
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
