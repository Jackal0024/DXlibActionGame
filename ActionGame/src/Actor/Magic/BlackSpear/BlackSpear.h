#pragma once

#include"../../Base/Actor.h"

class BlackSpear : public Actor
{
public:
	BlackSpear(IWorld * world, Vector3 position, Tag tag);
	~BlackSpear();
private:
	void onUpdate(float deltaTime) override;
	void onDraw() const override;
	void onCollide(Actor& other) override;
private:
	Vector3 mToPos; //�ړI�̏ꏊ
	Vector3 mFromPos;
	int mModelHandle;
	float mTimer;
	float mAtkPower;
	bool mHit;

};