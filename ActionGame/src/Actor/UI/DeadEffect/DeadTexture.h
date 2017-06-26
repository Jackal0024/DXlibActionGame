/*
*死亡時のテクスチャー
*概要：デットエフェクトクラスで使うためのテクスチャパーツの管理クラス
*/
#pragma once

#include"../../Base/Actor.h"

class DeadTexture : public Actor
{
public:
	DeadTexture(IWorld* world,ActorPtr Fade);
	~DeadTexture();
	void onUpdate(float deltaTime) override;
	void onDraw() const override;

private:
	ActorPtr mFade;
	ActorPtr mWhite;
	int mTexHandle;
	float mAlpha;
};
