#pragma once

#include"../../Base/Actor.h"

class Bomb : public Actor
{
public:
	Bomb(IWorld* world, Vector3 position,Tag tag);
	~Bomb();
private:
	void onUpdate(float deltaTime) override;
	void onDraw() const override;
	void onCollide(Actor& other) override;
private:
	int mModelHandle;
	float mTimer;
	float mAtkPower;
	bool mHit;

};
