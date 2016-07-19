#pragma once
#include"../../Base/Actor.h"

class EnemyArrack : public Actor
{
public:
	EnemyArrack(IWorld* world, const Vector3& position);
	void onUpdate(float deltaTime) override;
	void onDraw() const override;

private:
	float mTimer;
};