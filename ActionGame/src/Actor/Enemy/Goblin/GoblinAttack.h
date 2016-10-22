#pragma once

#include"../../Base/Actor.h"

class GoblinAttack : public Actor
{
public:
	GoblinAttack(IWorld* world, const Vector3& position,float delay);
	void onUpdate(float deltaTime) override;
	void onDraw() const override;
	void onCollide(Actor& othr) override;

private:
	float mDelay;
	float mTimer;
	float mAtk;
};
