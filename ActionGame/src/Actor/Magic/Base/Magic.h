/*
*�}�W�b�N���N���X
*�T�v�F�}�W�b�N�̊��N���X�������݂͎g�p����Ă��Ȃ�
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
