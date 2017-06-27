/*
*ＨＰバークラス
*概要：ＨＰバーのＵＩ管理
*/
#pragma once
#include"../../Base/Actor.h"

class HPBar :public  Actor
{
public:
	//コンストラクタ
	HPBar(IWorld* world, Vector3 position);
	//デストラクタ
	~HPBar();
	//更新処理
	void onUpdate(float deltaTime) override;
	//描画処理
	void onDraw() const override;
private:
	float mMaxHP;
	float mHPValue;

	float mPrevHP;
	Vector3 mSlipBar_rb;
};
