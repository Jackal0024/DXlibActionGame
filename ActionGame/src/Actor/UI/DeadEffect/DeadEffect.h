/*
*死亡時のエフェクトクラス
*概要：死亡時のエフェクトを管理する
*/
#pragma once

#include"../../Base/Actor.h"

class DeadEffect : public Actor
{
public:
	//コンストラクタ
	DeadEffect(IWorld* world);

private:
	ActorPtr mFade;
};
