/*
*アイスニードルクラス
*概要：地面から突き上げる氷の魔法
*/
#pragma once

#include"../../Base/Actor.h"
#include"../../../Effect/Base/Effect.h"

class IceNeedle : public Actor
{
public:
	//コンストラクタ
	IceNeedle(IWorld* world, Vector3 position,Vector3 velocity,int num,Tag tag, float atk);

private:
	//更新処理
	void onUpdate(float deltaTime) override;
	//描画処理
	void onDraw() const override;
	//接触時の処理
	void onCollide(Actor& other) override;

private:
	Vector3 mVelocity;
	Vector3 mDestination; //目的地
	float mLifeTimer_;
	int mNum;
	int mModelHandle;
	float mAtkPower;
	bool isNext;
	bool mHit = false;
	IEffect mIceEffect;

private:
	//魔法自体の攻撃力
	const float MAGICPOWER = 20;

};