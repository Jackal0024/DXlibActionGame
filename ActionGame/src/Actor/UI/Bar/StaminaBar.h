#pragma once

#include"../../Base/Actor.h"

class StaminaBar :public  Actor
{
public:
	StaminaBar(IWorld* world, Vector3 position);
	~StaminaBar();
	void onUpdate(float deltaTime) override;
	void onDraw() const override;
private:
	float mMaxStamina;
	float mStaminaValue;
};