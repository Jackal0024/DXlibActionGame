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
	//コンストラクタ
	Bomb(IWorld* world, Vector3 position,Tag tag,float atk);
	//デストラクタ
	~Bomb();
private:
	//更新処理
	void onUpdate(float deltaTime) override;
	//描画処理
	void onDraw() const override;
	//当たった時の処理
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
