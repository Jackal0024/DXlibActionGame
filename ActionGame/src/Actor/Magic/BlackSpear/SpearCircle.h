/*
*スピアーサークルクラス
*概要：スピアーを召喚するための魔法陣
*/
#pragma once

#include"../../Base/Actor.h"

class SpearCircle : public Actor
{
public:
	SpearCircle(IWorld * world, Vector3 position, Tag tag, float power);
	~SpearCircle();
private:
	void onUpdate(float deltaTime) override;
	void onDraw() const override;
	void onCollide(Actor& other) override;

private:
	int mModelHandle;
	float mTimer;
	float mPower;

};
