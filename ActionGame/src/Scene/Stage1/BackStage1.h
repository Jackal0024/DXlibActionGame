/*
*�A��̃X�e�[�W�P
*�T�v�F�v���C���[���X�e�[�W�Q����A���Ă������̃X�e�[�W
*/
#pragma once

#include"../Base/IScene.h"
#include"../../World/World.h"
#include"../../System/MagicMenu/MagicMenu.h"

class BackStage1 : public IScene
{
public:
	//�J�n����
	virtual void Start() override;
	//�X�V����
	virtual void Update(float deltaTime) override;
	//�`�揈��
	virtual void Draw() const override;
	//�I���̃t���O�������Ă��邩
	virtual bool IsEnd() const override;
	//���̃V�[��
	virtual Scene Next() const override;
	//�I������
	virtual void End() override;
	//�C�x���g���󂯎��
	void HandleMessage(EventMessage message, void* param);

private:
	//�}�b�v���󂯎��
	void MapDateInput(const std::string& fileName);
	//���f���𐶐�����
	void CharacterCreate(const std::string& name, Vector3& position, Vector3& rotate);
	//�S�[������ݒ�A��������
	void GolemCreate(Vector3& position, Vector3& rotate);
	//���U�[�h��ݒ�A��������
	void LizardCreate(Vector3& position, Vector3& rotate);
	//�t�F�[�h�̏���
	void IsFadeEnd();
private:
	std::shared_ptr<World> mWorld;
	ActorPtr mFade;
	bool isFade;
	Scene mNext;
	MagicMenu mMenu;
	bool isPause;
	bool isEnd;
	bool isDraw;

};
