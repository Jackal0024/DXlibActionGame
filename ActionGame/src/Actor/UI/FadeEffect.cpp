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
	mTimer(0.0),
	mTextureHandle(-1)
{
	mAlpha = mStartAlpha;
}

Fadeeffect::Fadeeffect(IWorld * world, float start, float end, float time, std::string filename):
	mStartAlpha(start),
	mEndAlpha(end),
	mTime(time),
	isFadeIn(false),
	isFadeOut(false),
	mTimer(0.0)
{
	mTextureHandle = LoadGraph(filename.c_str());
	mAlpha = mStartAlpha;
}

Fadeeffect::~Fadeeffect()
{
	DeleteGraph(mTextureHandle);
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
	if(mTextureHandle == -1) DrawBox(0, 0, WIDTH, HEIGHT, mColor, true);
	else DrawGraph(0, 0, mTextureHandle, TRUE);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}

bool Fadeeffect::IsEnd()
{
	return mAlpha == mEndAlpha;
}