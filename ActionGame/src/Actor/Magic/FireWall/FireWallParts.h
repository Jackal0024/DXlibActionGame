/*
*�t�@�C�A�[�E�H�[���̃p�[�c�N���X
*�T�v�F�t�@�C�A�[�E�H�[���Ŕ�������Β��̂P�{
*/
#pragma once
#include"../../Base/Actor.h"
#include"../../../Effect/Base/Effect.h"

class FireWallParts :public  Actor
{
public:
	//�R���X�g���N�^
	FireWallParts(IWorld * world, Vector3 position, const Vector3 & Velocity, Tag tag,float atk);
	//�f�X�g���N�^
	~FireWallParts();
private:
	//�X�V����
	void onUpdate(float deltaTime) override;
	//�`�揈��
	void onDraw() const override;
	//�ڐG���̏���
	void onCollide(Actor& other) override;
private:
	int mModelHandle;
	float mTimer;
	Vector3 mVelocity;
	float mAtkPower;
	bool mHit;
	IEffect mFireEffect;

private:
	//���@���̂̍U����
	const float MAGICPOWER = 40;

};
