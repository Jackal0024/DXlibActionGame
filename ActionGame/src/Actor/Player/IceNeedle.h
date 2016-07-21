#pragma once

#include"../Base/Actor.h"

class IceNeedle : public Actor
{
public:
	IceNeedle(IWorld* world, Vector3 position,Vector3 velocity,int num);

private:
	void onUpdate(float deltaTime) override;
	void onDraw() const override;

private:
	Vector3 mVelocity;
	float mLifeTimer_;
	int mNum;
	int mModelHandle;
	bool isNext;

};