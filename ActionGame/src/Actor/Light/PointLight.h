#pragma once

#include"../Base/Actor.h"
#include"../../Math/Vector3.h"

class PointLight : public Actor
{
public:
	//コンストラクタ
	PointLight(IWorld* world);
private:
	//描画
	virtual void onDraw() const override;
	virtual void onUpdate(float deltaTime) override;

private:
	ActorPtr mPlayer;
};