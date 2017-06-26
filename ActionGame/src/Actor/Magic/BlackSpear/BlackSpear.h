/*
*トラップスピアークラス
*概要：トラップスピアーの管理をするクラス
*/
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
	Vector3 mToPos; //目的の場所
	Vector3 mFromPos;
	int mModelHandle;
	float mTimer;
	float mAtkPower;
	bool mHit;

private:
	//魔法自体の攻撃力
	const float MAGICPOWER = 20;

};
