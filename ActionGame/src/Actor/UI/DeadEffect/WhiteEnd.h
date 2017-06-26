/*
*ホワイトエンドクラス
*概要：死亡時のスモークテクスチャの管理
*/
#pragma once

#include"../../Base/Actor.h"

class WhiteEnd : public Actor
{
public:
	WhiteEnd(IWorld* world);
	void onUpdate(float deltaTime) override;

private:
	ActorPtr mFade;
};
