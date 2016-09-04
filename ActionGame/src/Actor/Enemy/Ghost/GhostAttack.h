#pragma once
#include"../../Base/Actor.h"

class GhostArrack : public Actor
{
public:
	GhostArrack(IWorld* world, const Vector3& position, const Vector3& Velocity);
	void onUpdate(float deltaTime) override;
	void onDraw() const override;
	void onCollide(Actor& other) override;

private:
	float mTimer;
	Vector3 m_Velocity;
};