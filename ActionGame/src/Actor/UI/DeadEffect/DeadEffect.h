/*
*���S���̃G�t�F�N�g�N���X
*�T�v�F���S���̃G�t�F�N�g���Ǘ�����
*/
#pragma once

#include"../../Base/Actor.h"

class DeadEffect : public Actor
{
public:
	//�R���X�g���N�^
	DeadEffect(IWorld* world);

private:
	ActorPtr mFade;
};
