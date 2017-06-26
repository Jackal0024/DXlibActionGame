/*
*ファイアーウォールのパーツクラス
*概要：ファイアーウォールで発生する火柱の１本
*/
#pragma once
#include"../../Base/Actor.h"
#include"../../../Effect/Base/Effect.h"

class FireWallParts :public  Actor
{
public:
	FireWallParts(IWorld * world, Vector3 position, const Vector3 & Velocity, Tag tag,float atk);
	~FireWallParts();
private:
	void onUpdate(float deltaTime) override;
	void onDraw() const override;
	void onCollide(Actor& other) override;
private:
	int mModelHandle;
	float mTimer;
	Vector3 mVelocity;
	float mAtkPower;
	bool mHit;
	IEffect mFireEffect;

private:
	//魔法自体の攻撃力
	const float MAGICPOWER = 40;

};
