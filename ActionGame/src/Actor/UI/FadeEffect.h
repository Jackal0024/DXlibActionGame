/*
*�t�F�[�h�G�t�F�N�g
*�T�v�F�t�F�[�h���Ǘ�����N���X
*/
#pragma once

#include"../Base/Actor.h"
#include<string>

class Fadeeffect : public Actor
{
public:
	//�R���X�g���N�^
	Fadeeffect(IWorld* world, float start, float end,float time ,int color = GetColor(255,255,255));
	//�摜�Ńt�F�[�h�̏�������Ƃ��̃R���X�g���N�^
	Fadeeffect(IWorld* world, float start, float end, float time, std::string filename);
	//�f�X�g���N�^
	~Fadeeffect();
	//�X�V����
	void onUpdate(float deltaTime) override;
	//�`�揈��
	void onDraw() const override;
	//�I�����Ă��邩
	bool IsEnd();

private:
	int mTextureHandle;
	float mAlpha;
	float mStartAlpha;
	float mEndAlpha;
	float mTime;
	float mTimer;
	int mColor;
	bool isFadeIn;
	bool isFadeOut;
};