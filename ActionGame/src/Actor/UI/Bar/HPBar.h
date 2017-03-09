#pragma once
#include"../../Base/Actor.h"

class HPBar :public  Actor
{
public:
	HPBar(IWorld* world, Vector3 position);
	~HPBar();
	void onUpdate(float deltaTime) override;
	void onDraw() const override;
private:
	float mMaxHP;
	float mHPValue;

	float mPrevHP;
	Vector3 mSlipBar_rb;
};
