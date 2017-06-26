/*
*マジック基底クラス
*概要：マジックの基底クラスだが現在は使用されていない
*/
#pragma once

class Magic
{
public:
	Magic(float cost, float power);
	float GetCost() const;
	float GetPower() const;
protected:
	float mMPCost;
	float mAttackPower;
};
