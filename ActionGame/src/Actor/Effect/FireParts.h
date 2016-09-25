#pragma once

#include"../Base/Actor.h"

class FirePats : public Actor
{
public:
	FirePats(IWorld* world, Vector3 position);
private:
	void onUpdate(float deltaTime) override;
	void onDraw() const override;

private:
	int mTexHandle;
	float mTimer;
	float mAngle;


};
