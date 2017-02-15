#pragma once

#include"../../Base/Actor.h"

class RockBlast : public Actor
{
public:
	RockBlast(IWorld* world, Vector3 position, const Vector3& Velocity, Tag tag,float atk);
	~RockBlast();
private:
	void onUpdate(float deltaTime) override;
	void onDraw() const override;
	void onCollide(Actor& other) override;

private:
	int mModelHandle;
	float mTimer;
	float mAtkPower;
	Vector3 mVelocity;
	Vector3 mGravity;
	bool mHit;

private:
	//ñÇñ@é©ëÃÇÃçUåÇóÕ
	const float MAGICPOWER = 30;

};
