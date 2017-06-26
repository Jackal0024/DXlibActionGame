/*
*マジックマイン
*概要：爆発するクリスタルを飛ばす魔法
*/
#pragma once

#include"../../Base/Actor.h"

class MagicMine : public Actor
{
public:
	MagicMine(IWorld* world, Vector3 position, const Vector3& Velocity, Tag tag,float power);
	~MagicMine();
private:
	void onUpdate(float deltaTime) override;
	void onDraw() const override;
	void onCollide(Actor& other) override;

	void Explosion();
private:
	int mModelHandle;
	Vector3 mVelocity;
	float mTimer;
	float mExpTimer;
	bool mHit;
	float mPower;


};