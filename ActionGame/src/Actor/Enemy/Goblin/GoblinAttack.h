/*
*ゴブリン攻撃クラス
*概要：ゴブリンの攻撃判定のクラス
*/
#pragma once

#include"../../Base/Actor.h"

class GoblinAttack : public Actor
{
public:
	//コンストラクタ
	GoblinAttack(IWorld* world, const Vector3& position,Vector3 velocity,float delay,float Atk);
	//更新処理
	void onUpdate(float deltaTime) override;
	//描画処理
	void onDraw() const override;
	//接触時の処理
	void onCollide(Actor& othr) override;

private:
	float mDelay;
	float mTimer;
	float mAtk;
	Vector3 mVelocity;
};
