/*
*���S���̃e�N�X�`���[
*�T�v�F�f�b�g�G�t�F�N�g�N���X�Ŏg�����߂̃e�N�X�`���p�[�c�̊Ǘ��N���X
*/
#pragma once

#include"../../Base/Actor.h"

class DeadTexture : public Actor
{
public:
	//�R���X�g���N�^
	DeadTexture(IWorld* world,ActorPtr Fade);
	//�f�X�g���N�^
	~DeadTexture();
	//�X�V����
	void onUpdate(float deltaTime) override;
	//�`�揈��
	void onDraw() const override;

private:
	ActorPtr mFade;
	ActorPtr mWhite;
	int mTexHandle;
	float mAlpha;
};
