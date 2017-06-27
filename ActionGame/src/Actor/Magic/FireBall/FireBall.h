/*
*�t�@�C�A�[�{�[��
*�T�v�F�t�@�C�A�[�{�[���̖��@�N���X
*/
#pragma once

#include"../../Base/Actor.h"
#include"../../../Effect/Base/Effect.h"

class FireBall : public Actor
{
public:
	//�R���X�g���N�^
	FireBall(IWorld* world, Vector3 position, const Vector3& Velocity,Tag tag,float atk = 20);
	//�f�X�g���N�^
	~FireBall();
private:
	//�X�V����
	void onUpdate(float deltaTime) override;
	//�`�揈��
	void onDraw() const override;
	//�����������̏���
	void onCollide(Actor& other) override;


private:
	IEffect mEffect;
	int mHandle[32];
	int mIndex;
	float mTimer;
	float mAtkPower;
	Vector3 mVelocity;

private:
	//���@���̂̍U����
	const float MAGICPOWER = 5;

};
