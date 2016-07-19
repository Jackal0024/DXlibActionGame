#pragma once

#include"../Base/Actor.h"

class PlayerHP :public  Actor
{
public:
	PlayerHP(IWorld* world,Vector3 position);
	void onUpdate(float deltaTime) override;
	void onDraw() const override;
private:
	int mTextHandle;
	int mSlashHandle;
	int mHPValue;
	int mMaxHPValue;
};
