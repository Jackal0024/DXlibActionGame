#pragma once

#include"../Base/Actor.h"
#include"NumberTexture.h"

class PlayerMP :public  Actor
{
public:
	PlayerMP(IWorld* world, Vector3 position);
	~PlayerMP();
	void onUpdate(float deltaTime) override;
	void onDraw() const override;
private:
	int mTextHandle;
	int mSlashHandle;
	float mMPValue;
	float mMaxMPValue;
	NumberTexture num;

	float mMagicInterval;
};
