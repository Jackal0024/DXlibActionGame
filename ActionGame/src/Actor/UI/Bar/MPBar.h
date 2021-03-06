/*
*マジックポイントバー
*概要：マジックポイントのＵＩ
*/
#pragma once

#include"../../Base/Actor.h"

class MPBar :public  Actor
{
public:
	MPBar(IWorld* world, Vector3 position);
	~MPBar();
	void onUpdate(float deltaTime) override;
	void onDraw() const override;
private:
	float mMaxMP;
	float mMPValue;

	float mPrevMP;
	Vector3 mSlipBar_rb;
};
