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
	FlashEffect(IWorld* world, float end, float time, int color = GetColor(255, 255, 255));
	~FlashEffect();

	void onUpdate(float deltaTime) override;
	void onDraw() const override;

private:
	int mColor;
	float mAlpha;
	float mTime;
	float mTimer;
	float mEndAlpha;
	bool isFinale;

};

