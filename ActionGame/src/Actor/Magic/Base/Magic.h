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
