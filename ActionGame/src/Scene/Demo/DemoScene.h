/*
*�f���V�[���N���X
*�T�v�F���E�������̃V�[���̃N���X
*/
#pragma once

#include"../Base/IScene.h"
#include"../../World/World.h"
#include"../../System/MagicMenu/MagicMenu.h"

class DemoScene : public IScene
{
public:
	//�J�n����
	virtual void Start() override;
	//�X�V����
	virtual void Update(float deltaTime) override;
	//�`�揈��
	virtual void Draw() const override;
	//�V�[�����I�����Ă��邩�ǂ���
	virtual bool IsEnd() const override;
	//���̃V�[��
	virtual Scene Next() const override;
	//�I������
	virtual void End() override;
	//�C�x���g���󂯎��
	void HandleMessage(EventMessage message, void* param);
private:
	int mBackGround;
	int mDemoText;
	int mSkipText;
	float mDemoTextYPos;

	float mTimer;

	bool isEnd;
	bool isDraw;
};