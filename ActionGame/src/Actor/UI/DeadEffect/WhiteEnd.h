/*
*�z���C�g�G���h�N���X
*�T�v�F���S���̃X���[�N�e�N�X�`���̊Ǘ�
*/
#pragma once

#include"../../Base/Actor.h"

class WhiteEnd : public Actor
{
public:
	WhiteEnd(IWorld* world);
	void onUpdate(float deltaTime) override;

private:
	ActorPtr mFade;
};
