/*
*�t���b�V���G�t�F�N�g�N���X
*�T�v�F��ʂɃt���b�V���G�t�F�N�g������
*/
#pragma once

#include"../Base/Actor.h"
#include<string>

class FlashEffect : public Actor
{
public:
	//�R���X�g���N�^
	FlashEffect(IWorld* world, float end, float time, int color = GetColor(255, 255, 255));
	//�f�X�g���N�^
	~FlashEffect();
	//�X�V����
	void onUpdate(float deltaTime) override;
	//�`�揈��
	void onDraw() const override;

private:
	int mColor;
	float mAlpha;
	float mTime;
	float mTimer;
	float mEndAlpha;
	bool isFinale;

};

