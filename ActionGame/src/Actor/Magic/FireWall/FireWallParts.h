#pragma once
#include"../../Base/Actor.h"

class FireWallParts :public  Actor
{
public:
	FireWallParts(IWorld * world, Vector3 position, const Vector3 & Velocity, Tag tag);
	~FireWallParts();
private:
	void onUpdate(float deltaTime) override;
	void onDraw() const override;
	void onCollide(Actor& other) override;
private:
	int mModelHandle;
	float mTimer;
	Vector3 mVelocity;
	float mAtkPower;
	bool mHit;

};
