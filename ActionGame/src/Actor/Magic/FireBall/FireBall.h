#pragma once

#include"../../Base/Actor.h"
#include"../../../Effect/Base/Effect.h"

class FireBall : public Actor
{
public:
	FireBall(IWorld* world, Vector3 position, const Vector3& Velocity,Tag tag,float atk = 20);
	~FireBall();
private:
	void onUpdate(float deltaTime) override;
	void onDraw() const override;
	void onCollide(Actor& other) override;


private:
	IEffect mEffect;
	int mHandle[32];
	int mIndex;
	float mTimer;
	float mAtkPower;
	Vector3 mVelocity;

private:
	//ñÇñ@é©ëÃÇÃçUåÇóÕ
	const float MAGICPOWER = 5;

};
