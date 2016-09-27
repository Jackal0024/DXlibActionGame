#pragma once

#include"../../Base/Actor.h"

class FireBall : public Actor
{
public:
	FireBall(IWorld* world, Vector3 position, const Vector3& Velocity);
	~FireBall();
private:
	void onUpdate(float deltaTime) override;
	void onDraw() const override;
	void onCollide(Actor& other) override;


private:
	int mHandle[32];
	int mIndex;
	float mTimer;
	float mAtkPower;
	Vector3 mVelocity;

};
