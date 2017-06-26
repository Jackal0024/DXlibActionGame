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
	Fadeeffect(IWorld* world, float start, float end,float time ,int color = GetColor(255,255,255));
	Fadeeffect(IWorld* world, float start, float end, float time, std::string filename);
	~Fadeeffect();
	void onUpdate(float deltaTime) override;
	void onDraw() const override;

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