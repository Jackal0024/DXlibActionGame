#include "DeadTexture.h"
#include"../FadeEffect.h"
#include"WhiteEnd.h"
#include"../../../System/ConstantList/WindowSize.h"

DeadTexture::DeadTexture(IWorld * world, ActorPtr Fade):
	Actor(world, "DeadTexture", { 0,0,0 }, Capsule(Vector3(0, 0, 0), 0)),
	mFade(Fade),
	mAlpha(0.0f),
	mWhite(nullptr)
{
	mTexHandle = LoadGraph("./res/Texture/Dead.png");
}

DeadTexture::~DeadTexture()
{
	DeleteGraph(mTexHandle);
}

void DeadTexture::onUpdate(float deltaTime)
{
	mAlpha += deltaTime * 30;
	if (mAlpha >= 255 && !mWhite)
	{
		mWhite = std::make_shared<WhiteEnd>(mWorld);
		this->AddChild(mWhite);
	}
}

void DeadTexture::onDraw() const
{
	Fadeeffect* temp = (Fadeeffect*)mFade.get();
	if (temp->IsEnd())
	{
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, (int)mAlpha);
		DrawGraph(0, (HEIGHT / 2) - 137, mTexHandle, TRUE);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	}
}
