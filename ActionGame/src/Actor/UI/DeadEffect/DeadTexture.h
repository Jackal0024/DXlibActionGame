/*
*死亡時のテクスチャー
*概要：デットエフェクトクラスで使うためのテクスチャパーツの管理クラス
*/
#pragma once

#include"../../Base/Actor.h"

class DeadTexture : public Actor
{
public:
	//コンストラクタ
	DeadTexture(IWorld* world,ActorPtr Fade);
	//デストラクタ
	~DeadTexture();
	//更新処理
	void onUpdate(float deltaTime) override;
	//描画処理
	void onDraw() const override;

private:
	ActorPtr mFade;
	ActorPtr mWhite;
	int mTexHandle;
	float mAlpha;
};
