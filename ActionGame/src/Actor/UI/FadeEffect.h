#pragma once

#include"../Base/Actor.h"

class Fadeeffect : public Actor
{
public:
	Fadeeffect(IWorld* world, float start, float end,float time ,int color = GetColor(255,255,255));
	~Fadeeffect();
	void onUpdate(float deltaTime) override;
	void onDraw() const override;

	bool IsEnd();

private:
	float mAlpha;
	float mStartAlpha;
	float mEndAlpha;
	float mTime;
	float mTimer;
	int mColor;
	bool isFadeIn;
	bool isFadeOut;
};