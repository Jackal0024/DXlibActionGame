/*
*フェードエフェクト
*概要：フェードを管理するクラス
*/
#pragma once

#include"../Base/Actor.h"
#include<string>

class Fadeeffect : public Actor
{
public:
	//コンストラクタ
	Fadeeffect(IWorld* world, float start, float end,float time ,int color = GetColor(255,255,255));
	//画像でフェードの処理するときのコンストラクタ
	Fadeeffect(IWorld* world, float start, float end, float time, std::string filename);
	//デストラクタ
	~Fadeeffect();
	//更新処理
	void onUpdate(float deltaTime) override;
	//描画処理
	void onDraw() const override;
	//終了しているか
	bool IsEnd();

private:
	int mTextureHandle;
	float mAlpha;
	float mStartAlpha;
	float mEndAlpha;
	float mTime;
	float mTimer;
	int mColor;
	bool isFadeIn;
	bool isFadeOut;
};