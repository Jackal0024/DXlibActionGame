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
	//コンストラクタ
	FireWallParts(IWorld * world, Vector3 position, const Vector3 & Velocity, Tag tag,float atk);
	//デストラクタ
	~FireWallParts();
private:
	//更新処理
	void onUpdate(float deltaTime) override;
	//描画処理
	void onDraw() const override;
	//接触時の処理
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
