#pragma once

#include"../Base/Actor.h"
#include"NumberTexture.h"

class PlayerHP :public  Actor
{
public:
	PlayerHP(IWorld* world,Vector3 position);
	~PlayerHP();
	void onUpdate(float deltaTime) override;
	void onDraw() const override;
private:
	int mTextHandle;
	int mSlashHandle;
	float mHPValue;
	float mMaxHPValue;
	NumberTexture num;

	float mAtk;
};
