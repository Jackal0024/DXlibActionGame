/*
*ファイアーボール
*概要：ファイアーボールの魔法クラス
*/
#pragma once

#include"../../Base/Actor.h"
#include"../../../Effect/Base/Effect.h"

class FireBall : public Actor
{
public:
	//コンストラクタ
	FireBall(IWorld* world, Vector3 position, const Vector3& Velocity,Tag tag,float atk = 20);
	//デストラクタ
	~FireBall();
private:
	//更新処理
	void onUpdate(float deltaTime) override;
	//描画処理
	void onDraw() const override;
	//当たった時の処理
	void onCollide(Actor& other) override;


private:
	IEffect mEffect;
	int mHandle[32];
	int mIndex;
	float mTimer;
	float mAtkPower;
	Vector3 mVelocity;

private:
	//魔法自体の攻撃力
	const float MAGICPOWER = 5;

};
