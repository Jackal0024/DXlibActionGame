/*
*ゴーレム攻撃クラス
*概要：ゴーレムの攻撃判定クラス
*/
#pragma once
#include"../../Base/Actor.h"

class EnemyArrack : public Actor
{
public:
	//コンストラクタ
	EnemyArrack(IWorld* world, const Vector3& position,Vector3 mVelocity,float Atk);
	//更新処理
	void onUpdate(float deltaTime) override;
	//描画処理
	void onDraw() const override;
	//接触時の処理
	void onCollide(Actor& othr) override;

private:
	float mTimer;
	float mAtk;
	Vector3 mVelocity;
};
