#include "FadeEffect.h"
#include"../../System/ConstantList/WindowSize.h"
#include"../../Math/Math.h"

Fadeeffect::Fadeeffect(IWorld * world, float start, float end, float time, int color):
	Actor(world, "Fade", { 0,0,0 }, Capsule(Vector3(0, 0, 0), 0)),
	mColor(color),
	mStartAlpha(start),
	mEndAlpha(end),
	mTime(time),
	isFadeIn(false),
	isFadeOut(false),
	mTimer(0.0)
{
	mAlpha = mStartAlpha;
}

Fadeeffect::~Fadeeffect()
{
}

void Fadeeffect::onUpdate(float deltaTime)
{
	mTimer = min(mTimer + deltaTime,mTime);
	float f = (mTimer / mTime);
	mAlpha =  Math::lerp(mStartAlpha, mEndAlpha, f);
}

void Fadeeffect::onDraw() const
{
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, mAlpha);
	DrawBox(0, 0, WIDTH, HEIGHT, mColor, true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}

bool Fadeeffect::IsEnd()
{
	return mAlpha == mEndAlpha;
}