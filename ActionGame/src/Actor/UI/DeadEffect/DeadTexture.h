/*
*���S���̃e�N�X�`���[
*�T�v�F�f�b�g�G�t�F�N�g�N���X�Ŏg�����߂̃e�N�X�`���p�[�c�̊Ǘ��N���X
*/
#pragma once

#include"../../Base/Actor.h"

class DeadTexture : public Actor
{
public:
	DeadTexture(IWorld* world,ActorPtr Fade);
	~DeadTexture();
	void onUpdate(float deltaTime) override;
	void onDraw() const override;

private:
	ActorPtr mFade;
	ActorPtr mWhite;
	int mTexHandle;
	float mAlpha;
};
