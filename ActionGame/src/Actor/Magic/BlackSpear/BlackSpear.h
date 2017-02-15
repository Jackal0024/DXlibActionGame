#pragma once

#include"../../Base/Actor.h"

class BlackSpear : public Actor
{
public:
	BlackSpear(IWorld * world, Vector3 position, Tag tag,float atk);
	~BlackSpear();
private:
	void onUpdate(float deltaTime) override;
	void onDraw() const override;
	void onCollide(Actor& other) override;
private:
	Vector3 mToPos; //–Ú“I‚ÌêŠ
	Vector3 mFromPos;
	int mModelHandle;
	float mTimer;
	float mAtkPower;
	bool mHit;

private:
	//–‚–@©‘Ì‚ÌUŒ‚—Í
	const float MAGICPOWER = 20;

};
