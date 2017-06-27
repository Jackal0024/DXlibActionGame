/*
*�{�X�N���X
*�T�v�F�}�W�b�N�}�C���N���X���琶������锚���̃N���X
*/
#pragma once

#include"../../Base/Actor.h"
#include"../../../Effect/Base/Effect.h"

class Bomb : public Actor
{
public:
	//�R���X�g���N�^
	Bomb(IWorld* world, Vector3 position,Tag tag,float atk);
	//�f�X�g���N�^
	~Bomb();
private:
	//�X�V����
	void onUpdate(float deltaTime) override;
	//�`�揈��
	void onDraw() const override;
	//�����������̏���
	void onCollide(Actor& other) override;
private:
	int mModelHandle;
	float mTimer;
	float mAtkPower;
	bool mHit;
	IEffect mBombEffect;

private:
	//���@���̂̍U����
	const float MAGICPOWER = 40;

};
