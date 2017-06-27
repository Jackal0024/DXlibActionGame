/*
*フラッシュエフェクトクラス
*概要：画面にフラッシュエフェクトをつける
*/
#pragma once

#include"../Base/Actor.h"
#include<string>

class FlashEffect : public Actor
{
public:
	//コンストラクタ
	FlashEffect(IWorld* world, float end, float time, int color = GetColor(255, 255, 255));
	//デストラクタ
	~FlashEffect();
	//更新処理
	void onUpdate(float deltaTime) override;
	//描画処理
	void onDraw() const override;

private:
	int mColor;
	float mAlpha;
	float mTime;
	float mTimer;
	float mEndAlpha;
	bool isFinale;

};

