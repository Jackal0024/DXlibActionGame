#include "FlashEffect.h"
#include"../../System/ConstantList/WindowSize.h"
#include"../../Math/MathHelper.h"

FlashEffect::FlashEffect(IWorld * world, float end, float time, int color):
	Actor(world, "Flash", { 0,0,0 }, Capsule(Vector3(0, 0, 0), 0)),
	mAlpha(0.0f),
	mTime(time),
	mTimer(0.0f),
	mEndAlpha(end),
	isFinale(false),
	mColor(color)
{
}

FlashEffect::~FlashEffect()
{

}

void FlashEffect::onUpdate(float deltaTime)
{
	if(!isFinale)mTimer = min(mTimer + deltaTime, mTime);
	else mTimer = max(mTimer - deltaTime, 0.0f);
	float f = (mTimer / mTime);
	mAlpha = MathHelper::Lerp(0.0f, mEndAlpha, f);
	if (f >= 1) isFinale = true;
	if (isFinale && f <= 0) Dead();
}

void FlashEffect::onDraw() const
{
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, mAlpha);
	DrawBox(0, 0, WIDTH, HEIGHT, mColor, true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}
