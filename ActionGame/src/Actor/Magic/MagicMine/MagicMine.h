#pragma once

#include"../../Base/Actor.h"

class MagicMine : public Actor
{
public:
	MagicMine(IWorld* world, Vector3 position, const Vector3& Velocity, Tag tag);
	~MagicMine();
private:
	void onUpdate(float deltaTime) override;
	void onDraw() const override;
	void onCollide(Actor& other) override;

	void Explosion();
private:
	int mModelHandle;
	Vector3 mVelocity;
	float mTimer;
	float mExpTimer;
	bool mHit;


};