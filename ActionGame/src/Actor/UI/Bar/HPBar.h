/*
*�g�o�o�[�N���X
*�T�v�F�g�o�o�[�̂t�h�Ǘ�
*/
#pragma once
#include"../../Base/Actor.h"

class HPBar :public  Actor
{
public:
	//�R���X�g���N�^
	HPBar(IWorld* world, Vector3 position);
	//�f�X�g���N�^
	~HPBar();
	//�X�V����
	void onUpdate(float deltaTime) override;
	//�`�揈��
	void onDraw() const override;
private:
	float mMaxHP;
	float mHPValue;

	float mPrevHP;
	Vector3 mSlipBar_rb;
};
