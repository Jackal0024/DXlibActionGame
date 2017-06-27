/*
*�q�[���T�[�N���N���X
*�T�v�F�v���C���[���񕜂�����N���X
*/
#pragma once

#include"../Base/Actor.h"

class HealCircle :public Actor
{
public:
	//�R���X�g���N�^
	HealCircle(IWorld* world, Vector3 position);
	//�R���X�g���N�^
	HealCircle(IWorld* world, Vector3 position, Vector3 rotate);
	//�f�X�g���N�^
	~HealCircle();
private:
	//�J�n����
	void onStart() override;
	//�`�揈��
	void onUpdate(float deltaTime) override;
	//�`�揈��
	void onDraw() const override;
	//�ڐG���̏���
	void onCollide(Actor& other) override;
	//�C�x���g���󂯎�������̏���
	void onMessage(EventMessage message, void* p);

private:
	int mHandle;
	bool isHealing;
	ActorPtr mTarget;

};
