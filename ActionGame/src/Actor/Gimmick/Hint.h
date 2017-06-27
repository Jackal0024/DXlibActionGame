/*
*�q���g�N���X
*�T�v�F�߂��Ɋ��ƕ\�������UI�����N���X
*/
#pragma once

#include"../Base/Actor.h"

class Hint : public Actor
{
public:
	//�R���X�g���N�^
	Hint(IWorld* world,const std::string& num, Vector3& position);
	//�R���X�g���N�^
	Hint(IWorld* world,const std::string& num, Vector3 position, Vector3 rotate);
	//�f�X�g���N�^
	~Hint();

private:
	//�X�V����
	void onUpdate(float deltaTime) override;
	//�`�揈��
	void onDraw() const override;
	//�ڐG���̏���
	void onCollide(Actor& other) override;
	//���b�Z�[�W���󂯎�������̏���
	void onMessage(EventMessage message, void* p) override;
private:
	ActorPtr mTarget;
	float mTimer;
	int mModelHandle;
	int mHintTexture;
	bool isDraw;
};
