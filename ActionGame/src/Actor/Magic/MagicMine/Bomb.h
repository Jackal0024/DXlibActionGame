/*
*ボスクラス
*概要：マジックマインクラスから生成される爆風のクラス
*/
#pragma once

#include"../../Base/Actor.h"
#include"../../../Effect/Base/Effect.h"

class Bomb : public Actor
{
public:
	Bomb(IWorld* world, Vector3 position,Tag tag,float atk);
	~Bomb();
private:
	void onUpdate(float deltaTime) override;
	void onDraw() const override;
	void onCollide(Actor& other) override;
private:
	int mModelHandle;
	float mTimer;
	float mAtkPower;
	bool mHit;
	IEffect mBombEffect;

private:
	//魔法自体の攻撃力
	const float MAGICPOWER = 40;

};
