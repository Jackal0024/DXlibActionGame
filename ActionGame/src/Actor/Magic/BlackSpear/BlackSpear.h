/*
*トラップスピアークラス
*概要：トラップスピアーの管理をするクラス
*/
#pragma once

#include"../../Base/Actor.h"

class BlackSpear : public Actor
{
public:
	//コンストラクタ
	BlackSpear(IWorld * world, Vector3 position, Tag tag,float atk);
	//デストラクタ
	~BlackSpear();
private:
	//更新処理
	void onUpdate(float deltaTime) override;
	//描画処理
	void onDraw() const override;
	//当たった時の判定
	void onCollide(Actor& other) override;

private:
	Vector3 mToPos; //目的の場所
	Vector3 mFromPos;
	int mModelHandle;
	float mTimer;
	float mAtkPower;
	bool mHit;

private:
	//魔法自体の攻撃力
	const float MAGICPOWER = 20;

};
