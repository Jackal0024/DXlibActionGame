#pragma once

#include"../../Base/Actor.h"

class IceNeedle : public Actor
{
public:
	IceNeedle(IWorld* world, Vector3 position,Vector3 velocity,int num);

private:
	void onUpdate(float deltaTime) override;
	void onDraw() const override;
	void onCollide(Actor& other) override;

private:
	Vector3 mVelocity;
	Vector3 mDestination; //–Ú“I’n
	float mLifeTimer_;
	int mNum;
	int mModelHandle;
	float mAtkPower;
	bool isNext;

};